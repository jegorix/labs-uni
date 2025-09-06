cmake_minimum_required(VERSION 3.30)
project(10lab C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(10lab
        output/byte_fields_1.c
        byte_fields_1.c
        main.c
        struct_task_1.c
        struct_task_2.c
        validators.c
        validators.h)
