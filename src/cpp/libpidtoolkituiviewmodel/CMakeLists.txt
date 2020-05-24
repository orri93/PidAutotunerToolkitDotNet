list(APPEND gos_pid_toolkit_ui_view_model_cpp_library_source
  "blackbox.cpp"
  "modbus.cpp"
  "tuning.cpp")

find_package(Qt5 COMPONENTS REQUIRED
  QuickControls2
  SerialPort
  Quick
  Core
  Gui
  Qml)

list(APPEND gos_pid_toolkit_ui_view_model_cpp_library_include
  ${gos_pid_toolkit_cpp_include}
  ${QtSerialPort_INCLUDE_DIRS}
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Qml_INCLUDE_DIRS})

#list(APPEND gos_pid_toolkit_ui_view_model_cpp_library_libraries
#  Qt5::QuickControls2
#  Qt5::SerialPort
#  Qt5::Quick  
#  Qt5::Core
#  Qt5::Gui
#  Qt5::Qml)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF)

add_library(${gos_pid_toolkit_ui_view_model_cpp_library_target}
  ${gos_pid_toolkit_ui_view_model_cpp_library_source})

list(APPEND gos_pid_toolkit_ui_view_model_cpp_library_include
  ${Boost_INCLUDE_DIRS})

if(CLANG_TIDY_EXE)
  set_target_properties(${gos_pid_toolkit_ui_view_model_cpp_library_target}
    PROPERTIES
    CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")
endif()

target_include_directories(${gos_pid_toolkit_ui_view_model_cpp_library_target}
  PUBLIC ${gos_pid_toolkit_ui_view_model_cpp_library_include})

#target_compile_definitions(${gos_pid_toolkit_ui_view_model_cpp_library_target} PRIVATE
#  ${gos_pid_toolkit_ui_view_model_cpp_library_definitions})

#target_link_libraries(${gos_pid_toolkit_ui_view_model_cpp_library_target} PRIVATE
#  ${gos_pid_toolkit_ui_view_model_cpp_library_libraries})

if (gos_pid_toolkit_ui_view_model_cpp_library_public_header)
  set_target_properties(${gos_pid_toolkit_ui_view_model_cpp_library_target}
    PROPERTIES PUBLIC_HEADER
    "${gos_pid_toolkit_ui_view_model_cpp_library_public_header}")
endif ()

install(TARGETS ${gos_pid_toolkit_ui_view_model_cpp_library_target}
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/cpp/gos/pid/toolkit/ui/configuration
  ARCHIVE DESTINATION lib)
