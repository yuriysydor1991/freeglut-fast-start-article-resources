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

// заголовкові файли проекту
#include "cube_raw_texture.h"

// деякі константи
// ширини і висоти вікна за замовчуванням
constexpr const unsigned int W_DEFAULT_WIDTH = 500;
constexpr const unsigned int W_DEFAULT_HEIGHT = 500;

long int getMillisecondsTime();

// глобальна змінна для обертання бублика
// градуси обертання бублика
long int spin = 0;
long int spin2 = 0;
// змінна для зберігання часу пройденого від
// останнього намальованого кадру.
long int timestart = getMillisecondsTime();

// ідентифікатор текстури куба
unsigned int ctext{0};

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
    spin2 += deltaTime / 10;

    // обрізаємо значення обертань у проміжок [0,360]
    if (spin > 360) { spin -= 360; }
    if (spin2 > 360) { spin2 -= 360; }

    // зберігаємо поточне значення часу
    timestart = ctime;
}

// функція ініціалізації параметрів OpenGL
void init()
{
    // встановлюємо колір очищення пікселів екрану
    glClearColor (0.0, 0.0, 0.0, 1.0);

    // Детальніше про функцію glEnable у статті http://www.kytok.org.ua/post/glenable
    // вмикаємо розпізнавання глибини
    glEnable(GL_DEPTH_TEST);
    // вмикаємо текстурування
    glEnable(GL_TEXTURE_2D);

    // Генеруємо ідентифікатор текстури в кількості 1 штуки
    // Детальніше про дану функцію у статті http://www.kytok.org.ua/post/glgentextures
    glGenTextures(1, &ctext) ;

    // Робимо її поточною
    // Детальніше про функцію glBindTexture за посиланням http://www.kytok.org.ua/post/glbindtexture
    glBindTexture(GL_TEXTURE_2D, ctext) ;   // 2d texture (x and y size)

    // встановлюємо деякі корисні параметри текстури
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    // Вказуємо на безпосередні дані зображення текстури
    // 2D текстура, рівень деталізації 0 (нормальний), 4-ри компоненти (червоний, зелений, синій і прозорість)
    // ширина і висота зображення (1024х1024), границя 0, RGBA кольорові дані, unsigned char тип і
    // в кінці самі дані текстури.
    // Детальніше про дану функцію у статті http://www.kytok.org.ua/post/glteximage2d
    glTexImage2D(GL_TEXTURE_2D, 0,
                 GL_RGBA,
                 rawTexture::rawTextureWidth,
                 rawTexture::rawTextureHeight,
                 0, GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 rawTexture::rawTextureData);
}

