#include "callback.h"

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
		case 27:
			/* ESC button - exit game. */
			exit(0);
			break;
		case 'a':
			glutTimerFunc(50, on_timer, 0);
			car_rot += 15;
			break;
		case 'd':
			glutTimerFunc(50, on_timer, 0);
			car_rot -= 15;
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

	if (is_active_left_right_timer) {
		glutTimerFunc(50, on_timer, left_right_timer);
	}
}
