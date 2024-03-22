# FreeGLUT - швидкий старт

Вихідний код для статті на http://www.kytok.org.ua/post/freeglut-and-opengl-lehkyj-start про бібліотеку FreeGLUT.

# Наявні програми

Щоб команди побудови працювали, спочатку необхідно склонувати (або завантажити) проект на свій комп'ютер за допомогою команди:

```
git clone https://github.com/yuriysydor1991/freeglut-fast-start-article-resources.git
```

Після чого зайти у директорію проекту за допомогою команди

```
cd freeglut-fast-start-article-resources
```

## blank-window

В субдиректорії blank-window розміщений приклад найпростішої OpenGL/FreeGLUT програми для показу пустого вікна заповненого чорним кольором розміром 500x500 пікселів.

Щоб збудувати і запустити програму необхідно пройти в командному рядку у корінь проекту і ввести наступні команди:

```
rm -fr build
mkdir -vp build
cd build
cmake ../ 
cmake --build blank-window 
./blank-window/blank-window
```

## torus-window

В піддиректорії torus-window розміщений приклад відмальовування каркасу бублика на чорному фоні з ротацією в залежності від часу.

Щоб збудувати і запустити програму необхідно пройти в командному рядку у корінь проекту і ввести наступні команди:

```
rm -fr build
mkdir -vp build
cd build
cmake ../ 
cmake --build torus-window 
./torus-window/torus-window
```