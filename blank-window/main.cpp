/*
 * Copyright (c) 2024 Yurii Sydor (yuriysydor1991@gmail.com) kytok.org.ua
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *     Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON  ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS  SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

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