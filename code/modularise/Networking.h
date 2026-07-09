#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "Config.h"

#define NUM_PLAYERS 4
#define PLAYER_TAG 3
#define BOMB_TIMEOUT 4000.0

extern ErrEvent errEvent;
extern NetDisplayErr errBuffer;
extern String netErrMsg;

enum PacketType {
  BEACON,        // BROADCASTS PARTY INVITE

  JOIN_REQUEST,  // CLIENT ASKS TO JOIN
  JOIN_ACCEPT,   // HOST APPROVES
  JOIN_REJECT,   // HOST REJECTS

  HEARTBEAT,     // TO ENSURE CLIENT IS CONNECTED

  PLAYER_UPDATE, // UPDATING OTHER PLAYERS ABOUT NEW PLAYERS
  PLAYER_REMOVE, // UPDATING OTHER PLAYERS ABOUT DISCONNECTS

  START, 
  POLLING_DATA
};

struct Player {
  int x;
  int y;
  char id[PLAYER_TAG + 1];
};

struct PlayerEntry {
  uint8_t mac[6];
  Player status;
  bool isActive;
  uint32_t lastBeat;
};

struct Packet {
  PacketType type;
  union {
    uint32_t partyCode;
    Player status;
    PlayerEntry pEntry;
    PlayerEntry playerInit[NUM_PLAYERS];
    char raw[26];
    uint8_t mac[6];
  } payload;
};

void IRAM_ATTR gameEncoderISR();

class Networking {
public:
  Networking();
  void begin();
  void setMode(NetMode mode) { _m = mode; };
  NetMode getMode() { return _m; };
  const PlayerEntry getPlayer(int i) { return _players[i]; };
  void pollData();

  void handleEncoder();

  // HOST CONTROLS
  void genBeacon(const uint32_t code);
  void sendBeacon();
  void setJoinCode(uint32_t code) { _joinCode = code; };
  void checkHeartbeat();
  void removePlayer(const uint8_t mac[6]);
  void acceptJoinRequest(const uint8_t clientMac[6]);
  void rejectJoinRequest(const uint8_t clientMac[6]);
  void hostHeartbeat();
  void startGame();
  
  // CLIENT CONTROLS
  void sendJoinRequest(const uint8_t mac[6]);
  void heartbeat();
  void checkHostHeartbeat();

  const PlayerEntry& getPlayer(int i) const { return _players[i]; }
  
  Player _me;
  Player *currFocus;
  unsigned long lastBomb;

private:
  static void OnDataSent(const wifi_tx_info_t* tx_info, esp_now_send_status_t status);
  static void OnDataRecv(const esp_now_recv_info_t* recv_info, const uint8_t* incomingData, int len);
  void sendMessage(const Packet &pkt, const uint8_t mac[6]);
  void addPlayer(const PlayerEntry p);

  esp_now_peer_info_t _peerInfo;
  static Packet _incoming;
  Packet _b;
  NetMode _m;
  static uint32_t _joinCode;
  PlayerEntry _players[NUM_PLAYERS-1];
  uint8_t _playerCount = 0;
  uint8_t _hostMac[6];
  static Networking* _instance;
  int lastBeat;
  bool _prevSt;
  int focusOff = 0;
};

extern Networking *netInstance;