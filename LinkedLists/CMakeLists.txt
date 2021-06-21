cmake_minimum_required(VERSION 3.19)
project(LinkedLists)

set(CMAKE_CXX_STANDARD 98)

add_executable(LinkedLists main.cpp Node.h List.h SimpleNode.h algorithms.h algorithms.cpp)