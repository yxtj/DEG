cmake_minimum_required(VERSION 2.8)

# c++11
macro(use_cxx11)
if (CMAKE_VERSION VERSION_LESS "3.1")
  if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
  endif ()
else ()
  set (CMAKE_CXX_STANDARD 11)
endif ()
endmacro(use_cxx11)

project(GraphMaker)
enable_language(CXX)
use_cxx11()

set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS filesystem system program_options REQUIRED)

message("${Boost_INCLUDE_DIR} ${Boost_LIBRARY_DIRS}")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(
    ${PROJECT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDE_DIR}
    )

link_directories (${Boost_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CXX_WARN} ${CXX_DEFINE} ${CMAKE_CXX_FLAGS}")

add_subdirectory (libcommon)
add_subdirectory (libutil)
add_subdirectory (libteg)
add_subdirectory (libio)
add_subdirectory (GraphFormater)
add_subdirectory (TGMaker)
add_subdirectory (Tools)
add_subdirectory (Test)


