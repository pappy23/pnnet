cmake_minimum_required(VERSION 2.6)

project(pann)

#http://www.cmake.org/Wiki/CMake:Component_Install_With_CPack
#TODO: install
include(CPack)

set(CMAKE_VERBOSE_MAKEFILE OFF)

############################################################################
# OPTIONS

option(BUILD_TESTS "Build or not rarely needed Unit-tests and other staff" OFF)

if(NOT ${BUILD_TEST})
    message(STATUS "NOT building optional tests. You may redefine this behavour via BUILD_TESTS variable")
endif()

############################################################################
# COMPILERS STAFF

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)
elseif(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-Wall -ansi)
#-fprofile-arcs -ftest-coverage
endif(MSVC)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-g -DDEBUG)
endif()

if(UNIX)
    add_definitions(-DUNIX)
elseif(WIN32)
    add_definitions(-DWIN32)
endif(UNIX)

#set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/../bin" CACHE INTERNAL "")
#set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/../bin" CACHE INTERNAL "")

############################################################################
# UGLY HACKS

if(WIN32)
	set(Boost_DEBUG TRUE)
	set(BOOST_ROOT "C:/Program Files/boost/boost_1_38") 
	#set(BOOST_INCLUDEDIR "C:/Program Files/boost/boost_1_38")
#elseif(UNIX)
#    set(BOOST_INCLUDEDIR /usr/local/include/boost-1_38)
#    #set(BOOST_LIBRARYDIR /usr/local/lib)
endif(WIN32)

#if(WIN32)
#	set(QT_QMAKE_EXECUTABLE	"C:/Qt/4.4.3/qmake/qmake.exe")
#endif(WIN32)

############################################################################
# DEPENDENCIES

find_package(MPI)

set(BOOST_MODULES thread serialization)
if(MPI_FOUND)
    set(BOOST_MODULES ${BOOST_MODULES} mpi)
endif(MPI_FOUND)
if(WIN32)
    set(BOOST_MODULES ${BOOST_MODULES} date_time)
endif(WIN32)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.35 REQUIRED COMPONENTS ${BOOST_MODULES})

if(UNIX)
    set(Boost_LIBRARIES ${Boost_LIBRARIES} pthread)
endif(UNIX)

set(QT_USE_QTOPENGL 1)
find_package(Qt4)
#find_package(JPEG REQUIRED)

############################################################################
# pann

include_directories(pann gnuplot-cpp ${Boost_INCLUDE_DIRS})
subdirs(Apps gnuplot-cpp pann)

