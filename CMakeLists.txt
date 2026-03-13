cmake_minimum_required(VERSION 3.20)
project(terminalChess)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(terminalChess src/main.cpp)


target_compile_options(terminalChess PRIVATE -Wall -Wextra -Wpedantic)