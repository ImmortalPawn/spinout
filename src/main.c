#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/glut.h>

/* Draw debug information. */
// #define DEBUG_VISUAL (1)
/* Print debug information. */
// #define DEBUG_CONSOLE (2)
#define ENTER (13)
#define ESC (27)
#define GAME_TIMER_ID (1)
#define GAME_TIMER_INTERVAL (17)

typedef struct _Line {
    GLfloat y;
} Line;

typedef struct _Car {
    GLfloat x;
    GLfloat y;
} Car;

typedef struct _Coin {
    GLfloat x;
    GLfloat y;
    int isActive;
} Coin;

/* START of GLOBAL variables. */
GLfloat carLength;
GLfloat carWidth;
GLfloat carScaleX;
GLfloat carWheelSize;

int carsNum;
Car* cars;
GLfloat carsSpawnY;

GLfloat playerCarX;
GLfloat playerCarY;

GLfloat lineLength;
GLfloat lineWidth;
GLfloat lineScaleX;

int linesNum;
Line* lines;

GLfloat linesLX;
GLfloat linesRX;
GLfloat linesSpawnY;

int coinsNum;
Coin* coins;
GLfloat coinsSpawnY;
GLfloat coinSize;
GLfloat coinScaleY;
GLfloat coinRotation;
int coinPoints;

int gameAnimation;

int levelsNum;
int* levels;
GLfloat difficulty;
char* playerName;
GLfloat finalScore;
GLfloat speed;
GLfloat score;

GLfloat lightX;
GLfloat lightY;
GLfloat lightZ;
GLfloat lightSpeed;
GLfloat isDay;
/* END of GLOBAL variables.  */

/* START of functions declarations. */

/* Error check. */
void assert(int expr, char* msg);
/* Initialize global variables. */
void initGlobalVars(int argc, char** argv);
/* Deinitialize variables. */
void deInitVars(void);
/* Initialize OpenGl*/
void initOpenGl(void);
/* Initialize light. */
void initLight(void);

/* Callback functions. */
void onKeyboard(unsigned char key, int x, int y);
void onReshape(int width, int height);
void onDisplay(void);
/* Timer function. */
void onTimer(int timerId);

