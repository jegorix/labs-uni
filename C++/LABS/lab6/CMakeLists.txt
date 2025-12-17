cmake_minimum_required(VERSION 3.30)
project(laba)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w") 

add_executable(laba
        main.cpp
        src/Menu.cpp
        src/Ring.cpp
        src/models/Shkolnik.cpp
        src/models/Student.cpp
        src/models/Uchaschiysya.cpp
        src/files/File.cpp
        src/utils/InputUtils.cpp
        exceptions/src/Exception.cpp
        exceptions/src/InputException.cpp
        exceptions/src/FileException.cpp
        exceptions/src/ContainerException.cpp
        src/files/TextFile.tpp
        src/files/BinaryFile.tpp
)
