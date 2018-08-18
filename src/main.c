#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

/* Draw debug information. */
// #define DEBUG_VISUAL (1)
/* Print debug information. */
// #define DEBUG_CONSOLE (2)
#define ENTER (13)
#define ESC (27)
#define GAME_TIMER_ID (1)
#define GAME_TIMER_INTERVAL (20)

typedef struct _Line {
    GLfloat y;
} Line;

typedef struct _Car {
    GLfloat x;
    GLfloat y;
} Car;

/* START of GLOBAL variables. */
int carsNum;
Car* cars;
GLfloat carsSeparation;
GLfloat carsSpawnY;
GLfloat carHeight;
GLfloat carScaleX;
GLfloat carWidth;
GLfloat playerCarX;
GLfloat playerCarY;

Line* lines;
int linesNum;
GLfloat lineScaleX;
GLfloat lineWidth;
GLfloat lineHeight;
GLfloat linesSeparation;
GLfloat linesLX;
GLfloat linesRX;

int gameAnimation;
GLfloat speed;
GLfloat score;
/* END of GLOBAL variables.  */

/* START of functions declarations. */

/* Error check function. */
void assert(int expr, char* msg);
/* Initialize global variables. */
void initGlobalVars(int argc, char** argv);
/* Free/Remove .. variables. */
void deInitVars(void);
/*Initialize OpenGl*/
void initOpenGl(void);

/* Callback functions. */
void onKeyboard(unsigned char key, int x, int y);
void onReshape(int width, int height);
void onDisplay(void);
/* Timer function. */
void onTimer(int timerId);

/* Drawing functions. */
void drawAxis(void);
void drawEdges(void);
void drawLines(void);
void drawCars(void);
/* END of functions declarations. */

