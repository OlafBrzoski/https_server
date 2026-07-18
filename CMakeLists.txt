cmake_minimum_required(VERSION 4.0)

project(server_https)

set(CMAKE_CXX_STANDARD 20)
find_package(OpenSSL REQUIRED)
target_link_libraries(server_https PRIVATE OpenSSL::SSL)
target_link_libraries(server_https PRIVATE OpenSSL::Crypto)

add_executable(server_https server.cpp)
