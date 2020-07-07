list(APPEND gos_pid_toolkit_cpp_library_source
  "exception.cpp"
  "reporting.cpp"
  "parsing.cpp"
  "default.cpp"
  "options.cpp"
  "setting.cpp"
  "version.cpp"
  "console.cpp"
  "serial.cpp"
  "stream.cpp"
  "text.cpp")

list(APPEND gos_pid_toolkit_cpp_include
  ${Boost_INCLUDE_DIRS})

list(APPEND gos_pid_toolkit_cpp_library_definitions
  ${gos_pid_toolkig_cpp_definitions})

add_library(${gos_pid_toolkit_cpp_library_target}
  ${gos_pid_toolkit_cpp_library_source})

target_compile_definitions(${gos_pid_toolkit_cpp_library_target} PUBLIC
  ${gos_pid_toolkit_cpp_library_definitions})

if(CLANG_TIDY_EXE)
  set_target_properties(${gos_pid_toolkit_cpp_library_target} PROPERTIES
    CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
endif()

target_include_directories(${gos_pid_toolkit_cpp_library_target} PUBLIC
  ${gos_pid_toolkit_cpp_include})

#if (GOS_PID_TOOLKIT_DOXYGEN AND DOXYGEN_FOUND)
#  message(STATUS "Doxygen for PID Toolkit requested")
#  doxygen_add_docs(${gos_pid_toolkit_doxygen_target}
#    ${CMAKE_CURRENT_SOURCE_DIR}
#    WORKING_DIRECTORY ${gos_pid_toolkit_doxygen_working_directory})
#endif ()

if (gos_pid_toolkit_cpp_public_header)
  set_target_properties(${gos_pid_toolkit_cpp_library_target}
    PROPERTIES PUBLIC_HEADER
    "${gos_pid_toolkit_cpp_public_header}")
endif ()

install(TARGETS ${gos_pid_toolkit_cpp_library_target}
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/cpp/gos/pid/toolkit
  ARCHIVE DESTINATION lib)
