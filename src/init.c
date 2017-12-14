#include "init.h"

void init_GLUT(int* argc, char** argv)
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
}

void init_window(void)
{
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("spinout");
}

void init_GL(void)
{
	/* Background color. */
	glClearColor(.75, .75, .75, 0);

	/* Set line width. */
	glLineWidth(2);

	/* Depth buffer. */
	glEnable(GL_DEPTH_TEST);
}

void init_projection(void)
{
	glViewport(0, 0, window_width, window_height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
			60,
			window_width/(float)window_height,
			1, 5);
}

void init_pov(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
			3, 0, 0,
			0, 0, 0,
			0, 1, 0);
}
