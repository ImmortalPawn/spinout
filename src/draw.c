#include "draw.h"
#include "global.h"

void drawAxis(void)
{
    glPushMatrix();

        glBegin(GL_LINES);
            /* X axis. */
            glColor3f(1.00f, 0.00f, 0.00f);
            glVertex3f(0.00f, 0.00f, 0.00f);
            glVertex3f(1.00f, 0.00f, 0.00f);

            /* Y axis. */
            glColor3f(0.00f, 1.00f, 0.00f);
            glVertex3f(0.00f, 0.00f, 0.00f);
            glVertex3f(0.00f, 1.00f, 0.00f);

            /* Z axis. */
            glColor3f(0.00f, 0.00f, 1.00f);
            glVertex3f(0.00f, 0.00f, 0.00f);
            glVertex3f(0.00f, 0.00f, 1.00f);
        glEnd();

    glPopMatrix();
}

void drawEdges()
{
    glPushMatrix();

        glLineWidth(5);

        glColor3f(1.00f, 0.00f, 0.00f);
        glBegin(GL_LINES);
            /* Left edge. */
            glVertex3f(-0.75f, -1.00f, 0.00f);
            glVertex3f(-0.75f, 1.00f, 0.00f);

            /* Right edge. */
            glVertex3f(0.75f, -1.00f, 0.00f);
            glVertex3f(0.75f, 1.00f, 0.00f);

            /* Bottom edge. */
            glVertex3f(-0.75f, -1.00f, 0.00f);
            glVertex3f(0.75f, -1.00f, 0.00f);

            /* Top edge. */
            glVertex3f(-0.75f, 1.00f, 0.00f);
            glVertex3f(0.75f, 1.00f, 0.00f);

            /* Left road line. */
            glVertex3f(-0.25f, -1.00f, 0.00f);
            glVertex3f(-0.25f, 1.00f, 0.00f);

            /* Right road line. */
            glVertex3f(0.25f, -1.00f, 0.00f);
            glVertex3f(0.25f, 1.00f, 0.00f);

        glEnd();

        glLineWidth(1);

    glPopMatrix();
}

void drawRoad(void)
{
    glColor3f(0.40f, 0.40f, 0.40f);
    glPushMatrix();
        glTranslatef(0.00f, 0.00f, -0.10f);
        glScalef(1.00f, 1.00f, 0.00f);
        glutSolidCube(2.00d);
    glPopMatrix();
}

void drawRoadLines(void)
{
    glColor3f(1.00f, 1.00f, 1.00f);

    for (int i = 0; i < linesNum; i++) {

        /* Draw left road lines. */
        glPushMatrix();
            glTranslatef(linesLX, lines[i].y, 0.00f);
            glScalef(lineScaleX, 1.00f, 0.00f);
            glutSolidCube(lineLength);
        glPopMatrix();

        /* Draw right road lines. */
        glPushMatrix();
            glTranslatef(linesRX, lines[i].y, 0.00f);
            glScalef(lineScaleX, 1.00f, 0.00f);
            glutSolidCube(lineLength);
        glPopMatrix();
    }
}

