cmake_minimum_required(VERSION 3.22)
set(CMAKE_C_STANDARD 90)

# Default CLion generated
project(assembler)
add_executable(assembler
                preprocessor.c preprocessor.h
                utils.c utils.h
                macroList.c macroList.h)

## math library, gcc option -lm
target_link_libraries(assembler)

## add warning flags -pedantic -Wall
set (CMAKE_CXX_FLAGS "-ansi -pedantic -Wall")

# Using makefile for compilation
project(assembler)
add_custom_target(assembler COMMAND make -C ${assembler_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR})

