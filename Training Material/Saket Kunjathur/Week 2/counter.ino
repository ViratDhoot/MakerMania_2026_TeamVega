#define PIN 16

int pins[8] = { 19, 18, 5, 27, 26, 25, 17, 16 };
void setup() {
  for (int i = 0; i < 8; i++)
    pinMode(pins[i], OUTPUT);
}

int count = 0;
int c;
void loop() {
  c = count;
  for (int i = 0; i < 8; i++) {
    if (c % 2 == 1)
      digitalWrite(pins[i], LOW);
    else
      digitalWrite(pins[i], HIGH);
    c /= 2;
  }
  count++;
  delay(analogRead(33));
}