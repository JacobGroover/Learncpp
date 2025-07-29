cmake_minimum_required(VERSION 3.31)
project(The_Override_and_Final_Specifiers_and_Covariant_Return_Types)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Weffc++ -Wshadow=global -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Weffc++ -Wshadow=global")

add_executable(The_Override_and_Final_Specifiers_and_Covariant_Return_Types main.cpp)
