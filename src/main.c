#include "global.h"
#include "callback.h"
#include "init.h"

int main(int argc, char **argv)
{
    /* GLUT init. */
	init_GLUT(&argc, argv);

    /* Create window. */
	init_window();

    /* Listening for callback functions. */
    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);

    /* Init window configuration. */
    init_GL();

	/* Enter main loop. */
    glutMainLoop();

    return 0;
}
