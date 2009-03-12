cmake_minimum_required(VERSION 2.6)

project (PANN)

set(EXECUTABLE_OUTPUT_PATH "./bin" CACHE INTERNAL "")
set(LIBRARY_OUTPUT_PATH "./bin" CACHE INTERNAL "")

############################################################################

#SET(BOOST_INCLUDEDIR /usr/local/include/boost-1_38)
#SET(BOOST_LIBRARYDIR /usr/local/lib)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS mpi thread)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    message(STATUS "Found Boost: ${Boost_INCLUDE_DIR}")
else(Boost_FOUND)
    message(FATAL_ERROR "Could not find Boost package!")
endif(Boost_FOUND)

#FIND_PACKAGE (MPI)
#IF(MPI_FOUND)
#        INCLUDE_DIRECTORIES ( ${MPI_INCLUDE_PATH} )
#    MESSAGE (STATUS "Found MPI: ${MPI_INCLUDE_PATH}")
#ELSE(MPI_FOUND)
#    MESSAGE(FATAL_ERROR "Could not find MPI!")
#ENDIF(MPI_FOUND)

############################################################################

set(PANN_SOURCES Core/*cpp NetworkModels/*cpp LearningAlgorithms/*cpp)
add_library(pann STATIC ${PANN_SOURCES})

add_subdirectory(UnitTests)

