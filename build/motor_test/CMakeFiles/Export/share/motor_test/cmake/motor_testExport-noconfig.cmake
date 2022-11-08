#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "motor_test::motor_test" for configuration ""
set_property(TARGET motor_test::motor_test APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(motor_test::motor_test PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmotor_test.so"
  IMPORTED_SONAME_NOCONFIG "libmotor_test.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS motor_test::motor_test )
list(APPEND _IMPORT_CHECK_FILES_FOR_motor_test::motor_test "${_IMPORT_PREFIX}/lib/libmotor_test.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
