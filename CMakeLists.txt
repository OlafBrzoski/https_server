cmake_minimum_required(VERSION 4.0)

project(HttpSerwer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_executable(serwer 
    src/main.cpp 
    src/http_parser.cpp
)

target_include_directories(serwer PRIVATE include)
