#include "callback.h"

void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
		case 27:
			/* ESC button - exit game. */
			exit(0);
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
