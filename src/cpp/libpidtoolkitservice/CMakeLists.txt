list(APPEND gos_pid_toolkit_service_cpp_library_source
  "subscriptions.cpp"
  "options.cpp"
  "setting.cpp"
  "service.cpp"
  "topics.cpp")

list(APPEND gos_pid_toolkit_service_cpp_library_include
  ${gos_pid_toolkit_lib_mqtt_include}
  ${Boost_INCLUDE_DIRS})

list(APPEND gos_pid_toolkit_service_cpp_library_definitions
  ${gos_pid_toolkig_cpp_definitions})

add_library(${gos_pid_toolkit_service_cpp_library_target}
  ${gos_pid_toolkit_service_cpp_library_source})

target_compile_definitions(${gos_pid_toolkit_service_cpp_library_target} PUBLIC
  ${gos_pid_toolkit_service_cpp_library_definitions})

if(CLANG_TIDY_EXE)
  set_target_properties(${gos_pid_toolkit_service_cpp_library_target} PROPERTIES
    CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
endif()

target_include_directories(${gos_pid_toolkit_service_cpp_library_target} PUBLIC
  ${gos_pid_toolkit_service_cpp_library_include}
  ${gos_pid_toolkit_cpp_include})

if (gos_pid_toolkit_service_cpp_public_header)
  set_target_properties(${gos_pid_toolkit_service_cpp_library_target}
    PROPERTIES PUBLIC_HEADER
    "${gos_pid_toolkit_service_cpp_public_header}")
endif ()

install(TARGETS ${gos_pid_toolkit_service_cpp_library_target}
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/cpp/gos/pid/toolkit/service
  ARCHIVE DESTINATION lib)
