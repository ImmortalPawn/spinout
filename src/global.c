#include "global.h"

int window_width = 800;
int window_height = 600;

int timer_game_begin = 0;
int is_active_timer_game_begin = 1;

int timer_car_move = 1;
int is_active_timer_car_move = 0;

float car_rot = 0;
float car_speed = 0;
float car_z_pos = 0;
float car_y_pos = 0; 


void print_car_speed()
{
	printf("Car speed: %f\n", car_speed);
}
