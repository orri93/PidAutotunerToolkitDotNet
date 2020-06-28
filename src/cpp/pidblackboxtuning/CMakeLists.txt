list(APPEND gos_pid_black_box_tuning_source
  "pidblackboxtuning.cpp")

list(APPEND gos_pid_black_box_tuning_include
  ${gos_pid_toolkit_cpp_include}
  ${extern_libmodbus_include}
  ${Boost_INCLUDE_DIRS})

list(APPEND gos_pid_black_box_tuning_libraries
  ${gos_pid_arduino_modbus_master_library_target}
  ${gos_pid_tuning_black_box_library_target}
  ${gos_pid_toolkit_cpp_library_target}
  ${gos_pid_toolkit_lib_modbus_lib}
  Boost::program_options
  Boost::filesystem
  Boost::date_time
# Boost::log_setup
  Boost::regex)

if (WIN32)
  list(APPEND gos_pid_black_box_tuning_libraries ws2_32)
endif ()

list(APPEND gos_pid_black_box_tuning_definitions
  NOMINMAX)

add_executable(${gos_pid_black_box_tuning_target}
  ${gos_pid_black_box_tuning_source} )

target_compile_definitions(${gos_pid_black_box_tuning_target} PUBLIC
  ${gos_pid_black_box_tuning_definitions})

target_include_directories(${gos_pid_black_box_tuning_target} PUBLIC
  ${gos_pid_black_box_tuning_include})

target_link_libraries(${gos_pid_black_box_tuning_target}
  ${gos_pid_black_box_tuning_libraries})

if(GOS_DEPLOY_PDB_FILES)
  install(FILES "$<TARGET_PDB_FILE:${gos_pid_black_box_tuning_target}>"
    DESTINATION pdb
    COMPONENT pdb)
endif()

install(TARGETS ${gos_pid_black_box_tuning_target}
# CONFIGURATIONS etc
  RUNTIME DESTINATION bin/tuning)
