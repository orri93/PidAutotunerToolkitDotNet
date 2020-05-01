list(APPEND gos_pid_arduino_modbus_master_source
  "options.cpp"
  "master.cpp"
  "retry.cpp")

add_library(${gos_pid_arduino_modbus_master_library_target}
  ${gos_pid_arduino_modbus_master_source})

if(CLANG_TIDY_EXE)
  set_target_properties(${gos_pid_arduino_modbus_master_library_target}
    PROPERTIES CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
endif()

target_include_directories(
  ${gos_pid_arduino_modbus_master_library_target} PUBLIC
  ${Boost_INCLUDE_DIRS}
  ${gos_pid_toolkit_cpp_include}
  ${gos_pid_toolkit_lib_modbus_include})

set_target_properties(${gos_pid_arduino_modbus_master_library_target} PROPERTIES
  PUBLIC_HEADER ${gos_pid_arduino_modbus_master_cpp_library_public_header})

install(TARGETS ${gos_pid_arduino_modbus_master_library_target}
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/gos/pid/arduino/modbus
  ARCHIVE DESTINATION lib)
