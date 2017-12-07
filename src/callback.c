#include "global.h"
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
    glClear(GL_COLOR_BUFFER_BIT);

    /* Send new picutre to window. */
    glutSwapBuffers();
}
