cmake_minimum_required(VERSION 3.30)
project(8lab C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(8lab
        file_utils.c
        file_utils.h
        filework_menu.c
        filework_menu.h
        main.c
        validators.c
        validators.h)
