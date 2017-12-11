#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define PRINT_CAR_SPEED 1

/* Window width & height*/
extern int window_width;
extern int window_height;

/* Value for timer_game_begin */ 
extern int timer_game_begin;
/* Flag for timer_game_begin state. */
extern int is_active_timer_game_begin;

/* Value for timer_car_move. */
extern int timer_car_move;
/* Flag for timer_car_move state. */
extern int is_active_timer_car_move;

/* Car rotation. */
extern float car_rot;
/* Car speed atm. */
extern float car_speed;
/* Car coordinates. */
extern float car_z_pos;
extern float car_y_pos;

void print_car_speed();

#endif
