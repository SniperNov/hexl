# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/babe/Desktop/hexl/cmake/third-party/gtest/gtest-src"
  "/Users/babe/Desktop/hexl/cmake/third-party/gtest/gtest-build"
  "/Users/babe/Desktop/hexl/cmake/third-party/gtest/gtest-download/gtest-prefix"
  "/Users/babe/Desktop/hexl/cmake/third-party/gtest/gtest-download/gtest-prefix/tmp"
  "/Users/babe/Desktop/hexl/cmake/third-party/gtest/gtest-download/gtest-prefix/src/gtest-stamp"
  "/Users/babe/Desktop/hexl/cmake/third-party/gtest/gtest-download/gtest-prefix/src"
  "/Users/babe/Desktop/hexl/cmake/third-party/gtest/gtest-download/gtest-prefix/src/gtest-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/babe/Desktop/hexl/cmake/third-party/gtest/gtest-download/gtest-prefix/src/gtest-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/babe/Desktop/hexl/cmake/third-party/gtest/gtest-download/gtest-prefix/src/gtest-stamp${cfgdir}") # cfgdir has leading slash
endif()
