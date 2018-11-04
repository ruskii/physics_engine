cmake_minimum_required(VERSION 3.5)
project(Physics)

set(CMAKE_CXX_STANDARD 11)
include_directories(${Physics_SOURCE_DIR}/src)

set(Physics_SOURCES
    ${Physics_SOURCE_DIR}/src/main.cpp
    ${Physics_SOURCE_DIR}/src/vectors.cpp
    ${Physics_SOURCE_DIR}/src/kinematics.cpp
    ${Physics_SOURCE_DIR}/src/rigidbody.h
    ${Physics_SOURCE_DIR}/src/point.h)

add_executable(Physics ${Physics_SOURCES})
