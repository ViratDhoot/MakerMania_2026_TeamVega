#include "TextInput.h"

TextInput::TextInput(int x, int y, int size, int max_length, bool num)
  : _x(x),
    _y(y),
    _size(size),
    _off(0),
    _prevSt(digitalRead(ENC_CLK)),
    _cIdx(0),
    _buttonTick(millis()),
    text(""), 
    _maxLen(max_length), 
    _isNum(num)
{
  for (int i = 0; i < _maxLen; i++)
    text += (_isNum)?'0':'A';
  int16_t xPos, yPos;
  uint16_t w, h;
  display.gfx().setTextSize(_size);
  display.gfx().getTextBounds(text, 0, 0, &xPos, &yPos, &w, &h);
  _x -= w / 2;
  _y -= h / 2;
};

void TextInput::begin() {
  activeInput = this;
  attachInterrupt(
    digitalPinToInterrupt(ENC_CLK),
    encoderISR,
    CHANGE
  );
}

void TextInput::handleEncoder() {
  bool currSt = digitalRead(ENC_CLK);
  bool dtSt = digitalRead(ENC_DT);

  if (currSt != _prevSt) {
    if (dtSt != currSt)
      _off = min(_off+1, (_isNum)?9:25);
    else
      _off = max(_off-1, 0);
    _prevSt = currSt;
  }
}

void TextInput::update() {
  if (analogRead(JOY_X) > (3.0f * 4096.0f / 4.0f) && (millis() - _buttonTick > 200)) {
    _buttonTick = millis();
    if (_cIdx < _maxLen - 1) {
      _cIdx++;
      if (_cIdx < text.length())
        _off = text[_cIdx] - (_isNum?'0':'A');
    }
  }
    
  // go back
  if (analogRead(JOY_X) < (4096.0f / 4.0f) && (millis() - _buttonTick > 200)) {
    _buttonTick = millis();
    if (_cIdx > 0) {
      _cIdx--;
      _off = text[_cIdx] - (_isNum?'0':'A');
    }
  }

  text[_cIdx] = (_isNum?'0':'A') + _off;
}

void TextInput::end() {
  detachInterrupt(digitalPinToInterrupt(ENC_CLK));
  if (activeInput == this)
    activeInput = nullptr;
}

void TextInput::draw() {
  display.gfx().setTextSize(_size);
  display.gfx().setTextColor(SWHITE);
  display.gfx().setCursor(_x, _y);
  display.gfx().println(text);
  display.gfx().setCursor(_x, _y + _size + 1);
  String sel = "";
  for (int i = 0; i < _cIdx; i++)
    sel += " ";
  sel += "_";
  display.gfx().println(sel);
}

String TextInput::getText(){
  return text;
}

void IRAM_ATTR encoderISR() {
  if (activeInput)
    activeInput->handleEncoder();
}

TextInput *activeInput = nullptr;