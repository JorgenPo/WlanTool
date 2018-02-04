cmake_minimum_required(VERSION 3.0)

project(WlanTool)

set(WLANTOOL_VERSION_MAJOR 0)
set(WLANTOOL_VERSION_MINOR 1)

set(WLANTOOL_SOURCE_DIR "src")
set(WLANTOOL_LIB_DIR "src/lib")
set(WLANTOOL_CONF_DIR "src/conf")

file(GLOB WLANTOOL_SOURCES 
	"${WLANTOOL_SOURCE_DIR}/*.h"
	"${WLANTOOL_SOURCE_DIR}/*.cpp"
)

file(GLOB WLANTOOL_LIBS
	"${WLANTOOL_LIB_DIR}/*.h"
	"${WLANTOOL_LIB_DIR}/*.hpp"
	"${WLANTOOL_LIB_DIR}/*.cpp"
)

configure_file(
	"${CMAKE_SOURCE_DIR}/${WLANTOOL_CONF_DIR}/Config.h.in"
	"${CMAKE_SOURCE_DIR}/${WLANTOOL_CONF_DIR}/Config.h"
)

include_directories("${WLANTOOL_SOURCES} ${WLANTOOL_CONF_DIR}")

add_executable(WlanTool ${WLANTOOL_SOURCES} ${WLANTOOL_LIBS}) 

install(TARGETS WlanTool DESTINATION bin)