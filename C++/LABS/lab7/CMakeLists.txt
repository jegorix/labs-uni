cmake_minimum_required(VERSION 3.30)
project(lab7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w") 

add_executable(lab7
        main.cpp
        src/Menu.cpp
        src/Ring.cpp
        src/File.cpp
        src/Shkolnik.cpp
        src/Student.cpp
        src/Uchaschiysya.cpp
        src/Exceptions.cpp
        src/InputUtils.cpp
)
