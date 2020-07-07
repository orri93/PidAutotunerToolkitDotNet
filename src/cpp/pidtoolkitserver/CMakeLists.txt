list(APPEND gos_pid_server_source
  "pidtoolkitserver.cpp")

if(WIN32 AND GOS_PID_TOOLKIT_WINDOWS_SERVICE)
  if ("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
    # this path is only present for 2008+, but we currently require PATH to
    # be set up anyway
    get_filename_component(sdk_dir "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Microsoft SDKs\\Windows;CurrentInstallFolder]" REALPATH)
    get_filename_component(kit_dir "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots;KitsRoot]" REALPATH)
    get_filename_component(kit81_dir "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots;KitsRoot81]" REALPATH)
    if (X64)
      set(sdk_bindir "${sdk_dir}/bin/x64")
      set(kit_bindir "${kit_dir}/bin/x64")
      set(kit81_bindir "${kit81_dir}/bin/x64")
    else (X64)
      set(sdk_bindir "${sdk_dir}/bin")
      set(kit_bindir "${kit_dir}/bin/x86")
      set(kit81_bindir "${kit81_dir}/bin/x86")
    endif (X64)
  endif ()
  find_program(CMAKE_MC_COMPILER mc.exe HINTS "${sdk_bindir}" "${kit_bindir}" "${kit81_bindir}"
    DOC "path to message compiler")

  set(gos_pid_server_win_mc "${CMAKE_CURRENT_SOURCE_DIR}/pidtoolkitservice.mc")
  set(gos_pid_server_win_mc_header "${CMAKE_CURRENT_BINARY_DIR}/pidtoolkitservice.h")
  add_custom_command(
    OUTPUT ${gos_pid_server_win_mc_header}
    COMMAND ${CMAKE_MC_COMPILER} ${gos_pid_server_win_mc}
    DEPENDS ${SOURCE_FILES} ${CMAKE_MC_COMPILER} ${gos_pid_server_win_mc}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

  list(APPEND gos_pid_server_source
    ${gos_pid_server_win_mc_header}
    "win/installer.cpp"
    "winsvc.cpp")
  
  message(STATUS "")
  message(STATUS "PID Toolkit Windows Service BUILD SUMMARY")
  message(STATUS "  MC Compiler  : ${CMAKE_MC_COMPILER}")
  message(STATUS "  MC Input     : ${gos_pid_server_win_mc}")
  message(STATUS "  MC Output    : ${gos_pid_server_win_mc_header}")

else()
  list(APPEND gos_pid_server_source "pidtoolkitserver.cpp")
endif()

list(APPEND gos_pid_server_include
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${gos_pid_toolkit_cpp_include}
  ${extern_libmodbus_include}
  ${Boost_INCLUDE_DIRS})

list(APPEND gos_pid_server_libraries
  ${gos_pid_toolkit_service_cpp_library_target}
  ${gos_pid_arduino_modbus_master_library_target}
  ${gos_pid_tuning_black_box_library_target}
  ${gos_pid_toolkit_cpp_library_target}
  ${gos_pid_toolkit_lib_mqtt_library}
  ${gos_pid_toolkit_lib_modbus_lib}
  ${gos_pid_toolkit_boost_libraries})

if (WIN32)
  list(APPEND gos_pid_server_libraries
    advapi32
    ws2_32)
endif ()

list(APPEND gos_pid_server_definitions
  ${gos_pid_toolkig_cpp_definitions}
  NOMINMAX)

add_executable(${gos_pid_server_target}
  ${gos_pid_server_source} )

target_compile_definitions(${gos_pid_server_target} PUBLIC
  ${gos_pid_server_definitions})

target_include_directories(${gos_pid_server_target} PUBLIC
  ${gos_pid_server_include})

target_link_libraries(${gos_pid_server_target}
  ${gos_pid_server_libraries})

if(GOS_DEPLOY_PDB_FILES)
  install(FILES "$<TARGET_PDB_FILE:${gos_pid_server_target}>"
    DESTINATION pdb
    COMPONENT pdb)
endif()

install(TARGETS ${gos_pid_server_target}
# CONFIGURATIONS etc
  RUNTIME DESTINATION bin)
