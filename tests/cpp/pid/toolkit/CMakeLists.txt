list(APPEND gos_pid_toolkit_cpp_test_source
  stability.cpp)

set(gos_pid_toolkit_cpp_test_target gospidtoolkitcpptest)

add_executable(${gos_pid_toolkit_cpp_test_target}
  ${gos_pid_toolkit_cpp_test_source})

target_include_directories(${gos_pid_toolkit_cpp_test_target} PUBLIC
  ${gos_pid_toolkit_unit_testing_gmock_include_dir}
  ${gos_pid_toolkit_unit_testing_gtest_include_dir}
  ${gos_pid_toolkit_cpp_include}
  ${Boost_INCLUDE_DIRS})

#target_compile_definitions(${gos_pid_toolkit_cpp_test_target} PUBLIC
#  SOME_DEF)

target_link_libraries(${gos_pid_toolkit_cpp_test_target}
  Boost::serialization
  ${gos_pid_toolkit_cpp_library_target}
  ${gos_pid_toolkit_gtest_libraries})

#if(CLANG_TIDY_EXE)
#  set_target_properties(${gos_pid_toolkit_cpp_test_target} PROPERTIES
#    CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
#endif()

add_test(NAME gos_pid_toolkit_cpp_test COMMAND
  ${gos_pid_toolkit_cpp_test_target})

add_subdirectory(ui)
