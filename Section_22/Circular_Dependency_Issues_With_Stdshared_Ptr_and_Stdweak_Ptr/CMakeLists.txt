cmake_minimum_required(VERSION 3.31)
project(Circular_Dependency_Issues_With_Stdshared_Ptr_and_Stdweak_Ptr)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Weffc++ -Wshadow=global -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Weffc++ -Wshadow=global")

add_executable(Circular_Dependency_Issues_With_Stdshared_Ptr_and_Stdweak_Ptr main.cpp)