// Процедура відображення OpenGL сцени
void display()
{
    // очищуємо буфер пікселів екрану
    // раніше встановленим за допомогою glClearColor
    // Детальніше про дану функцію у статті http://www.kytok.org.ua/post/glclear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // зберігаємо поточну матрицю у стеку матриць
    // і дублюємо її для редагування
    // Детальніше про дану функцію http://www.kytok.org.ua/post/glpushmatrix-glpopmatrix
    glPushMatrix();

    // вмикаємо нашу єдину текстуру куба
    // Детальніше про функцію glBindTexture за посиланням http://www.kytok.org.ua/post/glbindtexture
    glBindTexture (GL_TEXTURE_2D, ctext);

    // обертаємо поточну матрицю
    // Деталі за посиланням http://www.kytok.org.ua/post/glrotate
    glRotatef(spin, 0.0, 1.0, 0.0);
    // також обертаємо навколо X вісі
    glRotatef(spin2, 1.0, 0.0, 0.0);

    // Розпочинаємо малювання трихвимірного об'єкта
    // який складається з квадратів
    // Деталі за посиланням http://www.kytok.org.ua/post/glbegin
    glBegin(GL_QUADS);

    // використовуємо функцію OpenGL glVertex3f для відмальовування куба
    // кожна трійка чисел це координати граней куба у 3D просторі.
    // кожні 4 виклики glVertex3f це один квадрат, з якого складається куб.
    // Детальніше про glVertex3f за посиланням http://www.kytok.org.ua/post/glvertex

    // Функція glTexCoord2f вказує на координати точки початку на текстурі
    // Детальніше про glTexCoord2f у статті-перекладі http://www.kytok.org.ua/post/gltexcoord

    glTexCoord2f(0.0138,0.3196);
    glVertex3f(100,  -100,  -100);

    glTexCoord2f(0.3196,0.3196);
    glVertex3f(100,  -100, 100);

    glTexCoord2f(0.3196,0.0138);
    glVertex3f( -100,  -100, 100);

    glTexCoord2f(0.0138,0.0138);
    glVertex3f( -100,  -100,  -100);

    glTexCoord2f(0.6529,0.6529);
    glVertex3f(100, 100, -100);

    glTexCoord2f(0.6529,0.3471);
    glVertex3f( -100, 100,  -100);

    glTexCoord2f(0.3471,0.3471);
    glVertex3f( -100, 100, 100);

    glTexCoord2f(0.3471,0.6529);
    glVertex3f(100, 100, 100);

    glTexCoord2f(0.6529,0.6804);
    glVertex3f(100,  -100,  -100);

    glTexCoord2f(0.3471,0.6804);
    glVertex3f(100, 100, -100);

    glTexCoord2f(0.3471,0.9862);
    glVertex3f(100, 100, 100);

    glTexCoord2f(0.6529,0.9862);
    glVertex3f(100,  -100, 100);

    glTexCoord2f(0.0138,0.6804);
    glVertex3f(100,  -100, 100);

    glTexCoord2f(0.0138,0.9862);
    glVertex3f(100, 100, 100);

    glTexCoord2f(0.3196,0.9862);
    glVertex3f( -100, 100, 100);

    glTexCoord2f(0.3196,0.6804);
    glVertex3f( -100,  -100, 100);

    glTexCoord2f(0.9862,0.6804);
    glVertex3f( -100,  -100, 100);

    glTexCoord2f(0.6804,0.6804);
    glVertex3f( -100, 100, 100);

    glTexCoord2f(0.6804,0.9862);
    glVertex3f( -100, 100,  -100);

    glTexCoord2f(0.9862,0.9862);
    glVertex3f( -100,  -100,  -100);

    glTexCoord2f(0.0138,0.6529);
    glVertex3f(100, 100, -100);

    glTexCoord2f(0.3196,0.6529);
    glVertex3f(100,  -100,  -100);

    glTexCoord2f(0.3196,0.3471);
    glVertex3f( -100,  -100,  -100);

    glTexCoord2f(0.0138,0.3471);
    glVertex3f( -100, 100,  -100);

    // завершуємо вказування координат трьохвимірного об'єкту
    // Деталі за посиланням http://www.kytok.org.ua/post/glbegin
    glEnd();

    // витягуємо оригінальну матрицю зі стеку матриць
    // Детальніше про дану функцію http://www.kytok.org.ua/post/glpushmatrix-glpopmatrix
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
    // Детальніше про дану функцію за посиланням http://www.kytok.org.ua/post/glviewport
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    // встановлюжмо режим матриці у GL_PROJECTION
    // Детальніше про дану функцію за посиланням http://www.kytok.org.ua/post/glmatrixmode
    glMatrixMode(GL_PROJECTION);
    // Встановлюємо матрицю ідентичності
    // Детальніше про дану функцію за посиланням http://www.kytok.org.ua/post/glloadidentity
    glLoadIdentity();

    // Встановлюємо параметри проекції
    // Детальніше про дану функцію за посиланням http://www.kytok.org.ua/post/glortho
    glOrtho(-w/2.f, w/2.f, -h/2.f, h/2.f, -1000.0, 1000.0);

    // Встановлюємо режим огляду моделі
    glMatrixMode(GL_MODELVIEW);

    // завантажуємо матрицю ідентичності
    // Детальніше про дану функцію за посиланням http://www.kytok.org.ua/post/glloadidentity
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