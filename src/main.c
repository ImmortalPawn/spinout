#include "global.h"
#include "callback.h"
#include "init.h"

int main(int argc, char **argv)
{
    /* Initialize GLUT. */
	init_GLUT(&argc, argv);

    /* Create & initialize window. */
	init_window();

	glutIgnoreKeyRepeat(0);

    /* Listening for callback functions. */
    glutKeyboardFunc(on_keyboard_press);
	glutKeyboardUpFunc(on_keyboard_relase);
    glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);
	glutTimerFunc(50, on_timer, timer_game_begin);

    /* Initialize OpenGL configuration. */
    init_GL();

	/* Enter main loop. */
    glutMainLoop();

    return 0;
}
