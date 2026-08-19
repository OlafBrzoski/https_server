cmake_minimum_required(VERSION 4.0)

project(HttpSerwer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

add_executable(serwer 
    src/main.cpp 
    src/http_parser.cpp
    src/router.cpp
)

target_include_directories(serwer PRIVATE include)


# --- KONFIGURACJA TESTÓW ---
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests tests/test_parser.cpp src/http_parser.cpp)

target_link_libraries(run_tests GTest::gtest_main)
target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

