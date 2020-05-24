find_package(Doxygen REQUIRED dot dia OPTIONAL_COMPONENTS mscgen)

if (DOXYGEN_FOUND)
  set(DOXYGEN_OUTPUT_DIRECTORY        ${gos_pid_toolkit_doxygen_output_directory}) 
  set(DOXYGEN_GENERATE_LATEX          NO)
  set(DOXYGEN_EXTRACT_PRIVATE         YES)
  set(DOXYGEN_EXTRACT_PACKAGE         YES)
  set(DOXYGEN_EXTRACT_STATIC          YES)
  set(DOXYGEN_WARN_NO_PARAMDOC        YES)
  set(DOXYGEN_HTML_OUTPUT             ${CMAKE_BINARY_DIR}/docs)
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE  README.md)
  set(DOXYGEN_FILE_PATTERNS           *.c *.cpp *.h README.md)

  doxygen_add_docs(${gos_pid_toolkit_doxygen_main_target}
    ${gos_pid_toolkit_doxygen_source}
    WORKING_DIRECTORY ${gos_pid_toolkit_doxygen_working_directory})

else ()
  message(WARNING "Doxygen not found but requested")
endif ()
install(DIRECTORY ${gos_pid_toolkit_doxygen_output_directory}
  DESTINATION share/doc/api)
