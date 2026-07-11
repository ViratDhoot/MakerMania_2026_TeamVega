#include "Config.h"
#include "Display.h"
#include "TextInput.h"
#include "Networking.h"
#include "Sprites.h"

#define CODE_LEN 5

Player myData = { 0, 0, 0 };

enum Screen {
  COVER, 
  INITGAME,
  LOBBY,
  WAIT_ROOM,
  GAME, 
  PODIUM
};

Screen currFrame;
Networking net;

bool isInit;
bool isHost;
bool onJoin;
bool isStart;
int lastToggle = millis();
float arrow[2];
uint32_t party;
TextInput codeInput(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, 5, true);
Packet pkt;

float speed = 1.0f;
int size = 2;

uint8_t maze[MAZE_W][MAZE_H] = {
  { 25, 26, 24, 25, 19, 18, 24, 24, 24, 24, 25, 18, 17, 27, 26, 24, 24, 24, 25, 18, 25, 19, 18, 25, 18, 25, 19, 18, 17, 26, 24, 25, 27, 27, 19, 19, 18, 25, 18, 24, 24, 24, 24, 24, 17, 27, 19, 18, 17, 26 },
  { 20, 29, 31, 23, 19, 26, 28, 28, 29, 23, 22, 24, 25, 22, 21, 23, 31, 23, 23, 27, 31, 19, 19, 23, 27, 23, 18, 24, 25, 23, 23, 22, 20, 20, 25, 18, 17, 30, 24, 29, 23, 22, 29, 30, 25, 23, 19, 18, 17, 30 },
  { 25, 22, 29, 18, 24, 20, 29, 23, 23, 18, 24, 29, 22, 24, 25, 26, 21, 19, 26, 28, 21, 19, 26, 25, 23, 27, 27, 23, 22, 24, 24, 24, 17, 27, 31, 18, 25, 23, 23, 23, 27, 18, 28, 21, 23, 19, 18, 24, 24, 28 },
  { 20, 25, 30, 25, 22, 25, 31, 19, 19, 27, 31, 23, 27, 31, 22, 20, 25, 18, 28, 21, 18, 24, 20, 20, 17, 22, 20, 24, 25, 23, 31, 22, 17, 30, 21, 19, 23, 19, 18, 24, 21, 19, 23, 27, 19, 27, 18, 29, 23, 22 },
  { 17, 22, 28, 29, 19, 22, 21, 19, 18, 20, 20, 17, 22, 21, 19, 18, 29, 18, 20, 25, 18, 28, 25, 18, 24, 17, 26, 29, 30, 17, 30, 25, 19, 23, 19, 19, 19, 18, 17, 23, 26, 25, 18, 21, 18, 29, 19, 23, 27, 18 },
  { 17, 27, 31, 30, 24, 24, 24, 24, 24, 25, 19, 19, 19, 19, 18, 25, 23, 18, 24, 28, 17, 30, 29, 19, 22, 24, 29, 22, 21, 26, 21, 23, 18, 25, 19, 19, 18, 17, 26, 17, 31, 31, 19, 19, 18, 20, 24, 24, 28, 24 },
  { 17, 22, 28, 21, 31, 23, 30, 28, 28, 29, 19, 19, 18, 25, 19, 23, 18, 25, 23, 31, 18, 28, 29, 18, 24, 29, 23, 19, 18, 21, 19, 18, 25, 23, 27, 18, 17, 19, 31, 19, 30, 20, 25, 19, 19, 26, 29, 22, 29, 22 },
  { 17, 27, 30, 24, 29, 26, 21, 31, 23, 31, 18, 25, 18, 29, 19, 19, 19, 30, 24, 21, 19, 23, 31, 18, 28, 29, 18, 24, 24, 25, 26, 25, 23, 18, 21, 18, 24, 17, 30, 24, 28, 24, 28, 25, 18, 21, 23, 26, 21, 18 },
  { 17, 22, 20, 28, 28, 29, 18, 28, 25, 23, 27, 23, 19, 23, 19, 18, 24, 21, 22, 25, 19, 18, 20, 24, 28, 28, 25, 31, 23, 22, 21, 22, 24, 24, 25, 18, 28, 25, 23, 30, 29, 31, 23, 23, 27, 18, 24, 29, 27, 26 },
  { 25, 26, 24, 29, 22, 28, 25, 30, 21, 18, 29, 27, 19, 27, 18, 25, 23, 19, 27, 31, 19, 27, 19, 22, 28, 29, 22, 21, 19, 19, 19, 19, 23, 23, 22, 24, 29, 31, 18, 20, 28, 29, 18, 25, 31, 19, 30, 20, 20, 20 },
  { 28, 29, 23, 31, 18, 28, 28, 29, 26, 25, 30, 21, 18, 20, 25, 31, 18, 24, 28, 20, 24, 21, 19, 18, 29, 23, 19, 27, 27, 26, 25, 18, 25, 18, 25, 22, 28, 29, 27, 18, 28, 21, 18, 20, 20, 24, 21, 19, 18, 24 },
  { 28, 21, 26, 20, 17, 22, 28, 28, 28, 20, 29, 27, 19, 27, 22, 29, 19, 22, 20, 24, 29, 18, 25, 27, 22, 25, 18, 20, 20, 29, 23, 18, 29, 19, 30, 25, 22, 20, 20, 24, 20, 25, 18, 25, 19, 31, 27, 19, 18, 28 },
  { 28, 24, 20, 24, 17, 19, 22, 20, 20, 25, 22, 21, 26, 29, 18, 21, 26, 25, 18, 28, 29, 19, 22, 21, 19, 23, 19, 19, 18, 21, 27, 19, 23, 18, 29, 22, 25, 19, 19, 23, 19, 23, 18, 29, 26, 20, 20, 25, 18, 28 },
  { 29, 31, 19, 31, 19, 18, 24, 24, 17, 30, 17, 26, 20, 29, 19, 26, 29, 31, 27, 23, 31, 19, 18, 17, 27, 18, 25, 27, 19, 18, 21, 19, 19, 18, 29, 27, 30, 24, 24, 24, 25, 18, 24, 28, 21, 18, 24, 29, 19, 22 },
  { 28, 20, 25, 23, 18, 25, 31, 23, 26, 29, 18, 29, 18, 20, 25, 22, 20, 20, 29, 18, 29, 18, 25, 18, 29, 19, 22, 21, 19, 18, 17, 27, 19, 26, 20, 28, 20, 29, 31, 23, 31, 19, 31, 23, 18, 24, 29, 22, 24, 24 },
  { 28, 24, 29, 18, 17, 22, 20, 24, 29, 23, 27, 23, 18, 17, 31, 19, 19, 26, 20, 25, 30, 25, 23, 27, 23, 27, 19, 18, 25, 19, 18, 29, 26, 20, 24, 21, 19, 22, 20, 24, 20, 24, 21, 19, 18, 29, 22, 25, 30, 28 },
  { 21, 22, 20, 17, 19, 19, 19, 31, 22, 17, 31, 27, 18, 24, 21, 27, 18, 28, 24, 20, 29, 22, 17, 23, 26, 28, 24, 24, 28, 17, 27, 22, 20, 25, 23, 27, 27, 27, 27, 30, 25, 23, 18, 17, 19, 31, 19, 30, 21, 22 },
  { 17, 19, 19, 27, 18, 24, 24, 29, 18, 25, 30, 21, 27, 31, 26, 21, 26, 29, 22, 17, 31, 19, 19, 26, 20, 21, 23, 22, 29, 27, 23, 27, 27, 23, 26, 20, 20, 28, 20, 21, 22, 25, 18, 25, 19, 23, 26, 28, 25, 26 },
  { 24, 24, 24, 28, 24, 29, 23, 31, 26, 28, 20, 25, 22, 20, 20, 17, 22, 29, 19, 26, 21, 27, 26, 21, 19, 27, 19, 19, 30, 21, 18, 20, 21, 18, 20, 24, 24, 20, 25, 27, 18, 29, 19, 31, 27, 18, 20, 28, 28, 20 },
  { 28, 28, 21, 30, 28, 28, 25, 30, 28, 20, 25, 23, 19, 27, 19, 27, 26, 29, 18, 21, 26, 20, 29, 18, 24, 29, 18, 17, 23, 27, 18, 24, 25, 27, 19, 31, 23, 19, 30, 21, 19, 30, 17, 22, 21, 19, 18, 21, 23, 18 },
  { 29, 31, 27, 23, 31, 22, 20, 20, 28, 24, 21, 26, 25, 31, 18, 28, 20, 29, 27, 18, 21, 18, 28, 17, 23, 31, 19, 19, 26, 29, 27, 31, 30, 29, 18, 21, 19, 18, 29, 18, 24, 20, 25, 19, 18, 25, 27, 19, 18, 24 },
  { 20, 20, 28, 25, 31, 18, 24, 25, 23, 30, 24, 28, 20, 29, 18, 20, 17, 30, 29, 26, 25, 18, 21, 18, 17, 31, 19, 26, 28, 20, 28, 28, 28, 21, 19, 18, 24, 24, 28, 25, 22, 25, 23, 27, 27, 30, 21, 19, 19, 22 },
  { 17, 27, 22, 28, 28, 25, 23, 31, 18, 20, 21, 31, 18, 21, 19, 27, 26, 28, 28, 21, 30, 25, 27, 27, 27, 31, 26, 20, 20, 17, 30, 20, 21, 19, 19, 18, 29, 22, 29, 31, 27, 23, 18, 28, 20, 29, 27, 26, 25, 18 },
  { 25, 22, 25, 22, 28, 28, 25, 31, 27, 18, 17, 23, 26, 17, 27, 30, 28, 20, 29, 18, 29, 23, 31, 31, 31, 31, 31, 27, 27, 18, 21, 19, 27, 18, 25, 19, 23, 18, 28, 28, 20, 24, 24, 29, 26, 20, 28, 21, 23, 18 },
  { 29, 26, 29, 18, 28, 28, 20, 20, 29, 27, 18, 25, 30, 24, 20, 20, 21, 26, 28, 25, 31, 18, 29, 31, 31, 31, 30, 28, 29, 27, 27, 18, 29, 27, 31, 27, 19, 18, 20, 29, 19, 31, 22, 20, 29, 26, 29, 19, 27, 18 },
  { 20, 28, 28, 17, 30, 29, 26, 25, 22, 29, 18, 20, 29, 31, 19, 27, 26, 28, 20, 28, 20, 24, 29, 31, 31, 31, 30, 28, 28, 28, 20, 24, 20, 28, 20, 29, 18, 17, 19, 31, 18, 21, 18, 24, 28, 20, 29, 26, 29, 26 },
  { 17, 30, 28, 17, 22, 20, 28, 20, 17, 31, 26, 17, 22, 21, 26, 28, 28, 29, 18, 29, 19, 31, 23, 23, 31, 31, 30, 20, 20, 29, 27, 23, 26, 28, 17, 31, 27, 18, 25, 23, 26, 17, 27, 22, 29, 26, 20, 28, 20, 28 },
  { 17, 30, 21, 26, 25, 19, 23, 18, 17, 30, 29, 27, 27, 18, 20, 28, 20, 29, 18, 21, 26, 29, 19, 26, 20, 20, 29, 27, 18, 28, 29, 18, 20, 20, 24, 28, 28, 17, 30, 17, 23, 19, 31, 18, 20, 21, 18, 29, 18, 28 },
  { 17, 31, 18, 20, 28, 17, 27, 19, 19, 30, 28, 28, 28, 17, 27, 31, 18, 29, 18, 25, 30, 21, 26, 21, 26, 25, 30, 21, 18, 28, 29, 27, 19, 19, 22, 28, 20, 25, 31, 27, 18, 25, 31, 27, 19, 19, 18, 21, 26, 28 },
  { 24, 29, 18, 24, 20, 25, 22, 17, 27, 30, 28, 20, 29, 18, 20, 29, 18, 29, 26, 28, 21, 26, 29, 18, 28, 20, 29, 19, 26, 20, 20, 29, 19, 18, 24, 29, 26, 20, 28, 28, 17, 30, 20, 29, 27, 19, 27, 18, 20, 28 },
  { 29, 23, 27, 31, 26, 20, 17, 19, 30, 28, 20, 25, 23, 27, 26, 20, 17, 30, 20, 29, 18, 20, 21, 26, 28, 24, 21, 26, 28, 25, 18, 21, 19, 26, 28, 20, 21, 26, 20, 20, 17, 30, 25, 30, 28, 24, 20, 17, 26, 28 },
  { 28, 25, 22, 20, 29, 27, 27, 18, 20, 21, 26, 29, 26, 20, 29, 26, 24, 28, 17, 31, 18, 24, 17, 30, 29, 31, 18, 20, 29, 31, 19, 27, 18, 29, 23, 26, 24, 21, 18, 17, 19, 30, 28, 28, 29, 23, 19, 18, 29, 30 },
  { 28, 29, 18, 24, 28, 28, 29, 27, 18, 25, 30, 20, 29, 18, 20, 21, 30, 21, 18, 29, 19, 22, 17, 22, 28, 21, 26, 17, 22, 21, 18, 29, 18, 29, 18, 29, 31, 19, 19, 19, 18, 28, 20, 28, 21, 18, 24, 17, 22, 28 },
  { 20, 28, 17, 31, 22, 28, 28, 20, 17, 30, 29, 18, 21, 27, 18, 25, 31, 18, 24, 29, 27, 27, 19, 18, 21, 26, 21, 19, 27, 19, 26, 21, 26, 28, 25, 30, 29, 26, 24, 25, 18, 20, 25, 31, 19, 26, 28, 17, 27, 22 },
  { 17, 30, 24, 29, 18, 28, 29, 19, 18, 28, 29, 27, 18, 21, 18, 28, 29, 18, 29, 30, 20, 21, 18, 17, 27, 30, 25, 18, 20, 17, 23, 26, 20, 20, 28, 20, 28, 21, 31, 31, 26, 24, 20, 20, 17, 31, 23, 26, 21, 18 },
  { 17, 30, 29, 23, 18, 28, 20, 25, 19, 30, 20, 29, 18, 17, 19, 30, 29, 18, 28, 21, 26, 25, 18, 17, 22, 29, 23, 19, 27, 19, 18, 20, 17, 27, 30, 17, 22, 24, 28, 20, 29, 23, 27, 26, 25, 23, 26, 29, 26, 24 },
  { 25, 22, 29, 27, 18, 29, 18, 28, 25, 23, 26, 29, 27, 27, 18, 20, 21, 18, 29, 18, 29, 30, 25, 26, 24, 29, 27, 18, 21, 18, 25, 26, 24, 20, 21, 18, 25, 22, 21, 18, 21, 18, 20, 20, 29, 18, 20, 28, 29, 30 },
  { 20, 24, 28, 28, 17, 30, 17, 22, 20, 24, 20, 28, 28, 29, 27, 18, 24, 17, 23, 26, 20, 29, 22, 21, 30, 28, 21, 26, 25, 19, 22, 20, 21, 27, 18, 25, 23, 18, 24, 25, 18, 17, 27, 18, 20, 24, 17, 22, 28, 20 },
  { 17, 23, 22, 20, 24, 28, 24, 17, 27, 31, 19, 30, 28, 20, 20, 17, 30, 24, 25, 31, 18, 20, 25, 27, 22, 28, 25, 23, 23, 27, 27, 19, 18, 28, 24, 29, 27, 27, 23, 30, 25, 27, 23, 19, 27, 30, 17, 19, 31, 18 },
  { 24, 24, 24, 24, 29, 31, 31, 18, 28, 21, 18, 28, 29, 18, 25, 19, 31, 31, 30, 20, 25, 27, 30, 20, 17, 30, 29, 26, 17, 30, 29, 26, 25, 31, 23, 22, 20, 20, 24, 21, 30, 21, 27, 18, 28, 28, 17, 27, 31, 26 },
  { 29, 31, 23, 31, 30, 28, 29, 26, 21, 26, 25, 30, 20, 24, 29, 26, 20, 28, 29, 26, 28, 20, 29, 18, 25, 22, 20, 28, 25, 30, 28, 21, 30, 20, 25, 18, 24, 24, 29, 18, 29, 18, 21, 18, 20, 20, 17, 22, 28, 20 },
  { 28, 20, 17, 30, 28, 20, 28, 28, 17, 30, 28, 21, 26, 29, 22, 28, 24, 20, 28, 20, 20, 17, 22, 25, 23, 27, 26, 28, 20, 20, 20, 17, 31, 27, 30, 24, 29, 22, 29, 18, 21, 27, 19, 19, 19, 19, 18, 17, 23, 26 },
  { 29, 18, 17, 22, 28, 17, 30, 28, 17, 30, 29, 18, 28, 29, 18, 29, 31, 26, 21, 19, 27, 18, 17, 23, 26, 20, 28, 21, 19, 27, 18, 17, 30, 28, 29, 30, 29, 18, 29, 18, 24, 21, 18, 25, 18, 17, 26, 24, 17, 30 },
  { 20, 25, 27, 19, 30, 25, 30, 29, 18, 28, 28, 25, 30, 21, 26, 20, 28, 21, 18, 25, 23, 26, 25, 19, 31, 18, 29, 27, 26, 21, 18, 17, 30, 20, 20, 29, 23, 19, 22, 24, 29, 19, 19, 30, 24, 24, 28, 21, 19, 30 },
  { 17, 30, 20, 17, 30, 28, 28, 21, 26, 28, 20, 20, 20, 17, 31, 18, 29, 26, 24, 20, 25, 30, 21, 18, 20, 17, 22, 20, 28, 25, 19, 27, 31, 26, 25, 31, 19, 19, 27, 31, 23, 27, 18, 21, 23, 23, 30, 17, 19, 22 },
  { 17, 31, 27, 18, 28, 20, 29, 26, 20, 29, 27, 19, 18, 24, 28, 17, 30, 28, 29, 19, 30, 29, 27, 27, 19, 18, 24, 24, 20, 28, 17, 30, 28, 20, 20, 29, 26, 17, 30, 29, 18, 20, 24, 25, 18, 24, 20, 25, 19, 26 },
  { 24, 28, 28, 25, 30, 25, 30, 21, 26, 20, 21, 26, 25, 23, 31, 18, 28, 20, 28, 17, 30, 28, 20, 29, 19, 27, 22, 29, 26, 20, 17, 30, 29, 27, 18, 20, 29, 26, 28, 29, 19, 19, 31, 31, 27, 23, 19, 31, 18, 28 },
  { 21, 30, 20, 28, 20, 20, 29, 26, 21, 26, 24, 20, 20, 24, 29, 18, 28, 25, 22, 25, 30, 20, 25, 23, 26, 29, 19, 30, 21, 18, 25, 22, 28, 21, 19, 26, 20, 28, 20, 29, 18, 17, 22, 28, 21, 19, 18, 29, 26, 28 },
  { 17, 23, 18, 28, 17, 27, 30, 29, 18, 21, 22, 25, 19, 31, 23, 26, 28, 28, 17, 30, 21, 26, 21, 18, 20, 28, 17, 31, 18, 24, 29, 18, 21, 27, 18, 28, 25, 30, 25, 31, 19, 27, 18, 21, 27, 27, 18, 28, 20, 28 },
  { 17, 19, 19, 23, 18, 20, 20, 21, 19, 19, 18, 21, 18, 20, 17, 22, 20, 20, 17, 22, 17, 22, 17, 19, 19, 23, 18, 21, 19, 22, 21, 19, 18, 20, 17, 22, 20, 20, 20, 21, 18, 21, 19, 18, 20, 21, 18, 21, 18, 20 }
};

