#include <stdio.h>
#include <math.h>

#include "callback.h"
#include "global.h"
#include "draw.h"
#include "init.h"

void onKeyboard(unsigned char key, int x, int y)
{
    switch (key) {

        /* Close game. */
        case ESC:

            /* Deinitialize global variables (clean for memory leaks). */
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

    /* Initialize lighting. */
    initLighting();

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

        /* Print score only if long int value is different then previous one. (to reduce console spam) */
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

        /* Set day or night lighting. */
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

                            printf("%s YOU CRASHED!\nYOUR SCORE: %ld\n", playerName, (long int)finalScore);
                            gameAnimation = 0;
                            onKeyboard(ESC, 0, 0);
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