#include "drawShapes.h"

void draw_car(void)
{
	car_z_pos += car_speed / 1000;
	car_y_pos += car_speed / 1000;
	
	glPushMatrix();
		glTranslatef(0, car_y_pos, 0);
		glRotatef(car_rot, 1, 0, 0);
		glColor3f(1, 0, 0);
		glutSolidCube(0.2);
	glPopMatrix();
}
