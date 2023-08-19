# Copyright (C) 2020 Intel Corporation
# SPDX-License-Identifier: Apache-2.0

project(hexl_omp_example LANGUAGES C CXX)
cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)

# Define the directory containing HEXLConfig.cmake
set(HEXL_HINT_DIR "/Users/babe/Desktop/hexl/hexl_v2/lib/cmake/hexl-1.2.5")

# Example using source
find_package(HEXL 1.2.5
    HINTS ${HEXL_HINT_DIR}
    REQUIRED)
if (NOT TARGET HEXL::hexl)
    message(FATAL_ERROR "TARGET HEXL::hexl not found")
endif()

find_package(OpenMP)
if (OpenMP_FOUND)
    message(STATUS "OpenMP_CXX_INCLUDE_DIRS: ${OpenMP_CXX_INCLUDE_DIRS}")
    message(STATUS "OpenMP_CXX_LIBRARIES: ${OpenMP_CXX_LIBRARIES}")
endif()

add_executable(omp_example ../example.cpp)

target_link_libraries(omp_example PRIVATE HEXL::hexl)

