#include "Display.h"

Display::Display() : _dsp(128, 64, &Wire, -1) {}

void Display::begin() {
    Wire.begin(21, 22);
    
#ifdef BIG
  _dsp.begin(0x3C, true);
#else
  _dsp.begin(SSD1306_SWITCHCAPVCC, 0x3C);
#endif
  clear();
  show();
}

void Display::clear() { _dsp.clearDisplay(); }
void Display::show()  { _dsp.display(); }

void Display::drawText(int x, int y, const char *text, int size, bool light) {
  int16_t px, py;
  uint16_t w, h;

  _dsp.setTextSize(size);
  _dsp.getTextBounds(text, 0, 0, &px, &py, &w, &h);
  px = x - (w / 2);
  py = y - (h / 2);
  if (light)
    _dsp.setTextColor(SWHITE);
  else
    _dsp.setTextColor(SBLACK);
  _dsp.setCursor(px, py);
  _dsp.println(text);
}

void Display::drawText(int x, int y, const String &text, int size, bool light) {
  drawText(x, y, text.c_str(), size, light);
}

void Display::drawButton(int x, int y, const char *text, int size, bool selected) {
  int16_t px, py;
  uint16_t w, h;

  _dsp.setTextSize(size);
  _dsp.getTextBounds(text, 0, 0, &px, &py, &w, &h);
  px = x - (w / 2);
  py = y - (h / 2);
  int m = 3; // margin
  if (selected) {
    _dsp.fillRoundRect(px-m, py - m, w + 2*m, h + 2 * m, 3, SWHITE);
    _dsp.setTextColor(SBLACK);
  } else {
    _dsp.setTextColor(SWHITE);
    _dsp.drawRoundRect(px-m, py - m, w + 2*m, h + 2 * m, 3, SWHITE);
  }
  _dsp.setCursor(px, py);
  _dsp.println(text);
}

void Display::drawButton(int x, int y, const String &text, int size, bool selected) {
  drawButton(x, y, text.c_str(), size, selected);
}

void Display::drawCenteredBitmap(const uint8_t *bitmap, int x, int y, int width, int height, uint16_t color) {
  int16_t _x = x - (width / 2);
  int16_t _y = y - (height / 2);
  _dsp.drawBitmap(_x, _y, bitmap, width, height, color);
}

void Display::drawErr(const NetEvent &err) {
  if (err.type == NO_ERR) return;
  drawText(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, err.info.msg, 1, true);
}

Display display;