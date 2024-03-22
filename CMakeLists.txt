cmake_minimum_required(VERSION 3.22.1)

project(
        FreeGLUT_fast_start
        VERSION 0.0.1
        DESCRIPTION "A quick start for the FreeGLUT library with examples"
        HOMEPAGE_URL "http://www.kytok.org.ua/"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(blank-window)
add_subdirectory(torus-window)
