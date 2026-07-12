cmake_minimum_required(VERSION 3.11)

project(BigInteger)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic -fsanitize=address -fsanitize=undefined")

add_executable(BigInteger main.cpp big_integer.cpp rational.cpp)
