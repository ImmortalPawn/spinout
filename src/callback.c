#include "callback.h"

void on_keyboard_press(unsigned char key, int x, int y)
{
    switch (key) {
		case 27:
			/* ESC button - exit game. */
			exit(0);
			break;
		case 'a':
			key_state['a'] = 1;
			break;
		case 'd':
			key_state['d'] = 1;
			break;
		case 'w':
			key_state['w'] = 1;
			break;
		case 's':
			key_state['s'] = 1;
			break;
		case 32:
			key_state[32] = 1;
			break;
	}

	on_keyboard();
}

void on_keyboard_relase(unsigned char key, int x, int y)
{
	key_state[key] = 0;
}

void on_keyboard(void) 
{
	float car_rot_angle = car_speed / 15.0;

	if (key_state['w']) {

		if (car_speed + car_accel > 100) {
			car_speed = 100;
		}
		else {
			car_speed += car_accel;
		}
	}

	if (key_state['s']) {
		if (car_speed - car_decel < -50) {
			car_speed = -50;
		}
		else {
			car_speed -= car_decel;
		}
	}

	if (key_state['a']) {
		if (car_speed != 0) {
			car_rot += car_rot_angle;
		}
	}
	
	if (key_state['d']) {
		if (car_speed != 0) {
			car_rot -= car_rot_angle;
		}
	}

	if (key_state[32]) {
		/* SPACE button - handbrake. */
		if (car_speed > 0) {
			if (car_speed - car_handbrake_decel < 0) {
				car_speed = 0;
			}
			else {
				car_speed -= car_handbrake_decel;
			}
		}
		else {
			if (car_speed + car_handbrake_decel > 0) {
				car_speed = 0;
			}
			else {
				car_speed += car_handbrake_decel;
			}
		}
	}
}

void on_display(void)
{
    /* Clear previous buffer content. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Initialize point of view. */
	init_pov();
	
	draw_car();
	
    /* Send new content to window. */
    glutSwapBuffers();
}

void on_reshape(int width, int height)
{
	/* Adjust window width & height. */
	window_width = width;
	window_height = height;

	/* Initialize projection. */
	init_projection();
}

void on_timer(int value)
{
	/* Force window drawing. */
	glutPostRedisplay();

	if (is_active_timer_game_begin) {
		glutTimerFunc(50, on_timer, timer_game_begin);
	}

}
