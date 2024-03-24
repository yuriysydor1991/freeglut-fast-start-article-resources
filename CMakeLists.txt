cmake_minimum_required(VERSION 3.12)

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

include_directories(${GLUT_INCLUDE_DIRS})

link_libraries(${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})

add_subdirectory(blank-window)
add_subdirectory(torus-window)
add_subdirectory(teapot-window)
add_subdirectory(vertex-cube-window)
