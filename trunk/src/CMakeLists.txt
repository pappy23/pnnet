cmake_minimum_required(VERSION 2.6)

project(pann)

#http://www.cmake.org/Wiki/CMake:Component_Install_With_CPack
#TODO: install
#include(CPack)

set(CMAKE_VERBOSE_MAKEFILE OFF)

############################################################################
# OPTIONS

option(ENABLE_MOO "Enables easter egg compilation" OFF)
option(BUILD_PYTHON_BINDINGS "Compile Python bindings" OFF)
option(BUILD_TESTS "Build rarely needed Unit-tests and other staff" OFF)
option(BUILD_PANN_VIEWER "Build 3D topology viewer" OFF)
option(BUILD_ARTICLE1_APPS "Build basic apps (learning and performance measurement)" OFF)
option(BUILD_ARTICLE3_APPS "Build convolutional network app" ON)

if(ENABLE_MOO)
    add_definitions(-DOPTION_ENABLE_MOO_DEFINED)
endif()

if(BUILD_PYTHON_BINDINGS)
    add_definitions(-DOPTION_BUILD_PYTHON_BINDINGS_DEFINED)
endif()

if(BUILD_PANN_VIEWER)
    set(QT_USE_QTOPENGL 1)
    find_package(Qt4)
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
    add_definitions(-DUNIX -fPIC)
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
endif(WIN32)

#if(WIN32)
#	set(QT_QMAKE_EXECUTABLE	"C:/Qt/4.4.3/qmake/qmake.exe")
#endif(WIN32)

############################################################################
# DEPENDENCIES

#set(BOOST_MODULES thread serialization python)
set(BOOST_MODULES thread serialization)
if(WIN32)
    set(BOOST_MODULES ${BOOST_MODULES} date_time)
endif(WIN32)

#set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost 1.35 REQUIRED COMPONENTS ${BOOST_MODULES})

#if(UNIX)
#    set(Boost_LIBRARIES ${Boost_LIBRARIES} pthread)
#endif(UNIX)


#if(OPTION_BUILD_PYTHON_BINDINGS_DEFINED)
#find_package(PythonLibs REQUIRED)
#endif(OPTION_BUILD_PYTHON_BINDINGS_DEFINED)

############################################################################
# pann

#include_directories(pann pann-shit gnuplot-cpp ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_PATH})
include_directories(pann pann-shit gnuplot-cpp ${Boost_INCLUDE_DIRS})
subdirs(pann pann-shit gnuplot-cpp Apps)

