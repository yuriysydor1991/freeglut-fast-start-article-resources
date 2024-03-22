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
    // встановлюємо колір очищення піксеоів екрану
    glClearColor (0.0, 0.0, 0.0, 0.0);
}

// Процедура відображення OpenGL сцени
void display()
{
    // очищуємо буфер пікселів екрану
    // раніше встановленим за допомогою glClearColor
    glClear(GL_COLOR_BUFFER_BIT);
    // зберігаємо поточну матрицю у стеку матриць
    // і дублюємо її для редагування
    glPushMatrix();

    // ось тут відображення об'єктів і сцени

    // витягуємо оригінальну матрицю зі стеку матриць
    glPopMatrix();
    // підміняємо буфер для нових команд
    glutSwapBuffers();
}

// Процедура зміни розміру вікна
void reshape(int w, int h)
{
    // встановлюємо розмір вікна OpenGL
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    // встановлюжмо режим матриці у GL_PROJECTION
    glMatrixMode(GL_PROJECTION);
    // Встановлюємо матрицю ідентичності
    glLoadIdentity();

    // Встановлюємо параметри проекції
    glOrtho(0, w, 0, h, -1.0, 100.0);
    // Встановлюємо режим огляду моделі
    glMatrixMode(GL_MODELVIEW);
    // завантажуємо матрицю ідентичності
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