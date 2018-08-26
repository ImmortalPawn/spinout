#include <string.h>

#include "init.h"
#include "global.h"
#include "draw.h"

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

    /* Allocate memory for bot cars. */
    carsNum = 10;
    cars = (Car*)malloc(carsNum * sizeof(Car));
    assert(NULL != cars, "malloc()");

    /* Distance between two bot cars. */
    GLfloat carsSeparation = 0.00f;

    /* Initial (pseudo random) bot cars locations. */
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

    /* Allocate memory for road lines. */
    linesNum = 10;
    lines = (Line*)malloc(linesNum * sizeof(Line));
    assert(NULL != lines, "malloc()");

    /* Distance between road lines. */
    GLfloat linesSeparation = 0.00f;

    /* Initial (pseudo random) road lines locations. */
    for (int i = 0; i < linesNum; i++) {

        lines[i].y = 1.00f + lineLength/2 - linesSeparation;
        linesSeparation += 2 * lineLength; 
    }
    
    /* Spawn point for road lines. */
    linesSpawnY = linesSeparation;

    /* Allocate memory for levels. */
    levelsNum = 10;
    levels = (int*)calloc(levelsNum, sizeof(int));
    assert(NULL != levels, "malloc()");

    /* Coin properties. */
    coinSize = carWidth / 2; 
    coinScaleY = 0.20f;
    coinRotation = 0.00f;
    coinPoints = 5;

    /* Allocate memory for coins. */
    coinsNum = carsNum;
    coins = (Coin*)malloc(carsNum * sizeof(Coin));
    assert(NULL != coins, "malloc()");

    /* All coins are active at the beginning. */
    for (int i = 0; i < coinsNum; i++) {

        coins[i].isActive = 1;
    }

    /* Distance between two coins. */
    GLfloat coinsSeparation = difficulty * carLength/2;

    /* Initial (pseudo random) coins locations. */
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

    /* Indicator if game is animating. */
    gameAnimation = 0;

    /* Speed of ingame objects. */
    speed = carLength / (GLfloat) GAME_TIMER_INTERVAL / 2;

    /* Score based on distance traveled. */
    score = 0.00f;

    /* Final score based on sum of score and number of coins collected. */
    finalScore = 0.00f;

    /* Initial daylight position. */
    lightX = 1.00f;
    lightY = -0.99f;
    lightZ = 0.60f;
    lightSpeed = -0.002f;

    /* Indicator if it day or night. */
    isDay = 0;
}

void deInitVars(void)
{
    free(playerName);
    free(cars);
    free(lines);
    free(levels);
    free(coins);
}

void initOpenGl(void)
{
    /* Define clear color. */
    glClearColor(0.40f, 0.40f, 0.40f, 0.00f);

    /* Enable Z buffer. */
    glEnable(GL_DEPTH_TEST);
}

void initLighting(void)
{ 
    /* Daylight properties. */
    GLfloat lightPosition[] = {lightX, lightY, lightZ, 1.00f};
    GLfloat lightAmbient[] = {0.20f, 0.20f, 0.20f, 1.00f};
    GLfloat lightDiffuse[] = {0.80f, 0.80f, 0.80f, 1.00f};
    GLfloat lightSpecular[] = {1.00f, 1.00f, 1.00f, 1.00f};
    
    /* Apply daylight properties. */
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    /* Player car lights properties. */
    GLfloat carLightsPosition[] = {playerCarX, playerCarY-carLength*5, 0.02f, 1.00f};
    GLfloat carLightsAmbient[] = {0.40f, 0.40f, 0.00f, 1.00f};

    /* Apply player car lights properties. */
    glLightfv(GL_LIGHT1, GL_AMBIENT, carLightsAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT1, GL_POSITION, carLightsPosition);

    /* Player car lights cutoff. */
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.00f);
    GLfloat spotDirection[] = {0.00f, 1.00f, 0.00f};
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);

    /* Material properties. */
    GLfloat ambientCoeffs[] = {0.20f, 0.20f, 0.20f, 1.00f};
    GLfloat diffuseCoeffs[] = {0.80f, 0.80f, 0.80f, 1.00f};
    GLfloat specularCoeffs[] = {0.00f, 0.00f, 0.00f, 1.00f};
    GLfloat shininess = 20.00f;

    /* Apply material properties. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientCoeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseCoeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularCoeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    /* Enable coloring. */
    glEnable(GL_COLOR_MATERIAL);

    /* Smooth shading. */
    glShadeModel(GL_SMOOTH);

    /* Enable lighting. */
    glEnable(GL_LIGHTING);
}