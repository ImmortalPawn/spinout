#include "drawShapes.h"

void draw_car(void)
{
	glPushMatrix();
		glRotatef(car_rot, 1, 0, 0);
		glColor3f(1, 0, 0);
		glutSolidCube(0.2);
	glPopMatrix();
}
