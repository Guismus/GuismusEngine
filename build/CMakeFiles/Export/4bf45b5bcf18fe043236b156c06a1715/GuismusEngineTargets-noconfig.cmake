#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "GuismusEngine::GuismusEngine" for configuration ""
set_property(TARGET GuismusEngine::GuismusEngine APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(GuismusEngine::GuismusEngine PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libGuismusEngine.so"
  IMPORTED_SONAME_NOCONFIG "libGuismusEngine.so"
  )

list(APPEND _cmake_import_check_targets GuismusEngine::GuismusEngine )
list(APPEND _cmake_import_check_files_for_GuismusEngine::GuismusEngine "${_IMPORT_PREFIX}/lib/libGuismusEngine.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
