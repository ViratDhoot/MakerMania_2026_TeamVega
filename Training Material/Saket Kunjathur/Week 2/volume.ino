#define PIN 16

int pins[8] = { 19, 18, 5, 27, 26, 25, 17, 16};
void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 8; i++)
    pinMode(pins[i], OUTPUT);
}

void loop() {
  int vol = map(analogRead(33), 0, 4096, 0, 9);
  Serial.println(vol);
  for(int i = 0; i < vol; i++) {
    digitalWrite(pins[i], LOW);
  }
  for(int i = vol; i < 8; i++) {
    digitalWrite(pins[i], HIGH);
  }
}