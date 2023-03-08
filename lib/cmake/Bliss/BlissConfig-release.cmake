#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Bliss::libbliss" for configuration "Release"
set_property(TARGET Bliss::libbliss APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Bliss::libbliss PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/bliss.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Bliss::libbliss )
list(APPEND _IMPORT_CHECK_FILES_FOR_Bliss::libbliss "${_IMPORT_PREFIX}/lib/bliss.lib" )

# Import target "Bliss::bliss" for configuration "Release"
set_property(TARGET Bliss::bliss APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Bliss::bliss PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/bliss.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS Bliss::bliss )
list(APPEND _IMPORT_CHECK_FILES_FOR_Bliss::bliss "${_IMPORT_PREFIX}/bin/bliss.exe" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
