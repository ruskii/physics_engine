cmake_minimum_required(VERSION 3.5)
project(Physics)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    main.cpp
    vectors.cpp
    kinematics.cpp
    rigidbody.h
    point.h)

add_executable(phys ${SOURCE_FILES})
