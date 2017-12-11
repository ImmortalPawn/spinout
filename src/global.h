#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

extern int window_width;
extern int window_height;

/* Car rotation. */
extern float car_rot;

/* Flag for left_right_timer state. */
extern int is_active_left_right_timer;

/* Value for left_right timer. */
extern int left_right_timer;

#endif
