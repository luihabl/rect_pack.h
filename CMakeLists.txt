cmake_minimum_required(VERSION 3.20)
project(rect_pack)

option(BUILD_EXAMPLES "Build examples" OFF)

add_library(rect_pack INTERFACE rect_pack.h)
target_include_directories(rect_pack INTERFACE .)

if(BUILD_EXAMPLES)
add_subdirectory(examples)
endif()