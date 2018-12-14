cmake_minimum_required(VERSION 3.5)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
find_package(Catch2 REQUIRED)

set(TEST_FILES ../test_phys.cpp)

set(SOURCE_FILES
    ../../src/vectors.cpp
    ../../src/polygon.cpp
    ../../src/projectile.cpp)

add_executable(test_phys ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(test_phys Catch2::Catch2)
