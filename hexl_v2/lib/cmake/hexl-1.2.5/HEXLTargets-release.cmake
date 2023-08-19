#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "HEXL::hexl" for configuration "Release"
set_property(TARGET HEXL::hexl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(HEXL::hexl PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libhexl.1.2.5.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libhexl.1.2.5.dylib"
  )

list(APPEND _cmake_import_check_targets HEXL::hexl )
list(APPEND _cmake_import_check_files_for_HEXL::hexl "${_IMPORT_PREFIX}/lib/libhexl.1.2.5.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
