#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "sensor::sensor" for configuration ""
set_property(TARGET sensor::sensor APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(sensor::sensor PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libsensor.so"
  IMPORTED_SONAME_NOCONFIG "libsensor.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS sensor::sensor )
list(APPEND _IMPORT_CHECK_FILES_FOR_sensor::sensor "${_IMPORT_PREFIX}/lib/libsensor.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
