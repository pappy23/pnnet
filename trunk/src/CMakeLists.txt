cmake_minimum_required(VERSION 2.6)

project (PANN)

if(CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-Wall -ansi -g)
#-fprofile-arcs -ftest-coverage
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ansi")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(CMAKE_VERBOSE_MAKEFILE OFF)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/../bin" CACHE INTERNAL "")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/../bin" CACHE INTERNAL "")

############################################################################

if(WIN32)
	set(BOOST_INCLUDEDIR "C:/Program Files/boost/boost_1_38")
	set(BOOST_ROOT "C:/Program Files/boost/boost_1_38") 
elseif(UNIX)
	set(BOOST_INCLUDEDIR /usr/local/include/boost-1_38)
    #set(BOOST_LIBRARYDIR /usr/local/lib)
endif(WIN32)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS thread serialization date_time) #mpi

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    message(STATUS "Found Boost: ${Boost_INCLUDE_DIR}")
    message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
else(Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost package!")
endif(Boost_FOUND)

if(UNIX)
    set(Boost_LIBRARIES ${Boost_LIBRARIES} pthread)
endif(UNIX)

#########################################################################

find_package(MPI)
if(MPI_FOUND)
    include_directories(${MPI_INCLUDE_PATH})
    message(STATUS "Found MPI: ${MPI_INCLUDE_PATH}")
else(MPI_FOUND)
    message(STATUS "Could not find MPI")
endif(MPI_FOUND)

#########################################################################

find_package(JPEG REQUIRED)

#########################################################################

if(WIN32)
	set(QT_QMAKE_EXECUTABLE	"C:/Qt/4.4.2/qt/bin/qmake.exe")
endif(WIN32)

set(QT_USE_QTOPENGL 1)
find_package(Qt4)

#########################################################################

include_directories(pann gnuplot-cpp)
subdirs(Apps gnuplot-cpp pann)

