list(APPEND gos_pid_tuning_black_box_library_source
  "blackbox.cpp"
  "options.cpp"
  "setting.cpp"
  "output.cpp")

list(APPEND gos_pid_tuning_black_box_library_definitions
  ${gos_pid_toolkit_boost_version_definition})

add_library(${gos_pid_tuning_black_box_library_target}
  ${gos_pid_tuning_black_box_library_source})

if(CLANG_TIDY_EXE)
  set_target_properties(${gos_pid_tuning_black_box_library_target} PROPERTIES
    CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
endif()

list(APPEND gos_pid_tuning_black_box_library_include
  ${gos_pid_toolkit_cpp_include}
  ${Boost_INCLUDE_DIRS})

target_include_directories(${gos_pid_tuning_black_box_library_target} PUBLIC
  ${gos_pid_tuning_black_box_library_include})

target_compile_definitions(${gos_pid_tuning_black_box_library_target} PRIVATE
  ${gos_pid_tuning_black_box_library_definitions})

set_target_properties(${gos_pid_tuning_black_box_library_target} PROPERTIES
  PUBLIC_HEADER "${gos_pid_tuning_black_box_library_public_header}")

install(TARGETS ${gos_pid_tuning_black_box_library_target}
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/cpp/gos/pid/tuning
  ARCHIVE DESTINATION lib)
