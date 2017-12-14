#include "global.h"

int window_width = 800;
int window_height = 600;

int timer_game_begin = 0;
int is_active_timer_game_begin = 1;

unsigned char key_state[256];

float car_rot = 0;
float car_f_max_speed = 100;
float car_b_max_speed = -50;
float car_speed = 0;
float car_accel = 1;
float car_decel = 1.2;
float car_friction = 0.3;
float car_handbrake_decel = 20;
float car_z_pos = 0;
float car_y_pos = 0; 

void print_car_speed()
{
	printf("Car speed: %f\n", car_speed);
}
