/* GLOBAL variables. */

#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <GL/glut.h>

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

/* Car properties. */
GLfloat carLength;
GLfloat carWidth;
GLfloat carScaleX;
GLfloat carWheelSize;

/* Bot cars properties. */
int carsNum;
Car* cars;
GLfloat carsSpawnY;

/* Player car properties. */
GLfloat playerCarX;
GLfloat playerCarY;

/* Road lines properties. */
GLfloat lineLength;
GLfloat lineWidth;
GLfloat lineScaleX;
int linesNum;
Line* lines;
GLfloat linesLX;
GLfloat linesRX;
GLfloat linesSpawnY;

/* Coins properties. */
int coinsNum;
Coin* coins;
GLfloat coinsSpawnY;
GLfloat coinSize;
GLfloat coinScaleY;
GLfloat coinRotation;
int coinPoints;

/* Game properties. */
int gameAnimation;
int levelsNum;
int* levels;
GLfloat difficulty;
char* playerName;
GLfloat finalScore;
GLfloat speed;
GLfloat score;

/* Daylight properties. */
GLfloat lightX;
GLfloat lightY;
GLfloat lightZ;
GLfloat lightSpeed;

/* Activates day or night lighting. */
GLfloat isDay;

/* Error checker. */
void assert(int expr, char* msg);

#endif