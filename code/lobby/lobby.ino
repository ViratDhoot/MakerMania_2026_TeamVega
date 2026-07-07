#include <Wire.h>
#include <Adafruit_GFX.h>
#include <WiFi.h>
#include <esp_now.h>

#define LEN(X) (sizeof(X) / sizeof(X[0]))

// #define SMOL
#define BIG

#define BROADCAST { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

#ifdef BIG
#include <Adafruit_SH110X.h>
#endif

#ifdef SMOL
#include <Adafruit_SSD1306.h>
#endif

// Screen Dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#ifdef BIG
#define SWHITE SH110X_WHITE
#endif
#ifdef SMOL
#define SWHITE WHITE
#endif
#ifdef BIG
#define SBLACK SH110X_BLACK
#endif
#ifdef SMOL
#define SBLACK BLACK
#endif

// ENC PINS
#define ENC_CLK 18
#define ENC_DT 19
#define ENC_SW 23

// JOYSTICK PINS
#define JOY_SW 27
#define JOY_X 32
#define JOY_Y 33

#define CODE_LEN 5

#ifdef BIG
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#endif
#ifdef SMOL
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#endif

// uint8_t broadcastAddress[] = MAC_ADDR;

// INPUT MECHANISM
class TextInput;
void IRAM_ATTR encoderISR();

TextInput *activeInput = nullptr;

class TextInput {
private:
  String text;
  int _x, _y;
  int _size;
  volatile int _off;
  volatile bool _prevSt;
  int _cIdx;
  char _c;
  int _buttonTick; // for debouncing
  int _chars;
  int _maxLen;
  uint16_t _w;
  uint16_t _h;

public:
  TextInput(int x, int y, int size, int max_length, char def)
    : _x(x),
      _y(y),
      _size(size),
      _off(0),
      _prevSt(digitalRead(ENC_CLK)),
      _cIdx(0),
      _c('A'),
      _buttonTick(millis()),
      _chars(0),
      text(""), 
      _maxLen(max_length)
  {
    for (int i = 0; i < _maxLen; i++)
      text += def;
  };

  void begin() {
    activeInput = this;
    int16_t x1, y1;
    display.setTextSize(_size);
    display.getTextBounds(text, 0, 0, &x1, &y1, &_w, &_h);
    attachInterrupt(
        digitalPinToInterrupt(ENC_CLK),
        encoderISR,
        CHANGE
    );
  }

  void IRAM_ATTR handleEncoder() {
    bool currSt = digitalRead(ENC_CLK);
    bool dtSt = digitalRead(ENC_DT);

    if (currSt != _prevSt) {
      if (dtSt != currSt) {
        _off++;
        if (_off > 25)
          _off = 25;
      } else {
        _off--;
        if (_off < 0)
          _off = 0;
      }
      _prevSt = currSt;
    }
  }

  void update() {
    if (analogRead(JOY_X) > (3.0f * 4096.0f / 4.0f) && (millis() - _buttonTick > 200)) {
      _buttonTick = millis();
      if (_cIdx < _maxLen - 1) {
        if (_cIdx < text.length())
          text[_cIdx] = _c;
        else
          text += _c;
        _cIdx++;
        _chars = text.length();
        if (_cIdx < text.length())
          _off = text[_cIdx] - 'A';
        else
          _off = 0;
      }
    }

    // go back
    if (analogRead(JOY_X) < (4096.0f / 4.0f) && (millis() - _buttonTick > 200)) {
      _buttonTick = millis();
      if (_cIdx > 0) {
        _cIdx--;
        _off = text[_cIdx] - 'A';
      }
    }
    
    if (_cIdx < text.length())
      text[_cIdx] = _c;
    else
      text += _c;
    _c = 'A' + _off;
  }

  void end() {
    detachInterrupt(digitalPinToInterrupt(ENC_CLK));
    if (activeInput == this)
      activeInput = nullptr;
  }

