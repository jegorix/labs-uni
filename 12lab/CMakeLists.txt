cmake_minimum_required(VERSION 3.30)
project(12lab C)

set(CMAKE_C_STANDARD 11)

add_executable(12lab main.c validators.c serve_user.c queue_actions.c deque_actions.c queue_identity.c deep_compare.c)
