#pragma once

#include <Arduino.h>
#include "Display.h"
#include "Config.h"

class TextInput;
extern TextInput *activeInput;

void IRAM_ATTR encoderISR();

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
  bool _isAlpha;
  bool _isNum;

public:
  TextInput(int x, int y, int size, int max_length, bool num);
  void begin();
  void IRAM_ATTR handleEncoder();
  void update();
  void active() { activeInput = this; };
  void end();
  void draw();
  String getText();
};

