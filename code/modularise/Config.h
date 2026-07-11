#pragma once

#define LEN(X) (sizeof(X) / sizeof(X[0]))

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define MAZE_H 50
#define MAZE_W 50

// MASKS
#define VISIT 0b10000
#define RIGHT 0b01000
#define LEFT 0b00100
#define TOP 0b00010
#define BOTTOM 0b00001

// ENC PINS
#define ENC_CLK 18
#define ENC_DT 19
#define ENC_SW 23

// JOYSTICK PINS
#define JOY_SW 27
#define JOY_X 32
#define JOY_Y 33

enum NetMode { IDLE, JOINING, WAITING, IN_GAME };
enum NetDisplay { NO_ERR, MESSAGE, ANIMATE_BOMB };

struct NetEvent {
  NetDisplay type = NO_ERR;
  union {
    char msg[256];
    uint8_t bombCoords[2];
  } info;
  unsigned long shownAt = 0;
  unsigned long duration = 2000;
};

extern uint8_t maze[MAZE_W][MAZE_H];
extern int8_t MAPPING[4][2];
extern uint8_t DIM[2];