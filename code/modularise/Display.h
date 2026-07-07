#pragma once

#include <Adafruit_GFX.h>
#include <Wire.h>

#include "Config.h"

#define BIG
// #define SMOL

#ifdef BIG
#include <Adafruit_SH110X.h>
#endif

#ifdef SMOL
#include <Adafruit_SSD1306.h>
#endif

#ifdef BIG
using DisplayDriver = Adafruit_SH1106G;
#define SWHITE SH110X_WHITE
#define SBLACK SH110X_BLACK
#endif
#ifdef SMOL
using DisplayDriver = Adafruit_SSD1306;
#define SWHITE WHITE
#define SBLACK BLACK
#endif

class Display;
extern Display display;

class Display {
public:
  Display();
  void begin();
  void clear();
  void show();
  void drawText(int x, int y, const char *text, int size, bool light);
  void drawText(int x, int y, const String &text, int size, bool light);
  void drawButton(int x, int y, const char *text, int size, bool selected);
  void drawButton(int x, int y, const String &text, int size, bool selected);
  void drawErr(const ErrEvent &err);
  DisplayDriver& gfx() { return _dsp; };

private:
  DisplayDriver _dsp;
};