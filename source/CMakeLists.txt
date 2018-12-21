# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.12)
project(source C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(source
        dboperation.c
        dboperation.h
        includeheaders.c
        includeheaders.h
        main.c
        softio.c
        softio.h
        sqlite3.c
        sqlite3.h)
