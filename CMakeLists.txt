cmake_minimum_required(VERSION 3.26)
project(SDA C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(SDA
        main.c
        models.h
        models.c)
