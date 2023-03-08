#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "scip" for configuration "Release"
set_property(TARGET scip APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(scip PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/scip.exe"
  )

list(APPEND _IMPORT_CHECK_TARGETS scip )
list(APPEND _IMPORT_CHECK_FILES_FOR_scip "${_IMPORT_PREFIX}/bin/scip.exe" )

# Import target "libscip" for configuration "Release"
set_property(TARGET libscip APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libscip PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/libscip.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/libscip.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS libscip )
list(APPEND _IMPORT_CHECK_FILES_FOR_libscip "${_IMPORT_PREFIX}/lib/libscip.lib" "${_IMPORT_PREFIX}/bin/libscip.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
