cmake_minimum_required(VERSION 3.31)
project(Generating_Random_Numbers_Using_Mersenne_Twister)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Weffc++ -Wshadow=global -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Weffc++ -Wshadow=global")

add_executable(Generating_Random_Numbers_Using_Mersenne_Twister main.cpp)
