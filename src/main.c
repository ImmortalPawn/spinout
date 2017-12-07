#include "global.h"
#include "initialize.h"

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_display(void);

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

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* ESC button - exiting game. */
        exit(0);
        break;
	}

	/* FIXME glutPostRedisplay(); ubaci kada bude imalo iscrtavanja */
}

static void on_display(void)
{
    /* Clear previous buffer color. */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Send new picutre to window. */
    glutSwapBuffers();
}
