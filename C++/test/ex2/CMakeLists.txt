cmake_minimum_required(VERSION 3.10)

project(Money LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем путь к заголовочным файлам
#include_directories(include)

add_executable(
    Money 
    main.cpp
    Money.cpp
)