void drawBotCars(void)
{
    for (int i = 0; i < carsNum; i++) {

        /* Body. */ 
        glColor3f(1.00f, 0.00f, 0.00f); 
        glPushMatrix(); 
            glTranslatef(cars[i].x, cars[i].y, 0.01f);
            glScalef(carScaleX, 1.00f, 1.00f);
            glutSolidCube((GLdouble)carLength);
        glPopMatrix();

        /* Interior. */
        glColor3f(0.40f, 0.00f, 0.00f); 
        glPushMatrix(); 
            glTranslatef(cars[i].x, cars[i].y+carLength/9, 0.02f);
            glScalef(0.50f, 0.50f, 1.00f);
            glutSolidCube((GLdouble)carLength);
        glPopMatrix();

        /* Head. */
        glColor3f(0.44f, 0.43f, 0.23f); 
        glPushMatrix(); 
            glTranslatef(cars[i].x, cars[i].y+carLength/9, 0.03f);
            glScalef(0.50f, 0.50f, 1.00f);
            glutSolidSphere(0.10d, 50, 50);
        glPopMatrix();

        /* Wheels. */
        /* Top left. */
        glColor3f(0.00f, 0.00f, 0.00f); 
        glPushMatrix(); 
            glTranslatef(cars[i].x-carWidth/2, cars[i].y+carLength/3, 0.02f);
            glScalef(0.70f, 0.80f, 1.00f);
            glutSolidSphere((GLdouble)carWheelSize, 50, 50);
        glPopMatrix();

        /* Top right. */
        glPushMatrix(); 
            glTranslatef(cars[i].x+carWidth/2, cars[i].y+carLength/3, 0.02f);
            glScalef(0.70f, 0.80f, 1.00f);
            glutSolidSphere((GLdouble)carWheelSize, 50, 50);
        glPopMatrix();

        /* Bottom left. */
        glPushMatrix(); 
            glTranslatef(cars[i].x-carWidth/2, cars[i].y-carLength/3, 0.02f);
            glScalef(0.70f, 0.80f, 1.00f);
            glutSolidSphere((GLdouble)carWheelSize, 50, 50);
        glPopMatrix();

        /* Bottom right. */
        glPushMatrix(); 
            glTranslatef(cars[i].x+carWidth/2, cars[i].y-carLength/3, 0.02f);
            glScalef(0.70f, 0.80f, 1.00f);
            glutSolidSphere((GLdouble)carWheelSize, 50, 50);
        glPopMatrix();
    }

}

void drawCoins(void)
{
    for (int i = 0; i < coinsNum; i++) {

        if (coins[i].isActive) {

            glColor3f(0.88f, 0.91f, 0.20f);
            glPushMatrix();
                glTranslatef(coins[i].x, coins[i].y, 0.05f);

                if (coinRotation >= 360.00f) {

                    coinRotation = 0.00f;
                }

                glRotatef(coinRotation, 0.00f, 0.00f, 1.00f);
                glScalef(1.00f, coinScaleY, 1.00f);
                glutSolidSphere((GLdouble)coinSize, 50, 50);
            glPopMatrix();
        }
    }
}

void drawPlayer(void)
{

    /* Body. */ 
    glColor3f(0.00f, 0.00f, 1.00f); 
    glPushMatrix(); 
        glTranslatef(playerCarX, playerCarY, 0.01f);
        glScalef(carScaleX, 1.00f, 1.00f);
        glutSolidCube((GLdouble)carLength);
    glPopMatrix();

    /* Interior. */
    glColor3f(0.00f, 0.00f, 0.40f); 
    glPushMatrix(); 
        glTranslatef(playerCarX, playerCarY-carLength/9, 0.02f);
        glScalef(0.50f, 0.50f, 1.00f);
        glutSolidCube((GLdouble)carLength);
    glPopMatrix();

    /* Head. */
    glColor3f(0.44f, 0.43f, 0.23f); 
    glPushMatrix(); 
        glTranslatef(playerCarX, playerCarY-carLength/9, 0.03f);
        glScalef(0.50f, 0.50f, 1.00f);
        glutSolidSphere(0.10d, 50, 50);
    glPopMatrix();


    /* Wheels. */
    /* Top left. */
    glColor3f(0.00f, 0.00f, 0.00f);
    glPushMatrix(); 
        glTranslatef(playerCarX-carWidth/2, playerCarY+carLength/3, 0.02f);
        glScalef(0.70f, 0.80f, 1.00f);
        glutSolidSphere((GLdouble)carWheelSize, 50, 50);
    glPopMatrix();

    /* Top right. */
    glPushMatrix(); 
        glTranslatef(playerCarX+carWidth/2, playerCarY+carLength/3, 0.02f);
        glScalef(0.70f, 0.80f, 1.00f);
        glutSolidSphere((GLdouble)carWheelSize, 50, 50);
    glPopMatrix();

    /* Bottom left. */
    glPushMatrix(); 
        glTranslatef(playerCarX-carWidth/2, playerCarY-carLength/3, 0.02f);
        glScalef(0.70f, 0.80f, 1.00f);
        glutSolidSphere((GLdouble)carWheelSize, 50, 50);
    glPopMatrix();

    /* Bottom right. */
    glPushMatrix(); 
        glTranslatef(playerCarX+carWidth/2, playerCarY-carLength/3, 0.02f);
        glScalef(0.70f, 0.80f, 1.00f);
        glutSolidSphere((GLdouble)carWheelSize, 50, 50);
    glPopMatrix();
}
