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

// системні підключення
#include <chrono>

// головні заголовкові файли GLUT і OpenGL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// деякі константи
// ширини і висоти вікна за замовчуванням
constexpr const unsigned int W_DEFAULT_WIDTH = 500;
constexpr const unsigned int W_DEFAULT_HEIGHT = 500;

long int getMillisecondsTime();

// глобальна змінна для обертання бублика
// градуси обертання бублика
long int spin = 0;
// змінна для зберігання часу пройденого від
// останнього намальованого кадру.
long int timestart = getMillisecondsTime();

// функція яка повертає поточні мілісекунди пройденого часу
long int getMillisecondsTime()
{
    // отримуємо поточний час
    auto currentTime = std::chrono::system_clock::now();

    // Перетворюємо поточний час у мілісекунди від початку відліку
    auto currentTimeMillis = std::chrono::time_point_cast<std::chrono::milliseconds>(currentTime);

    // отримуємо значення мілісекунд
    return currentTimeMillis.time_since_epoch().count();
}

// процедура перераховування обертання фігури в залежності від часу
void recalculateSpin()
{
    // отримуємо поточний час у локальну змінну
    auto ctime = getMillisecondsTime();
    // обраховуємо пройдений час від попереднього кадру
    auto deltaTime =  ctime - timestart;

    // якщо змінити дільник тоді зміниться швидкість обертання
    spin += deltaTime / 10;

    // обрізаємо значення обертання у проміжок [0,360]
    if (spin > 360) { spin -= 360; }

    // зберігаємо поточне значення часу
    timestart = ctime;
}

// функція ініціалізації параметрів OpenGL
void init()
{
    // встановлюємо колір очищення пікселів екрану
    glClearColor (0.0, 0.0, 0.0, 0.0);
    // вмикаємо розпізнавання глибини
    glEnable(GL_DEPTH_TEST);
}

// Процедура відображення OpenGL сцени
void display()
{
    // очищуємо буфер пікселів екрану
    // раніше встановленим за допомогою glClearColor
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // зберігаємо поточну матрицю у стеку матриць
    // і дублюємо її для редагування
    glPushMatrix();

    // обертаємо поточну матрицю
    glRotatef(spin, 1.0, 0.0, 0.0);

    // встановлюємо колір який буде використовуватися для малювання
    glColor3f(.7f, .7f, .9f);
    // використовуємо функцію FreeGLUT для відмальовування бублика
    glutWireTorus (50.0, 200.0, 20, 20);

    // витягуємо оригінальну матрицю зі стеку матриць
    glPopMatrix();
    // підміняємо буфер для нових команд
    glutSwapBuffers();

    // перераховуємо кут обертання фігури в залежності від часу
    // пройденого між кадрами
    recalculateSpin();

    // примусово перемальовуємо екран
    glutPostRedisplay();
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
    glOrtho(-w/2.f, w/2.f, -h/2.f, h/2.f, -1000.0, 1000.0);
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