uint8_t DIM[2] = { 10, 10 };

void drawMaze(uint8_t maze[MAZE_W][MAZE_H], int ix, int iy) {
  int x = (SCREEN_WIDTH / 2) - ix;
  int y = (SCREEN_HEIGHT / 2) - iy;

  uint8_t cell, cx, cy;

  for (int i = max((ix / DIM[0]) - 7, 0); i < min(MAZE_W, (ix / DIM[0]) + 7); i++) {
    for (int j = max((iy / DIM[1]) - 7, 0); j < min(MAZE_H, (iy / DIM[1]) + 7); j++) {
      cell = maze[i][j];
      cx = (i * DIM[0]) + x;
      cy = (j * DIM[1]) + y;
      if ((cell & TOP) == 0)
        display.gfx().drawLine(cx, cy, cx + DIM[0], cy, SWHITE);
      if ((cell & LEFT) == 0)
        display.gfx().drawLine(cx, cy, cx, cy + DIM[1], SWHITE);
      if (i == MAZE_W - 1)
        display.gfx().drawLine(cx + DIM[0], cy, cx + DIM[0], cy + DIM[1], SWHITE);
      if (j == MAZE_H - 1)
        display.gfx().drawLine(cx, cy + DIM[1], cx + DIM[0], cy + DIM[1], SWHITE);
    }
  }
}

