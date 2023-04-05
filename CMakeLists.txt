cmake_minimum_required(VERSION 3.19)
project(CG2023)

set(CMAKE_CXX_STANDARD 20)

add_executable(CG2023 main.cpp vec3.cpp vec3.h Rayo.cpp Rayo.h
        Objeto.cpp Objeto.h Camara.cpp Camara.h Luz.cpp Luz.h)