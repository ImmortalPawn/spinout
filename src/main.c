/* Game starting point. */

#include <stdlib.h>

#include "global.h"
#include "draw.h"
#include "init.h"
#include "callback.h"

int main(int argc, char** argv)
{
    /* Initialize global variables. */
    initGlobalVars(argc, argv);

    /* Initialize GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Initialize/Create window. */
    glutInitWindowSize(300, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Initialize OpenGL. */ 
    initOpenGl();

    /* Callback functions. */
    glutKeyboardFunc(onKeyboard);
    glutReshapeFunc(onReshape);
    glutDisplayFunc(onDisplay);

    /* Main loop. */
    glutMainLoop();

    exit(EXIT_SUCCESS);
}