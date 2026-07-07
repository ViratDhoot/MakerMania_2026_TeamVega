#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Screen Dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SWHITE SH110X_WHITE

// JOYSTICK PINS
#define JOY_SW 27
#define JOY_X 32
#define JOY_Y 33

typedef struct {
  float x;
  float y;
} vec2;

typedef struct {
  float x;
  float y;
  float z;
} vec3;

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Wire.begin(21, 22);
  display.begin(0x3C, true);
  display.clearDisplay();
  display.display();
  pinMode(JOY_SW, INPUT_PULLUP);
}

vec3 verts[8] = {
  {-0.5f, -0.5f, -0.5f}, 
  { 0.5f, -0.5f, -0.5f}, 
  { 0.5f,  0.5f, -0.5f}, 
  {-0.5f,  0.5f, -0.5f},
  {-0.5f, -0.5f,  0.5f}, 
  { 0.5f, -0.5f,  0.5f}, 
  { 0.5f,  0.5f,  0.5f}, 
  {-0.5f,  0.5f,  0.5f},
};

int edges[12][2] = {
  {0, 1}, {1, 2}, {2, 3}, {3, 0},
  {4, 5}, {5, 6}, {6, 7}, {7, 4},
  {0, 4}, {1, 5}, {2, 6}, {3, 7}
};

int fov = 128;

vec2 getCoords(vec3 coord) {
  float nx = coord.x / coord.z;
  float ny = coord.y / coord.z;
  float sx = (nx + 1.0f) * SCREEN_WIDTH  * 0.5f;
  float sy = (1.0f - ny) * SCREEN_HEIGHT * 0.5f;
  return { sx, sy };
}

void drawVerts(vec3 vertices[], int count, vec3 off) {
  for (int i = 0; i < count; i++) {
    auto [ x, y ] = getCoords(translate(vertices[i], off));
    display.fillCircle(
      x, 
      y, 
      3, SWHITE
    );
  }
}

void drawSides(vec3 vertices[], int order[][2], int count, vec3 off, vec3 axis, float angle) {
  for (int i = 0; i < count; i++) {
    vec3 c1 = translate(rot(vertices[order[i][0]], axis, angle), off);
    vec2 p1 = getCoords(c1);
    vec3 c2 = translate(rot(vertices[order[i][1]], axis, angle), off);
    vec2 p2 = getCoords(c2);
    display.drawLine(p1.x, p1.y, p2.x, p2.y, SWHITE);
  }
}

vec3 translate(vec3 coord, vec3 off) {
  return {coord.x + off.x, coord.y + off.y, coord.z + off.z};
}

vec3 rot(vec3 v, vec3 k, float a) {
  float mag = pow((pow(k.x, 2) + pow(k.y, 2) + pow(k.z, 2)), 0.5);
  k.x /= mag;
  k.y /= mag;
  k.z /= mag;

  float c = cos(a);
  float s = sin(a);

  vec3 cross = {
    k.y*v.z - k.z*v.y,
    k.z*v.x - k.x*v.z,
    k.x*v.y - k.y*v.x
  };

  float dot =
    k.x*v.x +
    k.y*v.y +
    k.z*v.z;

  return {
    v.x*c + cross.x*s + k.x*dot*(1-c),
    v.y*c + cross.y*s + k.y*dot*(1-c),
    v.z*c + cross.z*s + k.z*dot*(1-c)
  };
}

void loop() {
  display.clearDisplay();
  // drawVerts(verts, sizeof(verts) / sizeof(verts[0]), map(analogRead(JOY_X), 0, 4096, 0, 3));
  float joyX = (analogRead(JOY_X) - 2047.5f) / 2730.0f;
  float joyY = (2047.5 - analogRead(JOY_Y)) / 2730.0f;

  if (abs(joyX) < 0.10f)
    joyX = 0;

  if (abs(joyY) < 0.10f)
    joyY = 0;

  vec3 off = {
    joyX, 
    joyY, 
    2.0f
  };
  drawSides(verts, edges, sizeof(edges) / sizeof(edges[0]), off, { 0.0f, 1.0f, 1.0f }, (millis() / 10.0f));
  display.display();
}