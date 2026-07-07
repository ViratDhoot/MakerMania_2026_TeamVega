#include "Networking.h"

ErrEvent errEvent;

Packet Networking::_incoming;
uint32_t Networking::_joinCode;
Networking* Networking::_instance = nullptr;

Networking::Networking() {
    _instance = this;
    lastBeat = millis();
    for (int i = 0; i < PLAYER_TAG; i++) {
      _me.id[i] = random(65, 91);
    }
}

void Networking::begin() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ERROR initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
}

void Networking::startGame() {
  Packet s;
  s.type = START;

  int posList[4][2] = {
    {       0, MAZE_H/2}, 
    {MAZE_W/2,   MAZE_H}, 
    {  MAZE_W, MAZE_H/2}, 
    {MAZE_W/2,        0}
  };

  for (int i = 3; i > 0; i--) {
    // Pick a random index from 0 to i (inclusive)
    int j = random(0, i + 1);
    
    int temp[2];
    memcpy(temp, posList[i], sizeof(temp));
    memcpy(posList[i], posList[j], sizeof(temp));
    memcpy(posList[j], temp, sizeof(temp));
  }

  _me.x = posList[0][0] * DIM[0];
  _me.y = posList[0][1] * DIM[1];
  s.payload.playerInit[0].status = _me;
  WiFi.macAddress(s.payload.playerInit[0].mac);
  for (int i = 0; i < NUM_PLAYERS-1; i++) {
    if (!_players[i].isActive) continue;
    _players[i].status.x = posList[i+1][0] * DIM[0];
    _players[i].status.y = posList[i+1][1] * DIM[1];
    s.payload.playerInit[i+1].status = _players[i].status;
    memcpy(s.payload.playerInit[i+1].mac, _players[i].mac, 6);
  }

  for (auto &player : _players) {
    if (!player.isActive) continue;
    sendMessage(s, player.mac);
  }
}

void Networking::genBeacon(const uint32_t code) {
  _b.payload.partyCode = code;
  _b.type = BEACON;
}

