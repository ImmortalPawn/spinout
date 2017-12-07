#include "global.h"
#include "initialize.h"
#include "callback.h"

int main(int argc, char **argv)
{
    /* GLUT init. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    /* Create window. */
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("spinout");

    /* Listening for callback funkctions. */
    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display);

    /* Init window configuration. */
    initialize();

	/* Enter main loop. */
    glutMainLoop();

    return 0;
}


