#include <Wire.h>
#include <Adafruit_GFX.h>
#include <WiFi.h>
#include <esp_now.h>

// #define SMOL
#define BIG

// #ifdef BIG
// #define MAC_ADDR { 0x00, 0x70, 0x07, 0xE2, 0x06, 0x54 }
// #endif
// #ifdef SMOL
// #define MAC_ADDR { 0x70, 0x4B, 0xCA, 0x25, 0x1D, 0x7C }
// #endif

#define BROADCAST { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

typedef struct {
  uint8_t type; // 0 = BEACON, 1 = CONNECTION, 2 = ACKNOWLEDGEMENT
  uint8_t[3] lobbyCode;
  uint8_t[2] pass;
  uint8_t[6] mac;
} Packet;

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

// MASKS
#define VISIT 0b10000
#define RIGHT 0b01000
#define LEFT 0b00100
#define TOP 0b00010
#define BOTTOM 0b00001

// Maze Dimensions
#define MAZE_H 50
#define MAZE_W 50

// JOYSTICK PINS
#define JOY_SW 27
#define JOY_X 32
#define JOY_Y 33

#ifdef BIG
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#endif
#ifdef SMOL
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
#endif

uint8_t broadcastAddress[] = MAC_ADDR;

struct Player {
    int x;
    int y;
};

Player others[8];
int _playerCount = 0;

Player myData = { 0, 0 };

esp_now_peer_info_t peerInfo;

void OnDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) {
  if (status != ESP_NOW_SEND_SUCCESS)
    Serial.println("Delivery Fail");
}

Player otherData = {0, 0};
bool rec = false;

void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len) {
  memcpy(&otherData, incomingData, sizeof(otherData));
  Serial.print(otherData.x);
  Serial.print(", ");
  Serial.println(otherData.y);
  rec = true;
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
  display.clearDisplay();
  display.display();
  pinMode(JOY_SW, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ERROR initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

float x = 0.0f;
float y = 0.0f;
int dx;
int dy;

float speed = 1.0f;

void loop() {
  display.clearDisplay();
  float joyX = (analogRead(JOY_X) - 2047.5f) / 2047.5f;
  float joyY = (analogRead(JOY_Y) - 2047.5f) / 2047.5f;

  if (abs(joyX) < 0.15f)
    joyX = 0;

  if (abs(joyY) < 0.15f)
    joyY = 0;

  myData.x += joyX * speed;
  myData.y += joyY * speed;
  
  if (myData.x < 0) myData.x = 0;
  else if (myData.x > SCREEN_WIDTH) myData.x = SCREEN_WIDTH;
  if (myData.y < 0) myData.y = 0;
  else if (myData.y > SCREEN_HEIGHT) myData.y = SCREEN_HEIGHT;

  display.fillCircle(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 2, SWHITE);
  display.drawRect(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, SWHITE);

  dx = otherData.x - myData.x;
  dy = otherData.y - myData.y;

  float drawX = SCREEN_WIDTH / 2.0f + dx;
  float drawY = SCREEN_HEIGHT / 2.0f + dy;

  if (abs(dx) < SCREEN_WIDTH/4.0f && abs(dy)  <= SCREEN_HEIGHT/4.0f) {
      display.fillCircle(drawX, drawY, 2, SWHITE);
  }

  static unsigned long lastSend = 0;

  if (millis() - lastSend > 100) {
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

      if (result != ESP_OK)
        Serial.println("Sending error");
      lastSend = millis();
  }

  display.display();
}