/* Drawing functions. */
void drawAxis(void);
void drawEdges(void);
void drawRoad(void);
void drawRoadLines(void);
void drawBotCars(void);
void drawCoins(void);
void drawPlayer(void);
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

    /* Initialize OpenGL. */ 
    initOpenGl();

    /* Callback functions. */
    glutKeyboardFunc(onKeyboard);
    glutReshapeFunc(onReshape);
    glutDisplayFunc(onDisplay);

    /* Main loop. */
    glutMainLoop();

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
    /* Game difficulty: E - easy, M - medium, H - hard, I - insane. */
    /* Set difficulty and player name based on command line arguments. */
    if (argc == 1) {

        difficulty = 5.00f;

        int playerNameLen = strlen("unnamed");
        playerName = (char*)malloc((playerNameLen + 1) * sizeof(char));
        assert(NULL != playerName, "malloc()");

        strcpy(playerName, "Unnamed");
        playerName[playerNameLen] = '\0';
    }
    else if (argc == 2) {

        int argvLen = strlen(argv[1]); 
        if (argvLen == 1) {

            switch (argv[1][0]) {

                case 'e':
                case 'E':
                    difficulty = 5.00f;
                    break;

                case 'm':
                case 'M':
                    difficulty = 4.00f;
                    break;

                case 'h':
                case 'H':
                    difficulty = 3.00f;
                    break;

                case 'i':
                case 'I':
                    difficulty = 2.50f;
                    break;

                default:
                    difficulty = 5.00f;
            }

            int playerNameLen = strlen("unnamed");
            playerName = (char*)malloc((playerNameLen + 1) * sizeof(char));
            assert(NULL != playerName, "malloc()");

            strcpy(playerName, "Unnamed");
            playerName[playerNameLen] = '\0';
        }
        else {

            difficulty = 5.00f;

            playerName = (char*)malloc((argvLen + 1) * sizeof(char));
            assert(NULL != playerName, "malloc()");

            strcpy(playerName, argv[1]);
            playerName[argvLen] = '\0';
        }
    }
    else if (argc == 3) {
        
        int argv1Len = strlen(argv[1]);

        if (argv1Len == 1) {

            switch (argv[1][0]) {

                case 'e':
                case 'E':
                    difficulty = 5.00f;
                    break;

                case 'm':
                case 'M':
                    difficulty = 4.00f;
                    break;

                case 'h':
                case 'H':
                    difficulty = 3.00f;
                    break;

                case 'i':
                case 'I':
                    difficulty = 2.50f;
                    break;

                default:
                    difficulty = 5.00f;
            }
        }
        else {

            difficulty = 5.00f;
        }

        int argv2Len = strlen(argv[2]);
        playerName = (char*)malloc((argv2Len + 1) * sizeof(char));
        assert(NULL != playerName, "malloc()");

        strcpy(playerName, argv[2]);
        playerName[argv2Len] = '\0';
    }
    else {

        difficulty = 5.00f;
        
        int playerNameLen = strlen("unnamed");
        playerName = (char*)malloc((playerNameLen + 1) * sizeof(char));
        assert(NULL != playerName, "malloc()");

        strcpy(playerName, "Unnamed");
        playerName[playerNameLen] = '\0';
    }

    /* Initialize cars properties. */
    carScaleX = 0.70f;
    carLength = 0.20f;
    carWidth = carLength * carScaleX;
    carWheelSize = 0.03;

    /* Initialize bot cars. */
    carsNum = 10;
    cars = (Car*)malloc(carsNum * sizeof(Car));
    assert(NULL != cars, "malloc()");

    /* Distance between two bot cars. */
    GLfloat carsSeparation = 0.00f;

    /* Initial bot cars locations. */
    for (int i = 0; i < carsNum; i++) {

        GLfloat carX;
        int carRandomX = rand() % 3;

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
        carsSeparation += difficulty * carLength; 
    }

    /* Spawn point for bot cars. */
    carsSpawnY = carsSeparation - 1.00f;
    
    #ifdef DEBUG_CONSOLE
        printf("carsSeparation = %.2lf, carsSpawnY = %.2lf\n", carsSeparation, carsSpawnY);
    #endif

    /* Player car location. */
    playerCarX = 0.00f;
    playerCarY = -0.70f;

    #ifdef DEBUG_CONSOLE
        printf("carLength = %.2f, carWidth = %.2f, carsNum = %d\n", carLength, carWidth, carsNum);
    #endif

    /* Initialize road lines properties. */
    lineScaleX = 0.30f;
    lineLength = carLength / 2;
    lineWidth = lineLength * lineScaleX;
    linesLX = -0.25f;
    linesRX = 0.25f;

    #ifdef DEBUG_CONSOLE
        printf("lineLength = %.2f, lineWidth = %.2f, linesLX = %.2f, linesRX = %.2f\n", lineLength, lineWidth, linesLX, linesRX);
    #endif

    /* Initialize road lines. */
    linesNum = 10;
    lines = (Line*)malloc(linesNum * sizeof(Line));
    assert(NULL != lines, "malloc()");

    /* Distance between road lines. */
    GLfloat linesSeparation = 0.00f;

    /* Initial road lines locations. */
    for (int i = 0; i < linesNum; i++) {

        lines[i].y = 1.00f + lineLength/2 - linesSeparation;
        linesSeparation += 2 * lineLength; 
    }
    
    linesSpawnY = linesSeparation;

    /* Initialize levels. */
    levelsNum = 10;
    levels = (int*)calloc(levelsNum, sizeof(int));
    assert(NULL != levels, "malloc()");

    /* Coin properties. */
    coinSize = carWidth / 2; 
    coinScaleY = 0.20f;
    coinRotation = 0.00f;
    coinPoints = 5;

    /* Initialize coins. */
    coinsNum = carsNum;
    coins = (Coin*)malloc(carsNum * sizeof(Coin));
    assert(NULL != coins, "malloc()");

    /* All coins are active at the beginning. */
    for (int i = 0; i < coinsNum; i++) {

        coins[i].isActive = 1;
    }

    /* Distance between two coins. */
    GLfloat coinsSeparation = difficulty * carLength/2;

    /* Initial coins locations. */
    for (int i = 0; i < coinsNum; i++) {

        GLfloat coinX;
        int coinRandomX = rand() % 3;

        switch (coinRandomX) {
            case 0:
                coinX = -0.50f;
                break;
            case 1:
                coinX = 0.00f;
                break;
            case 2:
                coinX = 0.50f;
                break;
        }

        coins[i].x = coinX;
        coins[i].y = 1.00f + coinsSeparation;
        coinsSeparation += difficulty * carLength; 
    }

    /* Spawn point for coins. */
    coinsSpawnY = coinsSeparation - 1.00f;

    #ifdef DEBUG_CONSOLE
        printf("coinsSeparation = %.2lf, coinsSpawnY = %.2lf\n", coinsSeparation, coinsSpawnY);
    #endif

    /* Indicator that shows if game should be animating. */
    gameAnimation = 0;

    /* Speed of ingame objects. */
    speed = carLength / (GLfloat) GAME_TIMER_INTERVAL / 2;

    /* Score based on distance traveled. */
    score = 0.00f;

    /* Final score based on sum of score and number of coins collected. */
    finalScore = 0.00f;

    /* Initial light position. */
    lightX = 1.00f;
    lightY = -0.99f;
    lightZ = 0.60f;
    lightSpeed = -0.002f;
    isDay = 0;
}

