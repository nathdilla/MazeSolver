cmake_minimum_required(VERSION 3.20)
project(MazeSolver)

set(CMAKE_CXX_STANDARD 14)

add_executable(MazeSolver MazeCell.h Source.cpp myStack.h MyQ.h)
