cmake_minimum_required(VERSION 3.30)
project(lab_3_1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")

add_executable(lab_3_1
        main.cpp
        src/Shkolnik.cpp
        src/Student.cpp
        src/Uchaschiysya.cpp
)
