cmake_minimum_required(VERSION 3.9)
project(Physics)

set(CMAKE_CXX_STANDARD 11)
add_executable(Physics main.cpp vectors.h rigidbody.h point.h world.h shapes.h)