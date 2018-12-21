cmake_minimum_required(VERSION 3.12)
project(testdb C)

set(CMAKE_C_STANDARD 99)

add_executable(testdb
        main.c
        sqlite3.c
        sqlite3.h
        )