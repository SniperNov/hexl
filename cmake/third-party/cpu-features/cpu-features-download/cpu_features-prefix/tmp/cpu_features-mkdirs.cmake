# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-src"
  "/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-build"
  "/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix"
  "/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/tmp"
  "/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/src/cpu_features-stamp"
  "/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/src"
  "/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/src/cpu_features-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/src/cpu_features-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/babe/Desktop/hexl/cmake/third-party/cpu-features/cpu-features-download/cpu_features-prefix/src/cpu_features-stamp${cfgdir}") # cfgdir has leading slash
endif()
