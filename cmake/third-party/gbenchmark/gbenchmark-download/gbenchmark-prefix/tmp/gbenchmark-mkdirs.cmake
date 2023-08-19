# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/babe/Desktop/hexl/cmake/third-party/gbenchmark/gbenchmark-src"
  "/Users/babe/Desktop/hexl/cmake/third-party/gbenchmark/gbenchmark-build"
  "/Users/babe/Desktop/hexl/cmake/third-party/gbenchmark/gbenchmark-download/gbenchmark-prefix"
  "/Users/babe/Desktop/hexl/cmake/third-party/gbenchmark/gbenchmark-download/gbenchmark-prefix/tmp"
  "/Users/babe/Desktop/hexl/cmake/third-party/gbenchmark/gbenchmark-download/gbenchmark-prefix/src/gbenchmark-stamp"
  "/Users/babe/Desktop/hexl/cmake/third-party/gbenchmark/gbenchmark-download/gbenchmark-prefix/src"
  "/Users/babe/Desktop/hexl/cmake/third-party/gbenchmark/gbenchmark-download/gbenchmark-prefix/src/gbenchmark-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/babe/Desktop/hexl/cmake/third-party/gbenchmark/gbenchmark-download/gbenchmark-prefix/src/gbenchmark-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/babe/Desktop/hexl/cmake/third-party/gbenchmark/gbenchmark-download/gbenchmark-prefix/src/gbenchmark-stamp${cfgdir}") # cfgdir has leading slash
endif()
