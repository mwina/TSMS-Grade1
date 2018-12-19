cmake_minimum_required(VERSION 3.12)
project(source)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(source
        backup/database.c
        data.db
        datastruct.h
        dboperation.c
        dboperation.h
        includeheaders.h
        main.c
        menu.c
        menu.h
        salarycalculate.c
        salarycalculate.h
        softio.c
        softio.h
        sqlite3.c
        sqlite3.h)