  void draw() {
    display.setTextSize(_size);
    display.setTextColor(SWHITE);
    display.setCursor(_x - _w/2, _y - _h/2);
    display.println(text.substring(0, _cIdx) + _c + text.substring(_cIdx + 1));
    display.setCursor(_x - _w/2, _y - _h/2 + _size + 1);
    String sel = "";
    for (int i = 0; i < _cIdx; i++)
      sel += " ";
    sel += "_";
    for (int i = _cIdx; i < _chars; i++)
      sel += " ";
    display.println(sel);
  }

  String getText(){
    text = text.substring(0, _cIdx) + _c + text.substring(_cIdx + 1);
    return text;
  }
};

void IRAM_ATTR encoderISR() {
  if (activeInput)
    activeInput->handleEncoder();
}

struct Player {
    int x;
    int y;
    int id;
};

Player myData = { 0, 0, 0 };

esp_now_peer_info_t peerInfo;

struct Packet {
  uint8_t type; // 0 = BEACON, 1 = CONNECTION, 2 = ACKNOWLEDGEMENT
  uint8_t mac[6];
  char payload[32];
};

void OnDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) {
  Serial.print("Last Packet Sent to: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(tx_info->src_addr[i]);
    if (i < 5) Serial.print(":");
  }
  Serial.println();
  Serial.print("Last Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

bool rec = false;
Packet info;
void broadcast(const Packet &p);

void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len) {
  memcpy(&info, incomingData, sizeof(info));
  Serial.print(info.type);
  Serial.print(", ");
  Serial.print(info.payload);
  Serial.print(", ");
  for (int i = 0; i < 6; i++)
    Serial.print(String(info.mac[i]) + ":");
  rec = true;
  Serial.println();
}

void broadcast(const Packet &p) {
  uint8_t broadcastAddr[6] = BROADCAST;
  memcpy(&peerInfo.peer_addr, broadcastAddr, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (!esp_now_is_peer_exist(broadcastAddr))
    esp_now_add_peer(&peerInfo);
  esp_err_t result = esp_now_send(broadcastAddr, (const uint8_t *)&p, sizeof(p));
 
  if (result == ESP_OK)
    Serial.println("Broadcast message success");
  else if (result == ESP_ERR_ESPNOW_NOT_INIT)
    Serial.println("ESP-NOW not Init.");
  else if (result == ESP_ERR_ESPNOW_ARG)
    Serial.println("Invalid Argument");
  else if (result == ESP_ERR_ESPNOW_INTERNAL)
    Serial.println("Internal Error");
  else if (result == ESP_ERR_ESPNOW_NO_MEM)
    Serial.println("ESP_ERR_ESPNOW_NO_MEM");
  else if (result == ESP_ERR_ESPNOW_NOT_FOUND)
    Serial.println("Peer not found.");
  else
    Serial.println("Unknown error");
}

enum Screen {
  INITGAME, 
  LOBBY, 
  GAME
};

Screen currFrame = INITGAME;

void drawText(int x, int y, const char *text, int size, bool light) {
  int16_t px, py;
  uint16_t w, h;

  display.setTextSize(size);
  display.getTextBounds(text, 0, 0, &px, &py, &w, &h);
  px = x - (w / 2);
  py = y - (h / 2);
  if (light)
    display.setTextColor(SWHITE);
  else
    display.setTextColor(SBLACK);
  display.setCursor(px, py);
  display.println(text);
}

void drawText(int x, int y, const String &text, int size, bool light) {
  drawText(x, y, text.c_str(), size, light);
}

void drawButton(int x, int y, const char *text, int size, bool selected) {
  int16_t px, py;
  uint16_t w, h;

  display.setTextSize(size);
  display.getTextBounds(text, 0, 0, &px, &py, &w, &h);
  px = x - (w / 2);
  py = y - (h / 2);
  int m = 3; // margin
  if (selected) {
    display.fillRoundRect(px-m, py - m, w + 2*m, h + 2 * m, 3, SWHITE);
    display.setTextColor(SBLACK);
  } else {
    display.setTextColor(SWHITE);
    display.drawRoundRect(px-m, py - m, w + 2*m, h + 2 * m, 3, SWHITE);
  }
  display.setCursor(px, py);
  display.println(text);
}

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);
#ifdef BIG
  display.begin(0x3C, true);
#endif
#ifdef SMOL
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
#endif

  currFrame = INITGAME;

  display.clearDisplay();
  display.display();
  pinMode(JOY_SW, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ERROR initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
}

Packet pkt;
bool isInit = false;

// Player friends[3];

Player players[4] = { myData, {0, 0, -1}, {0, 0, -1}, {0, 0, -1} };

void InitLobby(String &party) {
  party = "";
  for (int i = 0; i < CODE_LEN; i++)
    party += char('0' + random(0, 10));
  isInit = true;
}

bool isHost = false;
bool onJoin = false;
int lastToggle = millis();
String party;
TextInput codeInput(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 5, '0');

void loop() {
  display.clearDisplay();
  float joyX = (analogRead(JOY_X) - 2047.5f) / 2047.5f;
  float joyY = (analogRead(JOY_Y) - 2047.5f) / 2047.5f;

  switch (currFrame) {
    case INITGAME:
      drawButton(42, SCREEN_HEIGHT / 2, "HOST", 1, isHost);
      drawButton(85, SCREEN_HEIGHT / 2, "JOIN", 1, !isHost);
      if (analogRead(JOY_X) > (3.0f * 4096.0f / 4.0f) && (millis() - lastToggle > 200)) {
        lastToggle = millis();
        isHost = false;
      }
      if (analogRead(JOY_X) < (4096.0f / 4.0f) && (millis() - lastToggle > 200)) {
        lastToggle = millis();
        isHost = true;
      }
      if ((digitalRead(ENC_SW) == LOW || digitalRead(JOY_SW) == LOW) && (millis() - lastToggle > 200)) {
        Serial.println(".");
        currFrame = LOBBY;
        isInit = false;
        lastToggle = millis();
      }
      break;
    
    case LOBBY:
      if (isHost) {
        if (!isInit)
          InitLobby(party);
        uint8_t m[6];
        WiFi.macAddress(m);
        char pCode[5];
        party.toCharArray(pCode, 5);
        memcpy(&pkt.mac, m, 6);
        strncpy(pkt.payload, pCode, sizeof(pkt.payload));
        pkt.payload[sizeof(pkt.payload) - 1] = '\0';
        pkt.type = 0;
        broadcast(pkt);
        drawText(SCREEN_WIDTH/2, 10, "Lobby Code: " + party, 1, true);
        for (int i = 0; i < LEN(players); i++) {
          if (players[i].id == -1)
            drawText(i%2 * 54 + 37, i/2 * 15 + 30, "___", 1, true);
          else
            drawText(i%2 * 54 + 37, i/2 * 15 + 30, "ID0"+String(players[i].id), 1, true);
        }
      } else {
        if (!isInit) {
          codeInput.begin();
          isInit = true;
        }
        drawText(SCREEN_WIDTH/2, 10, "Enter Code:", 1, true);
        codeInput.update();
        codeInput.draw();
        if (analogRead(JOY_Y) > (3.0f * 4096.0f / 4.0f) && (millis() - lastToggle > 200)) {
          lastToggle = millis();
          codeInput.end();
          onJoin = true;
        }
        if (analogRead(JOY_Y) < (4096.0f / 4.0f) && (millis() - lastToggle > 200)) {
          lastToggle = millis();
          codeInput.begin();
          onJoin = false;
        }
        if ((digitalRead(ENC_SW) == LOW || digitalRead(JOY_SW) == LOW) && (millis() - lastToggle > 200)) {
          lastToggle = millis();
          if (onJoin) {
            currFrame = GAME;
            isInit = false;
          }
        }
        drawButton(SCREEN_WIDTH / 2, 50, "JOIN", 1, onJoin);
      }
      break;
    
    case GAME:
      if (!isInit) {
        // 
      }
      break;
  }

  display.display();
}