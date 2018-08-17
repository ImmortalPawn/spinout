#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define ESC (27)
// #define DEBUG (1)

typedef struct _Line {
    GLfloat y;
} Line;

/* START of GLOBAL variables. */
GLfloat carSize;
GLfloat carScaleX;
GLfloat carWidth;
GLfloat carHeight;

Line* lines;
int linesNum;
GLfloat lineScaleX;
GLfloat lineWidth;
GLfloat lineHeight;
GLfloat linesSeparation;
GLfloat linesLX;
GLfloat linesRX;

GLfloat speed;
GLfloat score;
/* END of GLOBAL variables.  */

/* Functions declarations. */
void assert(int expr, char* msg);
void initGlobalVars(void);
void onKeyboard(unsigned char key, int x, int y);
void onReshape(int width, int height);
void onDisplay(void);
void initOpenGl(void);
void drawAxis(void);
void drawEdges(void);
void drawLines(void);
void deInitVars(void);

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

    deInitVars();

    exit(EXIT_SUCCESS);
}

void assert(int expr, char* msg)
{
    if (!expr) {
        perror(msg);
        fprintf(stderr, "File: %s\nFunc: %s\nLine: %d\n", __FILE__, __func__, __LINE__);
        exit(EXIT_FAILURE);
    }    
}

void initGlobalVars(void)
{
    carSize = 0.30f;
    carScaleX = 0.70f;
    carWidth = carSize * carScaleX;
    carHeight = carSize;

    #ifdef DEBUG
        printf("carSize = %.2f, carWidth = %.2f, carHeight = %.2f\n", carSize, carWidth, carHeight);
    #endif

    linesNum = 8;
    lineScaleX = 0.30f;
    lineHeight = carHeight / 2;
    lineWidth = lineHeight * lineScaleX;
    linesLX = -0.25f;
    linesRX = 0.25f;

    #ifdef DEBUG
        printf("lineHeight = %.2f, lineWidth = %.2f, linesLX = %.2f, linesRX = %.2f\n", lineHeight, lineWidth, linesLX, linesRX);
    #endif

    lines = (Line*)malloc(linesNum * sizeof(Line));
    assert(NULL != lines, "malloc()");

    linesSeparation = 0.00d;
    for (int i = 0; i < linesNum; i++) {
        lines[i].y = 1.00f - linesSeparation;
        linesSeparation += 2 * lineHeight; 
    }

    #ifdef DEBUG
        printf("Road lines Y coordinates = ");
        for (int i = 0; i < linesNum; i++) {
            printf("%.2lf ", lines[i].y);
        }
        putchar('\n');
    #endif
}

 void onKeyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case ESC:
            exit(EXIT_SUCCESS);
            break;
    }
}

 void onReshape(int width, int height)
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
        1.00d, -1.00d
    );
}

 void onDisplay(void)
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

    /* Draw road lines. */
    drawLines();

    glColor3f(1.00f, 1.00f, 1.00f);
    glPushMatrix();
        glTranslatef(0.00f, -0.70f, 0.00f);
        glScalef(carScaleX, 1.00f, 1.00f);
        glutWireCube((GLdouble)carSize);
    glPopMatrix();

    /* Swap buffers. */
    glutSwapBuffers();
}

void initOpenGl(void)
{
    /* Define clear color. */
    glClearColor(0.00f, 0.00f, 0.00f, 0.00f);

    /* Enable Z buffer. */
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

            /* Left line. */
            glVertex3f(-0.25f, -1.00f, 0.00f);
            glVertex3f(-0.25f, 1.00f, 0.00f);

            /* Right line. */
            glVertex3f(0.25f, -1.00f, 0.00f);
            glVertex3f(0.25f, 1.00f, 0.00f);

        glEnd();

        glLineWidth(1);

    glPopMatrix();
}

void drawLines(void)
{
    glColor3f(1.00f, 1.00f, 1.00f);

    for (int i = 0; i < linesNum; i++) {

        /* Draw left lines. */
        glPushMatrix();
            glTranslatef(linesLX, lines[i].y, 0.00f);
            glScalef(lineScaleX, 1.00f, 0.00f);
            glutSolidCube(lineHeight);
        glPopMatrix();

        /* Draw right lines. */
        glPushMatrix();
            glTranslatef(linesRX, lines[i].y, 0.00f);
            glScalef(lineScaleX, 1.00f, 0.00f);
            glutSolidCube(lineHeight);
        glPopMatrix();
    }
}

void deInitVars(void)
{
    free(lines);
}