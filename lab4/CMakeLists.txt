cmake_minimum_required(VERSION 3.22)
project(rubiks_cube)

set(CMAKE_CXX_STANDARD 23)

add_executable(rubiks_cube main.cpp cube.h solver.h cube.cpp solver.cpp)
target_link_libraries(rubiks_cube -lOpenGL32 -lfreeGLUT -lglu32  -lopengl32)