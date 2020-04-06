list(APPEND gos_pid_toolkit_cpp_library_source
  "exception.cpp"
  "version.cpp")

add_library(${gos_pid_toolkit_cpp_library_target}
  ${gos_pid_toolkit_cpp_library_source})

list(APPEND gos_pid_toolkit_cpp_include
  ${Boost_INCLUDE_DIRS})

if(CLANG_TIDY_EXE)
  set_target_properties(${gos_pid_toolkit_cpp_library_target} PROPERTIES
    CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
endif()

target_include_directories(${gos_pid_toolkit_cpp_library_target} PUBLIC
  ${gos_pid_toolkit_cpp_include})

if (gos_pid_toolkit_cpp_public_header)
  set_target_properties(${gos_pid_toolkit_cpp_library_target}
    PROPERTIES PUBLIC_HEADER
    "${gos_pid_toolkit_cpp_public_header}")
endif ()

install(TARGETS ${gos_pid_toolkit_cpp_library_target}
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/cpp/gos/pid/toolkit
  ARCHIVE DESTINATION lib)
