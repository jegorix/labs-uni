cmake_minimum_required(VERSION 3.30)
project(lab1)  # Исправлено: простое имя проекта

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1  # Исправлено: простое имя исполняемого файла
        main.cpp
        string_subtractor.cpp
)