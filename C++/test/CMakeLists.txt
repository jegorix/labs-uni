cmake_minimum_required(VERSION 3.10)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем путь к заголовочным файлам
include_directories(include)

add_executable(
    MyProject 
    main.cpp
    src/Student.cpp
    src/Money.cpp
)