void onKeyboard(unsigned char key, int x, int y)
{
    switch (key) {

        /* Close game. */
        case ESC:

            /* Deinitialize global variables. */
            deInitVars();

            exit(EXIT_SUCCESS);
            break;

        /* Start game. */
        case ENTER:

            if (!gameAnimation) {

                glutTimerFunc(GAME_TIMER_INTERVAL, onTimer, GAME_TIMER_ID);
                gameAnimation = 1;
            }
            break;
        
        /* Pause game. */
        case 'p':
        case 'P':
            gameAnimation = 0;
            break;

        /* Move player car one track to the left. */
        case 'a':
        case 'A':

            if (playerCarX != -0.50f) {

                playerCarX -= 0.50f;
            }
            break;

        /* Move player car one track to the right. */
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
        -1.00d, 0.90d,
        -2.00d, 2.00d
    );
}

void onDisplay(void)
{
    /* Clear buffers. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Set model view. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Set point of view. */
    gluLookAt
    (
        0.00d, 0.00d, 1.00d,
        0.00d, 0.00d, 0.00d, 
        0.00d, 1.00d, 0.00d
    );

    /* Initialize light. */
    initLight();

    #ifdef DEBUG_VISUAL
        /* Draw main axis lines. */
        drawAxis();

        /* Draw edges of the scene. */
        drawEdges();
    #endif

    #ifdef DEBUG_CONSOLE
        printf("Road lines Y coordinates = ");
        for (int i = 0; i < linesNum; i++) {
            printf("%.2lf ", lines[i].y);
        }
        putchar('\n');
    #endif

    /* Draw road. */
    drawRoad();

    /* Draw road lines. */
    drawRoadLines();

    /* Draw bot cars. */
    drawBotCars();

    /* Draw coins. */
    drawCoins();

    /* Draw player car. */
    drawPlayer();

    /* Swap buffers. */
    glutSwapBuffers();
}

void onTimer(int timerId)
{
    if (timerId == GAME_TIMER_ID) {

        /* Score is based on speed and level. */
        GLfloat levelBase = 5.00f;
        for (int i = 0; i < levelsNum; i++) {

            GLfloat sumLess = 0.00f;
            GLfloat sumMore = 0.00f;

            for (int j = 0; j <= i; j++) {
                sumMore += levelBase * (j+1);
            }

            for (int j = 0; j < i; j++) {
                sumLess += levelBase * (j+1);
            }

            if (score > sumLess && score <= sumMore) {
                
                if (levels[i] != 1) {

                    GLfloat div;
                    
                    if (i == 0 || i == 1) {

                        div = 1.00f;
                    }
                    else {

                        div = (GLfloat)i;
                    }

                    speed *= (GLfloat)(i+1) / div;
                    levels[i] = 1;
                }
            }
        }

        long int scoreBefore = (long int)finalScore;
        score += speed;
        finalScore += speed;

        coinRotation += 5.00f;

        /* Print score only if long int value is different then previous one. (to reduce console spam). */
        if (scoreBefore != (long int)finalScore) {

            printf("Score: %ld\n", (long int)finalScore);
        }

        /* Animate road lines. */
        for (int i = 0; i < linesNum; i++) {

            lines[i].y -= speed;
        }

        /* Animate bot cars. */
        for (int i = 0; i < carsNum; i++) {

            cars[i]. y -= speed;
        }

        /* Animate coins. */
        for (int i = 0; i < coinsNum; i++) {

            coins[i].y -= speed;
        }

        /* Animate light to create day and night experience. */
        lightY += lightSpeed;

        if (lightY >= 0.99f) {

            lightSpeed = -lightSpeed;
            lightZ = -lightZ;
            isDay = 1;
        }

        if (lightY < -0.99f) {

            lightSpeed = -lightSpeed;
            lightZ = -lightZ;
            isDay = 0;
        }

        if (!isDay) {

            glDisable(GL_LIGHT0);
            glEnable(GL_LIGHT1);
        }
        else {

            glEnable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
        }

        /* Road lines collision with bottom edge. */
        for (int i = 0; i < linesNum; i++) {

            if ((lines[i].y + lineLength/2) <= -1.00f) {

                lines[i].y = linesSpawnY - 1.00f - lineLength/2;
            }
        }

        /* Bot cars collision with bottom edge. */
        for (int i = 0; i < carsNum; i++) {

            int carRandomX;
            GLfloat carX;

            if (cars[i].y + carLength/2 <= -1.00f) {
                
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

                /* New spawn point for bot car. */
                cars[i].x = carX;
                cars[i].y = carsSpawnY;
            }
        }

        /* Coins collision with bottom edge. */
        for (int i = 0; i < coinsNum; i++) {

            int coinRandomX; 
            GLfloat coinX;

            if (coins[i].y + coinSize/2 <= -1.00f) {
                
                coinRandomX = rand() % 3;

                switch (coinRandomX) {
                    case 0:
                        coinX = -0.50f;
                        break;
                    case 1:
                        coinX = 0.00f;
                        break;
                    case 2:
                        coinX = 0.50f;
                        break;
                }

                /* New spawn point for coin. */
                coins[i].x = coinX;
                coins[i].y = coinsSpawnY;
                coins[i].isActive = 1;
            }
        }

        /* TRICK: If coin spawns on top of bot car, remove it. */
        for (int i = 0; i < coinsNum; i++) {

            for (int j = 0; j < carsNum; j++) {

                /* Collision detect. */
                if (fabs((cars[j].y - coins[i].y)) <= carLength/2 + coinSize) {

                    if (coins[i].isActive) {

                        if (cars[j].x == coins[i].x) {
                            coins[i].isActive = 0;
                        }
                    }
                }
            }
        }

        /* Player car collision with bot cars. */
        for (int i = 0; i < carsNum; i++) {

            /* Possible collision. */
            if (cars[i].y <= -0.30f) {

                /* Collision detect. */
                if (fabs((cars[i].y - playerCarY)) <= carLength) {

                        if (cars[i].x == playerCarX) {

                            #ifdef DEBUG_CONSOLE
                                printf("GAMEOVER: playerCarY = %.2f, colisionCarY = %.2f\n", playerCarY, cars[i].y);
                            #endif
                            printf("%s YOU LOSE!\nHIGHSCORE: \nYOUR SCORE: %ld\n", playerName, (long int)finalScore);
                            gameAnimation = 0;
                            /* onKeyboard(ESC, 0, 0); commented for debugging purposes. */
                        }
                }
            }
        }

        /* Player collision with coins. */
        for (int i = 0; i < coinsNum; i++) {

            /* Possible collision. */
            if (coins[i].y <= -0.30f) {

                /* Collision detect. */
                if (fabs((coins[i].y - playerCarY)) <= carLength/2 + coinSize/2) {

                        if (coins[i].x == playerCarX) {

                            /* Remove coin because it is collected. */
                            if (coins[i].isActive) {

                                finalScore += coinPoints;
                                coins[i].isActive = 0;
                            }
                        }
                }
            }
        }

        /* Force draw on display. */
        glutPostRedisplay();

        if (gameAnimation) {

            glutTimerFunc(GAME_TIMER_INTERVAL, onTimer, GAME_TIMER_ID);
        }
    }
}

