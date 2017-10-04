cmake_minimum_required(VERSION 3.6)
project(Shell_Project)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c environment.c command_parser.c commands.c file_processing.c variables.c)
add_executable(Shell_Project ${SOURCE_FILES})