cmake_minimum_required(VERSION 2.8)

project(dijkstra_test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(CMAKE_CXX_FLAGS " -O3 ")

add_subdirectory(src)