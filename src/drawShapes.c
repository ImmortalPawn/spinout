#include "drawShapes.h"

void draw_car(void)
{
	/* Distance travel. */
	float car_dist_travel = car_speed / 1000;

	/* Defines UP as head of the car. */
	int car_rot_conf = car_rot + 90;

	/* Car pos on Z axis. */
	car_z_pos += car_dist_travel * cosf(car_rot_conf * DEG_TO_RAD);
	/* Car pos on Y axis. */
	car_y_pos += car_dist_travel * sinf(car_rot_conf * DEG_TO_RAD);

	glPushMatrix();
		glTranslatef(0, car_y_pos, -car_z_pos);
		glRotatef(car_rot, 1, 0, 0);
		glColor3f(1, 0, 0);
		glutSolidCube(0.2);
	glPopMatrix();
}
