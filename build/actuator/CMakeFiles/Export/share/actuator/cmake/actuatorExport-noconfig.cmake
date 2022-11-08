#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "actuator::actuator" for configuration ""
set_property(TARGET actuator::actuator APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(actuator::actuator PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libactuator.so"
  IMPORTED_SONAME_NOCONFIG "libactuator.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS actuator::actuator )
list(APPEND _IMPORT_CHECK_FILES_FOR_actuator::actuator "${_IMPORT_PREFIX}/lib/libactuator.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
