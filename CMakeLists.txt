cmake_minimum_required(VERSION 3.5)
project(Physics)

set(CMAKE_CXX_STANDARD 11)
include_directories(${Physics_SOURCE_DIR}/src
                    ${Physics_SOURCE_DIR}/test)

set(Physics_SOURCES
    ${Physics_SOURCE_DIR}/src/vectors.cpp
    ${Physics_SOURCE_DIR}/src/kinematics.cpp
    ${Physics_SOURCE_DIR}/src/rigidbody.h
    ${Physics_SOURCE_DIR}/src/point.h)

set(Test_SOURCES
    ${Physics_SOURCES}
    ${Physics_SOURCE_DIR}/test/test_phys.cpp
    ${Physics_SOURCE_DIR}/test/catch.hpp)

add_executable(Physics ${Physics_SOURCES} ${Physics_SOURCE_DIR}/src/main.cpp)
add_executable(test_phys ${Test_SOURCES})
