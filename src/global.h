#ifndef _GLOBAL_H
#define _GLOBAL_H

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PRINT_CAR_SPEED 1

#ifndef M_PI
#define M_PI 3.1415926535
#endif

/* Degrees to radians. */
#define DEG_TO_RAD (1 / (180.0 / M_PI))
/* Radians to degrees. */
#define RAD_TO_DEG (180.0 * M_PI)

/* Window width & height*/
extern int window_width;
extern int window_height;

/* Value for timer_game_begin */ 
extern int timer_game_begin;
/* Flag for timer_game_begin state. */
extern int is_active_timer_game_begin;
/* Array for keyboard keys state. 1-pressed, 0-not pressed. */
extern unsigned char key_state[256];

/* Car rotation. */
float car_rot;
/* Car speed atm. */
extern float car_speed;
/* Max forward car speed. */
extern float car_f_max_speed;
/* Max backward car speed. */
extern float car_b_max_speed;
/* Car acceleration. */
extern float car_accel;
/* Car deceleration. (breaking). */
extern float car_decel;
/* Friction between car and terrain. */
extern float car_friction;
/* Car handbrake speed deceleration. */
extern float car_handbrake_decel;
/* Car coordinates. */
extern float car_z_pos;
extern float car_y_pos;

void print_car_speed();

#endif
