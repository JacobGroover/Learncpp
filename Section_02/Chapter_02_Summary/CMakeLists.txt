cmake_minimum_required(VERSION 3.31)
project(Chapter_02_Summary)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Weffc++ -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Weffc++")

add_executable(Chapter_02_Summary main.cpp
        io.cpp
        io.h)

# Include the directory containing header files
#target_include_directories(MyProject PRIVATE ${CMAKE_SOURCE_DIR}/path/to/your/include)