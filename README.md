# FreeGLUT - швидкий старт

Вихідний код для статті на http://www.kytok.org.ua/post/freeglut-and-opengl-lehkyj-start про бібліотеку FreeGLUT.

Щоб команди побудови працювали, спочатку необхідно клонувати (або завантажити) проект на свій комп'ютер за допомогою команди:

# Встановлення необхідних пакунків і програм

Для того щоб на комп'ютері з'явилалсь можливість запускати приклади даного проекту необхідно мати відповідний інструментарій.

Для того щоб встановити необхідні програми на системах Debian/Ubuntu/Mint Linux або подібних необхідно виконати наступну команду.

```
sudo apt-get install -y cmake g++ make git
```

Для інших систем можливо використання наявного менеджера пакунків і пошуком відповідних назв необхідних програм.

# Отримання копії проекту прикладів

```
git clone https://github.com/yuriysydor1991/freeglut-fast-start-article-resources.git
```

Після чого зайти у директорію проекту за допомогою команди

```
cd freeglut-fast-start-article-resources
```

# Наявні програми

У наявних піддиректоріях розміщені приклади з демонстраційним кодом.

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

## teapot-window

В даній директорії розміщений приклад відмальовування 3D-чайника. 

Щоб збудувати даний приклад необхідно з кореня директорії проекту виконати наступні команди:

```
rm -fr build
mkdir -vp build
cd build
cmake ../ 
cmake --build teapot-window 
./torus-window/teapot-window
```

## vertex-cube-window

Даний приклад призначений для малювання і текстурування 3D-об'єкту, а саме куба на екрані.

Щоб побудувати даний приклад необхідно скористатись наступними командами.

```
git clone https://github.com/yuriysydor1991/freeglut-fast-start-article-resources.git
cd freeglut-fast-start-article-resources
mkdir -vp build
cd build
cmake ../
cmake --build vertex-cube-window
./vertex-cube-window/vertex-cube-window
```
