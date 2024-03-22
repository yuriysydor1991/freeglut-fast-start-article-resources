//
// Created by cc on 22.03.24.
//

// головні заголовкові файли GLUT і OpenGL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// деякі константи
// ширини і висоти вікна за замовчуванням
constexpr const unsigned int W_DEFAULT_WIDTH = 500;
constexpr const unsigned int W_DEFAULT_HEIGHT = 500;

// функція ініціалізації параметрів OpenGL
void init()
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

// Процедура відображення OpenGL сцени
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

// Процедура зміни розміру вікна
void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Головна функція програми
int main(int argc, char** argv)
{
    // Ініціалізація FreeGLUT бібліотеки
    glutInit(&argc, argv);
    // Встановлення параметрів відображення
    // для подвійної буферизації і RGB кольорової схеми
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    // Встановлення розмірів вікна
    glutInitWindowSize (W_DEFAULT_WIDTH, W_DEFAULT_HEIGHT);
    // Створення вікна з назвою у якості шляху до виконуваного файлу
    glutCreateWindow (argv[0]);

    // Виклик процедури ініціалізації
    init ();

    // Встановлення головних процедур
    // для відображення схеми
    glutDisplayFunc(display);
    // для зміни розміру вікна
    glutReshapeFunc(reshape);

    // Головний цикл FreeGLUT бібліотеки
    // у якому обробляються події
    // і відбувається інша магія
    glutMainLoop();

    return 0;
}