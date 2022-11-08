#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "motor_actuator::motor_actuator" for configuration ""
set_property(TARGET motor_actuator::motor_actuator APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(motor_actuator::motor_actuator PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libmotor_actuator.so"
  IMPORTED_SONAME_NOCONFIG "libmotor_actuator.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS motor_actuator::motor_actuator )
list(APPEND _IMPORT_CHECK_FILES_FOR_motor_actuator::motor_actuator "${_IMPORT_PREFIX}/lib/libmotor_actuator.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
