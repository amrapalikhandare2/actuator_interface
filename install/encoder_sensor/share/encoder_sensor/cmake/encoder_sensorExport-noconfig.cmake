#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "encoder_sensor::encoder_sensor" for configuration ""
set_property(TARGET encoder_sensor::encoder_sensor APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(encoder_sensor::encoder_sensor PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libencoder_sensor.so"
  IMPORTED_SONAME_NOCONFIG "libencoder_sensor.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS encoder_sensor::encoder_sensor )
list(APPEND _IMPORT_CHECK_FILES_FOR_encoder_sensor::encoder_sensor "${_IMPORT_PREFIX}/lib/libencoder_sensor.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
