cmake_minimum_required(VERSION 3.11)
project(ArithmeticOperations)           # name ofr project

set(CMAKE_CXX_STANDARD 17)              # c++ 17
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # if not c++ 17 - doesn't try compile
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic -fsanitize=address -fsanitize=undefined")


add_executable(ArithmeticOperations
    main.cpp
    arithmetic_operations.cpp
)

