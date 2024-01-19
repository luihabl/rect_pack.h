cmake_minimum_required(VERSION 3.20)
project(rect_pack)

option(BUILD_TESTS "Build tests" OFF)

add_library(rect_pack INTERFACE rect_pack.h)
target_include_directories(rect_pack INTERFACE .)

if(BUILD_TESTS)
add_subdirectory(tests)
target_link_libraries(rect_pack_test PRIVATE rect_pack)
endif()