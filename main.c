#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

/* Funkcija initalize() vrsi OpenGL inicijalizaciju. */
static void initialize(void);

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_display(void);

int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("spinout");

    /* Registruju se funkcije za obradu dogadjaja. */
    glutKeyboardFunc(on_keyboard);
    glutDisplayFunc(on_display);

    /* Obavlja se OpenGL inicijalizacija. */
    initialize();

    /* Ulazi se u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void initialize(void)
{
    /* Postavlja se boja pozadine. */
    glClearColor(0, 0, 0, 0);
}

static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        /* ESC dugme - Zavrsava se program. */
        exit(0);
        break;
	}

	//FIXME glutPostRedisplay(); ubaci kada bude imalo iscrtavanja
}

static void on_display(void)
{
    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
