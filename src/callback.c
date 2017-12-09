#include "callback.h"

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
		case 27:
			/* ESC button - exiting game. */
			exit(0);
			break;
	}

	/* FIXME glutPostRedisplay(); ubaci kada bude imalo iscrtavanja */
}

void on_display(void)
{
    /* Clear previous buffer color. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Set viewport. */
	glViewport(0, 0, window_width, window_height);

	init_projection();
	
	init_pov();
	
	draw_car();
	
    /* Send new picutre to window. */
    glutSwapBuffers();
}

void on_reshape(int width, int height)
{
	/* Adjusting window width & height. */
	window_width = width;
	window_height = height;
}
