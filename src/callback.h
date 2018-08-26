/* Callback and timer functions. */

#ifndef _CALLBACK_H
#define _CALLBACK_H

/* Callback functions. */
void onKeyboard(unsigned char key, int x, int y);
void onReshape(int width, int height);
void onDisplay(void);

/* Timer function. */
void onTimer(int timerId);

#endif