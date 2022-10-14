cmake_minimum_required(VERSION 3.23)
project(projetC C)

set(CMAKE_C_STANDARD 99)

add_executable(projetC src/main.c src/list.c src/list.h src/llist.c src/llist.h)
