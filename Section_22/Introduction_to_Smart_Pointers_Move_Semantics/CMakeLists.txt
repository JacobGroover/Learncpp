cmake_minimum_required(VERSION 3.31)
project(Introduction_to_Smart_Pointers_Move_Semantics)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Weffc++ -Wshadow=global -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Weffc++ -Wshadow=global")

add_executable(Introduction_to_Smart_Pointers_Move_Semantics main.cpp)
