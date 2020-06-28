find_package(Doxygen REQUIRED dot dia OPTIONAL_COMPONENTS mscgen)

#set(gos_pid_toolkit_doxygen_docs_directory
#  "${CMAKE_BINARY_DIR}/docs")

if (DOXYGEN_FOUND)
# set(DOXYGEN_OUTPUT_DIRECTORY        ${gos_pid_toolkit_doxygen_output_directory})
  set(DOXYGEN_GENERATE_TREEVIEW       YES)
  set(DOXYGEN_UML_LOOK                YES)
  set(DOXYGEN_DOT_IMAGE_FORMAT        svg)
  set(DOXYGEN_INTERACTIVE_SVG         YES)
  set(DOXYGEN_DOT_TRANSPARENT         YES)
  set(DOXYGEN_HIDE_UNDOC_RELATIONS    NO)
# set(DOXYGEN_GENERATE_LATEX          NO)
  set(DOXYGEN_GENERATE_HTML           YES)
# set(DOXYGEN_GENERATE_MAN            NO)
# set(DOXYGEN_EXTRACT_PRIVATE         NO)
# set(DOXYGEN_EXTRACT_PACKAGE         NO)
# set(DOXYGEN_EXTRACT_STATIC          NO)
# set(DOXYGEN_WARN_NO_PARAMDOC        YES)
  set(DOXYGEN_HTML_OUTPUT             html)
# set(DOXYGEN_LATEX_OUTPUT            "${gos_pid_toolkit_doxygen_docs_directory}/latex")
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE  ${gos_pid_toolkit_doxygen_main_page_mdfile})
# set(DOXYGEN_USE_PDFLATEX            NO)
# set(DOXYGEN_PDF_HYPERLINKS          NO)
  set(DOXYGEN_EXTENSION_MAPPING       qml=C++)
  SET(DOXYGEN_FILTER_PATTERNS         *.qml=doxyqml)
  set(DOXYGEN_FILE_PATTERNS           *.c *.cpp *.h README.md *.qml)
  set(DOXYGEN_EXCLUDE_PATTERNS        */empty/*.qml)

  doxygen_add_docs(${gos_pid_toolkit_doxygen_main_target}
    ${gos_pid_toolkit_doxygen_source}
    WORKING_DIRECTORY ${gos_pid_toolkit_doxygen_working_directory})

  set(gos_pid_toolkit_doxygen_html_directory "${CMAKE_BINARY_DIR}/doc/${DOXYGEN_HTML_OUTPUT}")

  message(STATUS "")
  message(STATUS "PID Toolkit Documents BUILD SUMMARY")
  message(STATUS "  Doxygen output directory : ${DOXYGEN_OUTPUT_DIRECTORY}")
  message(STATUS "  Doxygen html directory   : ${gos_pid_toolkit_doxygen_html_directory}")


  install(DIRECTORY ${gos_pid_toolkit_doxygen_html_directory}
    DESTINATION share/doc/api)


else ()
  message(WARNING "Doxygen not found but requested")
endif ()
