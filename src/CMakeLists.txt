cmake_minimum_required(VERSION 3.2)
project(Physics)

set(CMAKE_CXX_STANDARD 11)
add_executable(Physics main.cpp vectors.cpp kinematics.cpp vectors.h rigidbody.h point.h)
