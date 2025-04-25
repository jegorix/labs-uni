cmake_minimum_required(VERSION 3.30)
project(13lab C)

set(CMAKE_C_STANDARD 11)

add_executable(13lab main.c validators.c tree_lobby.c default_tree.c tree_functions.c find_repeats.c)
