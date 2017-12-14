#include "drawShapes.h"

void draw_car(void)
{
	/* Reducing car speed by friction. */
	if (!key_state['w']) {
		if (car_speed - car_friction >= 0) {
			car_speed -= car_friction;
		}
		else if ((car_speed > 0) && (car_speed<car_friction)) {
			car_speed = 0;
		}
	}

#if PRINT_CAR_SPEED
		print_car_speed();
#endif

	/* Distance travel. */
	float car_dist_travel = car_speed / 1000;

	/* Defines UP as head of the car. */
	float car_rot_conf = car_rot + 90;

	/* Car pos on Z axis. */
	car_z_pos += car_dist_travel * cosf(car_rot_conf * DEG_TO_RAD);
	/* Car pos on Y axis. */
	car_y_pos += car_dist_travel * sinf(car_rot_conf * DEG_TO_RAD);

	glPushMatrix();
		glTranslatef(0, car_y_pos, -car_z_pos);
		glRotatef(car_rot, 1, 0, 0);
		glScalef(1, 2, 1);
		glColor3f(1, 0, 0);
		glutWireCube(0.2);
	glPopMatrix();
}
