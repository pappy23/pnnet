cmake_minimum_required(VERSION 2.6)

project (PANN)

#set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" CACHE INTERNAL "")
#set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin" CACHE INTERNAL "")

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

set(PANN_SOURCES Core NetworkTopologies LearningAlgorithms)
include_directories(${PANN_SOURCES})
#link_directories("${CMAKE_BINARY_DIR}/bin")

message(STATUS "Adding files to build library")
foreach(dir ${PANN_SOURCES})
    file(GLOB files RELATIVE ""  "${dir}/*.cpp")
    foreach(filename ${files})
        set(PANN_SOURCE_FILES ${PANN_SOURCE_FILES} "${filename}")
        message(STATUS ">> ${filename}")
    endforeach(filename)
endforeach(dir)

add_library(pann STATIC ${PANN_SOURCE_FILES})

###########################################################################

set(UNIT_TESTS TestBoost TestOMP TestIntSize TestNet TestSerialization)

foreach(test ${UNIT_TESTS})
    add_executable(${test} UnitTests/${test}.cpp)
    target_link_libraries(${test} pann ${Boost_LIBRARIES})
endforeach(test)

