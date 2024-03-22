cmake_minimum_required(VERSION 3.22.1)

add_executable(
        torus-window
        main.cpp
)

include_directories(${GLUT_INCLUDE_DIRS})

target_link_libraries(torus-window ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})