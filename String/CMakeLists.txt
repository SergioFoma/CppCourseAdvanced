cmake_minimum_required(VERSION 3.11)

project(string)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic -fsanitize=address -fsanitize=undefined")

add_executable(string main.cpp string.cpp)


