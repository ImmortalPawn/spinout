#include <stdlib.h>
#include <GL/glut.h>

#define ESC (27)
/* #define DEBUG (1) */

/* START of GLOBAL variables. */
GLdouble carSize;
GLdouble carWidth;
GLdouble carHeight;
GLfloat carScaleX;
/* END of GLOBAL variables.  */

/* Functions declaration. */
static void initGlobalVars(void);
static void onKeyboard(unsigned char key, int x, int y);
static void onReshape(int width, int height);
static void onDisplay(void);
static void initOpenGl(void);
void drawAxis(void);
void drawEdges(void);

int main(int argc, char** argv)
{
    /* Initialize global variables. */
    initGlobalVars();

    /* Initialize GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Initialize/Create window. */
    glutInitWindowSize(300, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    /* Callback functions. */
    glutKeyboardFunc(onKeyboard);
    glutReshapeFunc(onReshape);
    glutDisplayFunc(onDisplay);

    /* Initialize OpenGL. */ 
    initOpenGl();

    /* Main loop. */
    glutMainLoop();

    exit(EXIT_SUCCESS);
}

static void initGlobalVars(void)
{
    carSize = 0.30d;
    carScaleX = 0.70f;
    carWidth = carSize / (GLdouble)carScaleX;
    carHeight = carSize;
}

static void onKeyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case ESC:
            exit(EXIT_SUCCESS);
            break;
    }
}

static void onReshape(int width, int height)
{
    /* Set viewport. */
    glViewport(0, 0, width, height);

    /* Set projection. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho
    (
        -0.75d, 0.75d,
        -1.00d, 1.00d,
        1.00d, 0.00d
    );
}

static void onDisplay(void)
{
    /* Clear buffers. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Set point of view. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt
    (
        0.00d, 0.00d, 1.00d,
        0.00d, 0.00d, 0.00d, 
        0.00d, 1.00d, 0.00d
    );

    #ifdef DEBUG
        /* Draw main axis lines. */
        drawAxis();

        /* Draw edges of view window. */
        drawEdges();
    #endif

    /*
    glColor3f(0.00f, 0.00f, 0.00f);
    glPushMatrix();
        glTranslatef(0.00f, -0.70f, 0.00f);
        glScalef(carScaleX, 1.00f, 1.00f);
        glutWireCube(carSize);
    glPopMatrix();
    */

    /* Swap buffers. */
    glutSwapBuffers();
}

static void initOpenGl(void)
{
    glClearColor(0.75f, 0.75f, 0.75f, 0.00f);
    glEnable(GL_DEPTH_TEST);
}

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

        glEnd();

        glLineWidth(1);

    glPopMatrix();
}