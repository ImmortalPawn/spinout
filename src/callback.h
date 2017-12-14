#ifndef _CALLBACK_H
#define _CALLBACK_H 

#include "global.h"
#include "init.h"
#include "drawShapes.h"

void on_keyboard_press(unsigned char key, int x, int y);
void on_keyboard_relase(unsigned char key, int x, int y);
void on_keyboard(void);
void on_display(void);
void on_reshape(int width, int height);
void on_timer(int value);

#endif
