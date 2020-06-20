include(ExternalProject)

set(MODBUS_TARGET libmodbus)
set(MODBU_EXTERNAL_PROJECT libmodbusexternal)
set(MODBUS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extern/libmodbus)
set(MODBUS_BIN ${CMAKE_CURRENT_BINARY_DIR}/libmodbus)
set(MODBUS_STATIC_LIB ${MODBUS_BIN}/lib/libmodbus.a)
set(MODBUS_INCLUDES ${MODBUS_BIN}/include)

file(MAKE_DIRECTORY ${MODBUS_INCLUDES})

ExternalProject_Add(
    ${MODBU_EXTERNAL_PROJECT}
    PREFIX ${MODBUS_BIN}
    SOURCE_DIR ${MODBUS_DIR}
    DOWNLOAD_COMMAND cd ${MODBUS_DIR} && git clean -dfX && ${MODBUS_DIR}/autogen.sh
    CONFIGURE_COMMAND ${MODBUS_DIR}/configure --srcdir=${MODBUS_DIR} --prefix=${MODBUS_BIN} --enable-static=yes --disable-shared --without-documentation
    BUILD_COMMAND make
    INSTALL_COMMAND make install
    BUILD_BYPRODUCTS ${MODBUS_STATIC_LIB}
)

add_library(${MODBUS_TARGET} STATIC IMPORTED GLOBAL)

add_dependencies(${MODBUS_TARGET} ${MODBU_EXTERNAL_PROJECT})

set_target_properties(${MODBUS_TARGET} PROPERTIES IMPORTED_LOCATION ${MODBUS_STATIC_LIB})
set_target_properties(${MODBUS_TARGET} PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${MODBUS_INCLUDES})
