#ifndef SCREENPOS_H
#define SCREENPOS_H
typedef struct {
  int x;
  int y;
} ScreenPos;
#endif

void set_screen_pos(ScreenPos* pos, int x, int y);

ScreenPos new_screen_pos();