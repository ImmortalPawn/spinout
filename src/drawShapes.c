#include "drawShapes.h"

void draw_car(void)
{
	glPushMatrix();
		glColor3f(1, 0, 0);
		glScalef(1, 1, 2);
		glutWireCube(0.2);
	glPopMatrix();
}