int main(int argc, char** argv)
{
    /* Initialize global variables. */
    initGlobalVars(argc, argv);

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

    /* Deinitialize global variables. */
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


void initGlobalVars(int argc, char** argv)
{
    playerCarX = 0.00f;
    playerCarY = -0.70f;

    /* TODO: game difficulty

    if (argc == 2) {

        char* str = argv[1];
        for (unsigned int i = 0; i < len(str), i++) {

            str[i] = tolower(str[i]);
        }

        switch (argv[1]) {

            case "easy": 
                break; 
            case "medium":
                break;
            case "hard":
                carsNum = 10;
                break;
            default: 
                carsNum = 5;
                break;
        }
    }

    */
    carsNum = 3;

    carHeight = 0.30f;
    carScaleX = 0.70f;
    carWidth = carHeight * carScaleX;

    cars = (Car*)malloc(carsNum * sizeof(Car));
    assert(NULL != cars, "malloc()");

    carsSeparation = 0.00f;
    GLfloat carX = 0.00f;
    int carRandomX = 0;
    for (int i = 0; i < carsNum; i++) {

        carRandomX = rand() % 3;
        switch (carRandomX) {
            case 0:
                carX = -0.50f;
                break;
            case 1:
                carX = 0.00f;
                break;
            case 2:
                carX = 0.50f;
                break;
        }

        cars[i].x = carX;
        cars[i].y = 1.00f + carsSeparation;
        carsSeparation += 2.5 * carHeight; 
    }

    carsSpawnY = carsSeparation - 1.00f;

    #ifdef DEBUG_CONSOLE
        printf("carHeight = %.2f, carWidth = %.2f, carsNum = %d\n", carHeight, carWidth, carsNum);
    #endif

    linesNum = 8;
    lineScaleX = 0.30f;
    lineHeight = carHeight / 2;
    lineWidth = lineHeight * lineScaleX;
    linesLX = -0.25f;
    linesRX = 0.25f;

    #ifdef DEBUG_CONSOLE
        printf("lineHeight = %.2f, lineWidth = %.2f, linesLX = %.2f, linesRX = %.2f\n", lineHeight, lineWidth, linesLX, linesRX);
    #endif

    lines = (Line*)malloc(linesNum * sizeof(Line));
    assert(NULL != lines, "malloc()");

    linesSeparation = 0.00f;
    for (int i = 0; i < linesNum; i++) {
        lines[i].y = 1.00f - linesSeparation;
        linesSeparation += 2 * lineHeight; 
    }

    gameAnimation = 0;
    speed = carHeight / (GLfloat) GAME_TIMER_INTERVAL / 2;
    score = 0.00f;
}

 void onKeyboard(unsigned char key, int x, int y)
{
    switch (key) {

        /* Close game. */
        case ESC:
            exit(EXIT_SUCCESS);
            break;

        /* Start game. */
        case ENTER:

            if (!gameAnimation) {

                glutTimerFunc(GAME_TIMER_INTERVAL, onTimer, GAME_TIMER_ID);
                gameAnimation = 1;
            }
            break;

        /* Move one track to the left. */
        case 'a':
        case 'A':

            if (playerCarX != -0.50f) {

                playerCarX -= 0.50f;
            }
            break;

        /* Move player one track to the right. */
        case 'd':
        case 'D':

            if (playerCarX != 0.50f) {

                playerCarX += 0.50f;
            }
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

    #ifdef DEBUG_VISUAL
        /* Draw main axis lines. */
        drawAxis();

        /* Draw edges of view window. */
        drawEdges();
    #endif

    #ifdef DEBUG_CONSOLE
        printf("Road lines Y coordinates = ");
        for (int i = 0; i < linesNum; i++) {
            printf("%.2lf ", lines[i].y);
        }
        putchar('\n');
    #endif

    /* Draw road lines. */
    drawLines();

    /* Draw bot cars. */
    drawCars();

    /* Draw player car. */
    glColor3f(1.00f, 1.00f, 1.00f); 
    glPushMatrix(); 
        glTranslatef(playerCarX, playerCarY, 0.00f);
        glScalef(carScaleX, 1.00f, 1.00f);
        glutWireCube((GLdouble)carHeight);
    glPopMatrix();

    /* Swap buffers. */
    glutSwapBuffers();
}

void onTimer(int timerId)
{
    if (timerId == GAME_TIMER_ID) {

        /* Animate road lines. */
        for (int i = 0; i < linesNum; i++) {
            lines[i].y -= speed;
        }

        /* Score is based on speed. */
        score += speed;
        printf("Score: %.2lf\n", score);

        /* Animate cars. */
        for (int i = 0; i < carsNum; i++) {
            cars[i]. y -= speed;
        }

        /* Force draw on display. */
        glutPostRedisplay();

        /* Lines collision with bottom edge. */
        for (int i = 0; i < linesNum; i++) {

            if ((lines[i].y + lineHeight/2) <= -1.00f) {

                lines[i].y = 1.00f;
            }
        }

        /* Cars colision with bottom edge. */
        for (int i = 0; i < carsNum; i++) {

            if (cars[i].y + carHeight/2 <= -1.00f) {
                
                int carRandomX = rand() % 3;
                GLfloat carX;

                switch (carRandomX) {
                    case 0:
                        carX = -0.50f;
                        break;
                    case 1:
                        carX = 0.00f;
                        break;
                    case 2:
                        carX = 0.50f;
                        break;
                }

                /* New spawn point for bot car. */
                cars[i].x = carX;
                cars[i].y = carsSpawnY;
            }
        }

        /* Cars collision with player car. */
        for (int i = 0; i < carsNum; i++) {

            /* Possible collision. */
            if (cars[i].y <= -0.30f) {

                /* Collision detect. */
                if (fabs((cars[i].y - playerCarY)) <= carHeight) {

                        if (cars[i].x == playerCarX) {

                            printf("GAMEOVER: playerCarY = %.2f, colisionCarY = %.2f\n", playerCarY, cars[i].y);
                            gameAnimation = 0;
                        }
                }
            }
        }

        if (gameAnimation) {
            glutTimerFunc(GAME_TIMER_INTERVAL, onTimer, GAME_TIMER_ID);
        }
    }
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
    free(cars);
    free(lines);
}

void drawCars(void)
{
    glColor3f(1.00f, 1.00f, 1.00f); 

    for (int i = 0; i < carsNum; i++) {

        glPushMatrix(); 
            glTranslatef(cars[i].x, cars[i].y, 0.00f);
            glScalef(carScaleX, 1.00f, 1.00f);
            glutWireCube((GLdouble)carHeight);
        glPopMatrix();
    }
}