void initOpenGl(void)
{
    /* Define clear color. */
    glClearColor(0.40f, 0.40f, 0.40f, 0.00f);

    /* Enable Z buffer. */
    glEnable(GL_DEPTH_TEST);
}

void initLight(void)
{ 
    /* Light properties. */
    GLfloat lightPosition[] = {lightX, lightY, lightZ, 1.00f};
    GLfloat lightAmbient[] = {0.20f, 0.20f, 0.20f, 1.00f};
    GLfloat lightDiffuse[] = {0.80f, 0.80f, 0.80f, 1.00f};
    GLfloat lightSpecular[] = {1.00f, 1.00f, 1.00f, 1.00f};

    /* Car lights properties. */
    GLfloat carLightsPosition[] = {playerCarX, playerCarY-carLength*5, 0.02f, 1.00f};
    GLfloat carLightsAmbient[] = {0.40f, 0.40f, 0.00f, 1.00f};

    /* Material properties. */
    GLfloat ambientCoeffs[] = {0.20f, 0.20f, 0.20f, 1.00f};
    GLfloat diffuseCoeffs[] = {0.80f, 0.80f, 0.80f, 1.00f};
    GLfloat specularCoeffs[] = {0.00f, 0.00f, 0.00f, 1.00f};
    GLfloat shininess = 20.00f;

    /* Enable coloring. */
    glEnable(GL_COLOR_MATERIAL);

    /* Smooth shading. */
    glShadeModel(GL_SMOOTH);

    /* Enable lighting. */
    glEnable(GL_LIGHTING);

    /* Apply light properties. */
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    /* Apply material properties. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientCoeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseCoeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularCoeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    /* Apply player car lights properties. */
    glLightfv(GL_LIGHT1, GL_AMBIENT, carLightsAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT1, GL_POSITION, carLightsPosition);

    /* Player car lights cutoff. */
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.00f);
    GLfloat spotDirection[] = {0.00f, 1.00f, 0.00f};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
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

void deInitVars(void)
{
    free(playerName);
    free(cars);
    free(lines);
    free(levels);
    free(coins);
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