void setup() {
  Serial.begin(9600);
  display.begin();

  pinMode(JOY_SW, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);

  currFrame = COVER;
  isInit = false;
  isHost = false;
  onJoin = false;
  isStart = false;
  lastToggle = millis();
  net.begin();
  
  netInstance = &net;
}

void loop() {
  display.clear();
  float joyX = (analogRead(JOY_X) - 2047.5f) / 2047.5f;
  float joyY = (analogRead(JOY_Y) - 2047.5f) / 2047.5f;

  display.drawErr(errEvent);

  if (errEvent.type != NO_ERR && millis() - errEvent.shownAt > errEvent.duration) {
    currFrame = INITGAME;
    isInit = false;
    isHost = false;
    net.setMode(IDLE);
    errEvent.type = NO_ERR;
  } else if (errEvent.type == NO_ERR) {
    switch (currFrame) {
      case COVER:
        display.gfx().drawBitmap(0, 3, logo_bitmap, 128, 26, SWHITE);
        display.drawButton(SCREEN_WIDTH / 2, 45, "Start", 1, true);
        if ((digitalRead(ENC_SW) == LOW || digitalRead(JOY_SW) == LOW) && (millis() - lastToggle > 200)) {
          currFrame = INITGAME;
          isInit = false;
          lastToggle = millis();
        }
        break;

      case INITGAME:
        display.drawButton(42, SCREEN_HEIGHT / 2, "HOST", 1, isHost);
        display.drawButton(85, SCREEN_HEIGHT / 2, "JOIN", 1, !isHost);
        if (analogRead(JOY_X) > (3.0f * 4096.0f / 4.0f) && (millis() - lastToggle > 200)) {
          lastToggle = millis();
          isHost = false;
        }
        if (analogRead(JOY_X) < (4096.0f / 4.0f) && (millis() - lastToggle > 200)) {
          lastToggle = millis();
          isHost = true;
        }
        if ((digitalRead(ENC_SW) == LOW || digitalRead(JOY_SW) == LOW) && (millis() - lastToggle > 200)) {
          currFrame = LOBBY;
          isInit = false;
          lastToggle = millis();
        }
        break;

      case LOBBY:
        if (isHost) {
          if (!isInit) {
            party = random(0, 99999);
            net.genBeacon(party);
            net.resetData();
            net.setMode(JOINING);
            isInit = true;
          }
          net.sendBeacon();
          display.drawText(SCREEN_WIDTH / 2, 10, "Lobby Code: " + String(party), 1, true);
          display.drawText(22, 30, net._me.id, 1, true);
          for(int i = 0; i < NUM_PLAYERS - 1; i++) {
            if (!net.getPlayer(i).isActive)
              display.drawText((i + 1) * 28 + 22, 30, "___", 1, true);
            else
              display.drawText((i + 1) * 28 + 22, 30, String(net.getPlayer(i).status.id), 1, true);
          }
          if (analogRead(JOY_X) > (3.0f * 4096.0f / 4.0f) && (millis() - lastToggle > 200)) {
            lastToggle = millis();
            isStart = false;
          }
          if (analogRead(JOY_X) < (4096.0f / 4.0f) && (millis() - lastToggle > 200)) {
            lastToggle = millis();
            isStart = true;
          }
          if ((digitalRead(ENC_SW) == LOW || digitalRead(JOY_SW) == LOW) && (millis() - lastToggle > 200)) {
            lastToggle = millis();
            if (isStart) {
              net.startGame();
              net.setMode(IN_GAME);
              currFrame = GAME;
              isInit = false;
            } else {
              net.setMode(IDLE);
              currFrame = INITGAME;
            }
          }
          display.drawButton(SCREEN_WIDTH / 4, 55, "START", 1, isStart);
          display.drawButton(3 * SCREEN_WIDTH / 4, 55, "BACK", 1, !isStart);
          net.hostHeartbeat();
          net.checkHeartbeat();
        } else {
          if (!isInit) {
            codeInput.begin();
            net.resetData();
            isInit = true;
          }
          display.drawText(SCREEN_WIDTH / 2, 10, "Enter Code:", 1, true);
          codeInput.update();
          codeInput.draw();
          if (analogRead(JOY_Y) > (3.0f * 4096.0f / 4.0f) && (millis() - lastToggle > 200)) {
            lastToggle = millis();
            codeInput.end();
            onJoin = true;
          }
          if (analogRead(JOY_Y) < (4096.0f / 4.0f) && (millis() - lastToggle > 200)) {
            lastToggle = millis();
            codeInput.active();
            onJoin = false;
          }
          if ((digitalRead(ENC_SW) == LOW || digitalRead(JOY_SW) == LOW) && (millis() - lastToggle > 200)) {
            lastToggle = millis();
            if (onJoin) {
              party = codeInput.getText().toInt();
              net.setJoinCode(party);
              net.setMode(JOINING);
              currFrame = WAIT_ROOM;
              isInit = false;
            }
          }
          display.drawButton(SCREEN_WIDTH / 2, 50, "JOIN", 1, onJoin);
        }
        break;

      case WAIT_ROOM:
        if (!isInit) {
          //
        }
        display.drawText(SCREEN_WIDTH / 2, 10, "Lobby Code: " + String(party), 1, true);
        display.drawText(22, 30, net._me.id, 1, true);
        for (int i = 0; i < NUM_PLAYERS - 1; i++) {
          if (!net.getPlayer(i).isActive)
            display.drawText((i + 1) * 28 + 22, 30, "___", 1, true);
          else
            display.drawText((i + 1) * 28 + 22, 30, String(net.getPlayer(i).status.id), 1, true);
        }
        net.heartbeat();
        net.checkHostHeartbeat();
        if (net.getMode() == IN_GAME) {
          currFrame = GAME;
          isInit = false;
        }
        break;

      case GAME: {
        if (!isInit) {
          net.lastBomb = millis();
          isInit = true;
        }
        if (isHost) {
          net.hostHeartbeat();
          net.checkHeartbeat();
        } else {
          net.heartbeat();
          net.checkHostHeartbeat();
        }
        
        int ix = int(net._me.x / DIM[0]);
        int iy = int(net._me.y / DIM[1]);
        
        ix = constrain(ix, 0, MAZE_W - 1);
        iy = constrain(iy, 0, MAZE_H - 1);
        
        int cell = maze[ix][iy];
        if (((cell & LEFT) == 0) && ((net._me.x - size) < (ix * DIM[0] + 1)))
        net._me.x = ix * DIM[0] + size + 1;
        if (((cell & RIGHT) == 0) && ((net._me.x + size) > ((ix + 1) * DIM[0] - 1)))
        net._me.x = (ix + 1) * DIM[0] - size - 1;
        if (((cell & TOP) == 0) && ((net._me.y - size) < (iy * DIM[1] + 1)))
        net._me.y = iy * DIM[1] + size + 1;
        if (((cell & BOTTOM) == 0) && ((net._me.y + size) > ((iy + 1) * DIM[1] - 1)))
        net._me.y = (iy + 1) * DIM[1] - size - 1;
        
        // Drawing maze
        drawMaze(maze, net.currFocus->x, net.currFocus->y);
        
        // drawing players
        display.gfx().fillCircle(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, size, SWHITE);
        int dx = net.currFocus->x - SCREEN_WIDTH / 2;
        int dy = net.currFocus->y - SCREEN_HEIGHT / 2;
        if (memcmp(net.currFocus->id, net._me.id, PLAYER_TAG+1) != 0) {
          display.gfx().fillCircle(
            net._me.x - dx, 
            net._me.y - dy, 
            size, 
            SWHITE
          );
        }
        for (int i = 0; i < NUM_PLAYERS - 1; i++) {
          const PlayerEntry player = net.getPlayer(i);
          if (!player.isActive) continue;
          if (memcmp(net.currFocus->id, player.status.id, PLAYER_TAG+1) == 0) continue;
          display.gfx().fillCircle(
            player.status.x - dx, 
            player.status.y - dy, 
            size, 
            SWHITE
          );
        }

        arrow[0] = MAZE_W / 2 - net.currFocus->x / DIM[0];
        arrow[1] = MAZE_H / 2 - net.currFocus->y / DIM[1];
        float mag = sqrt(arrow[0] * arrow[0] + arrow[1] * arrow[1]);

        if (mag > 3) {
          arrow[0] /= mag;
          arrow[1] /= mag;

          const int topMargin = 13 + 6;  // panel height + a little breathing room for the triangle itself
          const int bottomMargin = 6;
          const int sideMargin = 6;

          int cx = SCREEN_WIDTH / 2 + arrow[0] * (SCREEN_WIDTH / 2 - sideMargin);
          int cy = (SCREEN_HEIGHT + topMargin) / 2 + arrow[1] * ((SCREEN_HEIGHT - topMargin) / 2 - bottomMargin);

          const int len = 3;
          const int wing = 3;

          int tipX  = cx + arrow[0] * len;
          int tipY  = cy + arrow[1] * len;
          int backX = cx - arrow[0] * len;
          int backY = cy - arrow[1] * len;

          int rightX = backX - arrow[1] * wing;
          int rightY = backY + arrow[0] * wing;
          int leftX  = backX + arrow[1] * wing;
          int leftY  = backY - arrow[0] * wing;

          display.gfx().fillTriangle(tipX, tipY, rightX, rightY, leftX, leftY, SWHITE);
        }

        // Drawing crosshair
        if (memcmp(net.currFocus->id, net._me.id, PLAYER_TAG+1) != 0) {
          int cX = net.crosshair_x * DIM[0] - dx;
          int cY = net.crosshair_y * DIM[1] - dy;
          display.gfx().drawLine(cX + 2, cY + 2, cX + 3, cY + 2, SWHITE);
          display.gfx().drawLine(cX + 2, cY + 2, cX + 2, cY + 3, SWHITE);
          display.gfx().drawLine(cX + DIM[0] - 2, cY + 2, cX + DIM[0] - 3, cY + 2, SWHITE);
          display.gfx().drawLine(cX + DIM[0] - 2, cY + 2, cX + DIM[0] - 2, cY + 3, SWHITE);
          display.gfx().drawLine(cX + 2, cY + DIM[1] - 2, cX + 3, cY + DIM[1] - 2, SWHITE);
          display.gfx().drawLine(cX + 2, cY + DIM[1] - 2, cX + 2, cY + DIM[1] - 3, SWHITE);
          display.gfx().drawLine(cX + DIM[0] - 2, cY + DIM[1] - 2, cX + DIM[0] - 3, cY + DIM[1] - 2, SWHITE);
          display.gfx().drawLine(cX + DIM[0] - 2, cY + DIM[1] - 2, cX + DIM[0] - 2, cY + DIM[1] - 3, SWHITE);
        }

        if (displayEvent.type == ANIMATE_BOMB) {
          if ((millis() - displayEvent.shownAt) >= displayEvent.duration) displayEvent.type = NO_ERR;
          int frame = (int)((millis() - displayEvent.shownAt) / 100);
          frame = constrain(frame, 0, EXPL_FRAMES - 1);
          if (frame >= 3) {
            if (
              !net.isJammed && 
              (abs(ix - displayEvent.info.bombCoords[0]) + abs(iy - displayEvent.info.bombCoords[1]) <= 2)
            ) {
              net.jammed = millis();
              net.isJammed = true;
            }
          }
          display.drawCenteredBitmap(
            expl_frames_bitmap[frame], 
            displayEvent.info.bombCoords[0] * DIM[0] + DIM[0] / 2.0 - dx, 
            displayEvent.info.bombCoords[1] * DIM[1] + DIM[1] / 2.0 - dy, 
            BOMB_WIDTH, 
            BOMB_HEIGHT, 
            SWHITE
          );
        }

        if (abs(joyX) < 0.15f) joyX = 0;
        
        if (abs(joyY) < 0.15f) joyY = 0;
        
        if (memcmp(net.currFocus->id, net._me.id, PLAYER_TAG+1) == 0) {
          if (net.isJammed) {
            if (millis() - net.jammed > JAM_TIMEOUT) net.isJammed = false;
            display.drawButton(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, "CONTROLS JAMMED", 1, true);
          } else {
            net._me.x += joyX * speed;
            net._me.y += joyY * speed;
          }
        } else {
          
          if (joyX > 0.6 && (millis() - lastToggle > 200)) {
            net.crosshair_x++;
            lastToggle = millis();
          } else if (joyX < -0.6 && (millis() - lastToggle > 200)) {
            net.crosshair_x--;
            lastToggle = millis();
          };
          net.crosshair_x = constrain(net.crosshair_x, 0, MAZE_W-1);
          if (joyY > 0.6 && (millis() - lastToggle > 200)) {
            net.crosshair_y++;
            lastToggle = millis();
          } else if (joyY < -0.6 && (millis() - lastToggle > 200)) {
            net.crosshair_y--;
            lastToggle = millis();
          };
          net.crosshair_y = constrain(net.crosshair_y, 0, MAZE_W-1);
          if ((digitalRead(ENC_SW) == LOW || digitalRead(JOY_SW) == LOW) && (millis() - lastToggle > 200)) {
            net.sendBomb(net.currFocus->id);
            net.lastBomb = millis();
            net.currFocus = &net._me;
            lastToggle = millis();
          }
        }

        // Drawing INFO Palette
        display.gfx().fillRect(0, 0, SCREEN_WIDTH, 12, SBLACK);
        display.gfx().drawLine(0, 12, SCREEN_WIDTH, 12, SWHITE);
        display.drawText(15, 6, net.currFocus->id, 1, true);
        display.gfx().drawRoundRect(64, 2, 63, 8, 10, SWHITE);
        float barLoad = constrain(((millis() - net.lastBomb) * 59.0) / BOMB_TIMEOUT, 0.0, 59.0);
        display.gfx().fillRoundRect(66, 4, barLoad, 4, 10, SWHITE);
        display.drawCenteredBitmap(bomb_bitmap, SCREEN_WIDTH/2 - 5, 6, 9, 9, SWHITE);

        net.pollData();

        if (
          ((net._me.x/DIM[0]) >= 22 && (net._me.x/DIM[0]) <= 26) && 
          (net._me.y/DIM[1]) >= 22 && (net._me.y/DIM[1]) <= 26
        ) {
          net.sendWon(); // Add a spectate mode later on
        }
        if ((digitalRead(ENC_SW) == LOW || digitalRead(JOY_SW) == LOW) && (millis() - lastToggle > 200)) {
          Serial.println(net._me.x);
          Serial.println(net._me.y);
        }

        if (net.getMode() == LEADERBOARD) {
          currFrame = PODIUM;
        }

        break;
      }
      case PODIUM: {
        display.drawText(SCREEN_WIDTH / 2, 8, "LEADERBOARD", 1, true);

        int maxHeight = 10;
        int barWidth = SCREEN_WIDTH / NUM_PLAYERS - 10;
        int baseY = SCREEN_HEIGHT - 20;

        for (int rank = 0; rank < NUM_PLAYERS; rank++) {
          const Player* winner = net.getWinner(rank);
          
          int podiumX = (SCREEN_WIDTH * (2 * rank + 1)) / (2 * NUM_PLAYERS);
          int barHeight = 12 + ((maxHeight * (NUM_PLAYERS - rank)) / NUM_PLAYERS);
          int barTop = baseY - barHeight;
          
          display.gfx().drawRect(podiumX - barWidth / 2, barTop, barWidth, barHeight, SWHITE);
          display.drawText(podiumX, barTop + barHeight / 2, String(rank + 1), 1, true);
          if (winner == nullptr) continue;
          display.drawText(podiumX, barTop - 6, winner->id, 1, true);
        }
        
        if (isHost) {
          display.drawButton(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 10, "BACK TO LOBBY", 1, true);

          if ((digitalRead(ENC_SW) == LOW || digitalRead(JOY_SW) == LOW) && (millis() - lastToggle > 200)) {
            lastToggle = millis();
            net.playAgain();
          }
        }

        if (net.getMode() == WAITING) currFrame = WAIT_ROOM;
        if (net.getMode() == JOINING) currFrame = LOBBY;
        break;
      }
    }
  }
  display.show();
}