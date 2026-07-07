#include <Wire.h>
#include <Adafruit_GFX.h>
#include <String.h>

// #define SMOL
#define BIG

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

// ENC PINS
#define ENC_CLK 18
#define ENC_DT 19
#define ENC_SW 23

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
    display.setCursor(_x - _w, _y - _h);
    display.println(text.substring(0, _cIdx) + _c + text.substring(_cIdx + 1));
    display.setCursor(_x - _w, _y - _h + _size+1);
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

TextInput t(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 5, 'A');

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

  pinMode(ENC_CLK, INPUT_PULLUP);
  pinMode(ENC_DT, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);

  pinMode(JOY_SW, INPUT_PULLUP);
  pinMode(JOY_X, INPUT_PULLUP);
  pinMode(JOY_Y, INPUT_PULLUP);

  t.begin();
}

int lastSwPress = millis();

void loop() {
  display.clearDisplay();

  t.update();
  t.draw();

  // go back
  if (digitalRead(JOY_SW) == HIGH && (millis() - lastSwPress > 200)) {
    lastSwPress = millis();
    Serial.println(t.getText());
  }

  display.display();
}