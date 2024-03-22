# FreeGLUT - швидкий старт

Вихідний код для статті на kytok.org.ua про бібліотеку FreeGLUT.

# Наявні програми

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