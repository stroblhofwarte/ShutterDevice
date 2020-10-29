cmake_minimum_required(VERSION 2.4.7)
PROJECT(indi_arduinofw CXX C)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake_modules/")

include(GNUInstallDirs)

set (GENERIC_VERSION_MAJOR 0)
set (GENERIC_VERSION_MINOR 1)

find_package(Threads REQUIRED)
find_package(CFITSIO REQUIRED)
find_package(INDI REQUIRED)
find_package(ZLIB REQUIRED)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h )
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/indi_arduinofw.xml.cmake ${CMAKE_CURRENT_BINARY_DIR}/indi_arduinofw.xml )

include_directories( ${CMAKE_CURRENT_BINARY_DIR})
include_directories( ${CMAKE_CURRENT_SOURCE_DIR})
include_directories( ${INDI_INCLUDE_DIR})
include_directories( ${CFITSIO_INCLUDE_DIR})

include(CMakeCommon)

############# INDI arduinofw ###############
set(indiarduinofw_SRCS
	${CMAKE_CURRENT_SOURCE_DIR}/indi_arduinofw.cpp
)

add_executable(indi_arduinofw ${indiarduinofw_SRCS})

target_link_libraries(indi_arduinofw ${INDI_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${CFITSIO_LIBRARIES} m ${ZLIB_LIBRARY})

install(TARGETS indi_arduinofw RUNTIME DESTINATION bin)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/indi_arduinofw.xml DESTINATION ${INDI_DATA_DIR})
