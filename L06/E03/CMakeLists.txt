cmake_minimum_required(VERSION 3.22)
project(Lab6_3 C)

set(CMAKE_C_STANDARD 99)

add_executable(Lab6_3
        gdr.c
        inv.c inv.h
        invArray.h
        equipArray.h
        pg.c pg.h
        pgList.h pgList.c invArray.c equipArray.c)
