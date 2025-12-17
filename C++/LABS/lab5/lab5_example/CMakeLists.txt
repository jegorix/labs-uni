cmake_minimum_required(VERSION 3.10)
project(lab5)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

set(SOURCES
    models/src/Human.cpp
    models/src/Teacher.cpp
    models/src/CommissionMember.cpp
    models/src/TeacherCommissionMember.cpp
    templates/include/Deque.tpp
    exceptions/src/Exception.cpp
    exceptions/src/InputException.cpp
    exceptions/src/FileException.cpp
    exceptions/src/ContainerException.cpp
    exceptions/src/Date.cpp
    exceptions/src/InputHandler.cpp
    main/main.cpp
)

set(HEADERS
    models/include/Human.hpp
    models/include/Teacher.hpp
    models/include/CommissionMember.hpp
    models/include/TeacherCommissionMember.hpp
    templates/include/Deque.hpp
    exceptions/include/Exception.hpp
    exceptions/include/InputException.hpp
    exceptions/include/FileException.hpp
    exceptions/include/ContainerException.hpp
    exceptions/include/Date.hpp
    exceptions/include/InputHandler.hpp
)

add_executable(lab5 ${SOURCES} ${HEADERS})