cmake_minimum_required(VERSION 3.5)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
find_package(Catch2 REQUIRED)

set(TEST_FILES ../test_phys.cpp)

set(SOURCE_FILES
    ../../src/vectors.cpp
    ../../src/kinematics.cpp
    ../../src/rigidbody.h
    ../../src/vectors.h
    ../../src/point.h)

add_executable(test_phys ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(test_phys Catch2::Catch2)
