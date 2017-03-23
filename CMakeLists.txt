cmake_minimum_required(VERSION 3.0)
project(yanni)

set (CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories("${PROJECT_SOURCE_DIR}/common")
include_directories("${PROJECT_SOURCE_DIR}")

find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIRS} )

set(main_source yanni.cpp)

add_subdirectory(common)
add_subdirectory(fileio)
add_subdirectory(helper)
add_subdirectory(interpreter)
add_subdirectory(networks)

add_executable(yanni ${main_source})

target_link_libraries(yanni "${CURSES_LIBRARIES}" ncurses libcommon libparts libfileio libhelper libinterpreter libnetworks)
