#include "callback.h"

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
		case 27:
			/* ESC button - exit game. */
			exit(0);
			break;
		case 'a':
			car_rot += 15;
			break;
		case 'd':
			car_rot -= 15;
			break;
		case 'w':
			if (car_speed + 1 > 100) {
				car_speed = 100;
			}
			else {
				car_speed += 1;
			}
#if PRINT_CAR_SPEED
			print_car_speed();
#endif
			break;
		case 's':
			if (car_speed - 1 < -50) {
				car_speed = -50;
			}
			else {
				car_speed -= 1;
			}
#if PRINT_CAR_SPEED
			print_car_speed();
#endif
			break;
		case 32:
			/* SPACE button - handbrake. */
			if (car_speed > 0) {
				if (car_speed - 20 < 0) {
					car_speed = 0;
				}
				else {
					car_speed -= 20;
				}
			}
			else {
				if (car_speed + 20 > 0) {
					car_speed = 0;
				}
				else {
					car_speed += 20;
				}
			}
#if PRINT_CAR_SPEED
			print_car_speed();
#endif
			break;
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