void Networking::sendBeacon() {
  uint8_t broadcastAddr[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  sendMessage(_b, broadcastAddr);
}

void Networking::checkHeartbeat() {
  for (auto &player : _players) {
    if (!player.isActive) continue;
    if ((millis() - player.lastBeat) > 3000) {
      player.isActive = false;
      removePlayer(player.mac);
    }
  }
}

void Networking::checkHostHeartbeat() {
  for (auto &player : _players) {
    if (memcmp(player.mac, _hostMac, 6) != 0) continue;
    if ((millis() - player.lastBeat) > 3000) {
      player.isActive = false;
      errEvent = { MESSAGE, "HOST DISCONNECTED", millis(), 2000 };
    }
  }
}

void Networking::removePlayer(const uint8_t mac[6]) {
  Packet remP;
  remP.type = PLAYER_REMOVE;
  memcpy(remP.payload.mac, mac, 6);
  for (auto &player : _players)
    sendMessage(remP, player.mac);
  _playerCount--;
}

void Networking::heartbeat() {
  Packet h;
  h.type = HEARTBEAT;
  if (millis() - lastBeat > 200) {
    sendMessage(h, _hostMac);
    lastBeat = millis();
  }
}

void Networking::hostHeartbeat() {
  Packet h;
  h.type = HEARTBEAT;
  for (auto &player : _players) {
    if (!player.isActive) continue;
    Serial.println("SENDING HEARTBEAT");
    if (millis() - lastBeat > 200) {
      sendMessage(h, player.mac); 
      lastBeat = millis();
    }
  }
}

void Networking::sendMessage(const Packet &pkt, const uint8_t mac[6]) {
  memcpy(&_peerInfo.peer_addr, mac, 6);
  _peerInfo.channel = 0;
  _peerInfo.encrypt = false;
  if (!esp_now_is_peer_exist(mac))
    esp_now_add_peer(&_peerInfo);
  esp_err_t result = esp_now_send(mac, (const uint8_t *)&pkt, sizeof(pkt));
}

void Networking::OnDataSent(const wifi_tx_info_t* tx_info, esp_now_send_status_t status) {
  // if (_instance->_m == JOINING) {
  //   if (status != ESP_NOW_SEND_SUCCESS) {
  //     _instance->sendJoinRequest(_instance->_hostMac);
  //   }
  // }
}

void Networking::OnDataRecv(const esp_now_recv_info_t* recv_info, const uint8_t* incomingData, int len) {
  memcpy(&_incoming, incomingData, sizeof(_incoming));  
  if (_instance->_m == JOINING) {
    switch (_incoming.type) {
      // FOR THE CLIENT
      case BEACON:
        if (_incoming.payload.partyCode == _joinCode) {
          Serial.println("CONNECTED!!!");
          memcpy(_instance->_hostMac, recv_info->src_addr, 6);
          _instance->sendJoinRequest(_instance->_hostMac);
        _instance->setMode(WAITING);
        }
        break;

      // FOR THE HOST
      case JOIN_REQUEST:
        if (_instance->_playerCount < NUM_PLAYERS-1) {
          _instance->acceptJoinRequest(recv_info->src_addr);
          PlayerEntry newPlayer;
          memcpy(newPlayer.mac, recv_info->src_addr, 6);
          newPlayer.status = _incoming.payload.status;
          newPlayer.isActive = true;
          newPlayer.lastBeat = millis();
          for (PlayerEntry p : _instance->_players) {
            if (!p.isActive) continue;
            Packet newPlayerPacket;
            newPlayerPacket.type = PLAYER_UPDATE;
            newPlayerPacket.payload.pEntry = newPlayer;
            _instance->sendMessage(
              newPlayerPacket, 
              p.mac
            );
          }
          _instance->addPlayer(newPlayer);
          // UPDATING THE EXISTING PLAYERS TO THE NEW PLAYER
          Packet updatePlayerList;
          updatePlayerList.type = PLAYER_UPDATE;
          for (int i = 0; i < NUM_PLAYERS-1; i++) {
            if (!_instance->_players[i].isActive || (memcmp(_instance->_players[i].mac, newPlayer.mac, 6) == 0)) continue;
            updatePlayerList.payload.pEntry = _instance->_players[i];
            _instance->sendMessage(updatePlayerList, newPlayer.mac);
          }
        } else {
          _instance->rejectJoinRequest(recv_info->src_addr);
        }
        break;
      
      case HEARTBEAT:
        for (auto &player : _instance->_players) {
          if (memcmp(player.mac, recv_info->src_addr, 6) == 0)
            player.lastBeat = millis();
        }
        break;
    }
  } else if (_instance->_m == WAITING) {
    switch(_incoming.type) {
      case HEARTBEAT:
        Serial.println("RECIEVED HEARTBEAT FROM HOST");
        for (auto &player : _instance->_players) {
          if (memcmp(player.mac, recv_info->src_addr, 6) == 0)
            player.lastBeat = millis();
        }
        break;

      case PLAYER_UPDATE:
        _instance->addPlayer(_incoming.payload.pEntry);
        break;

      case PLAYER_REMOVE:
        for (int i = 0; i < NUM_PLAYERS-1; i++) {
          if (memcmp(_instance->_players[i].mac, _incoming.payload.mac, 6) == 0)
            _instance->_players[i].isActive = false;
        }
        break;
      
      case JOIN_ACCEPT:
        PlayerEntry newPlayer;
        memcpy(newPlayer.mac, recv_info->src_addr, 6);
        newPlayer.status = _incoming.payload.status;
        newPlayer.isActive = true;
        newPlayer.lastBeat = millis();
        _instance->addPlayer(newPlayer);
        break;
      
      case JOIN_REJECT:
        Serial.println("Couldn't Join");
        break;

      case START:
        for (auto &init : _incoming.payload.playerInit) {
          if (!init.isActive) continue;
          if (memcmp(init.mac, WiFi.macAddress(new uint8_t[6]), 6) == 0) {
              _instance->_me.x = init.status.x;
              _instance->_me.y = init.status.y;
          } else {
            for (auto &player : _instance->_players) {
              if (!player.isActive) continue;
              if (memcmp(init.mac, player.mac, 6) == 0) {
                player.status = init.status;
                break;
              }
            }
          }
        }
        _instance->setMode(IN_GAME);
        break;
    }
  } else if (_instance->_m == IN_GAME) {
    switch(_incoming.type) {
      case HEARTBEAT:
        for (auto &player : _instance->_players) {
          if (memcmp(player.mac, recv_info->src_addr, 6) == 0)
            player.lastBeat = millis();
        }
        break;

      case POLLING_DATA:
        for (auto &player : _instance->_players) {
          if (memcmp(player.mac, recv_info->src_addr, 6) == 0)
            player.status = _incoming.payload.status;
        }
        break;
    }
  }
}

void Networking::pollData() {
  Packet d;
  d.type = POLLING_DATA;
  d.payload.status = _me;  
  for (auto &player : _players) {
    if (!player.isActive) continue;
    sendMessage(d, player.mac);
  }
}

void Networking::sendJoinRequest(const uint8_t mac[6]) {
  Packet req;
  req.type = JOIN_REQUEST;
  req.payload.status = _me;
  sendMessage(req, mac);
}

void Networking::acceptJoinRequest(const uint8_t clientMac[6]) {
  Packet resp;
  resp.type = JOIN_ACCEPT;
  resp.payload.status = _me;
  sendMessage(resp, clientMac);
}

void Networking::rejectJoinRequest(const uint8_t clientMac[6]) {
  Packet resp;
  resp.type = JOIN_REJECT;
  sendMessage(resp, clientMac);
}

void Networking::addPlayer(const PlayerEntry p) {
  Serial.println(p.status.id);
  for (int i = 0; i < NUM_PLAYERS-1; i++) {
    if ((memcmp(_players[i].mac, p.mac, 6) == 0) && _players[i].isActive)
      return;
  }
  for (int i = 0; i < NUM_PLAYERS-1; i++) {
    if (!_players[i].isActive) {
      _players[i] = p;
      _playerCount++;
      return;
    }
  }
}