cmake_minimum_required(VERSION 2.6)

PROJECT (PANN)

#SET(BOOST_INCLUDEDIR /usr/local/include/boost-1_38)
#SET(BOOST_LIBRARYDIR /usr/local/lib)

SET(Boost_USE_STATIC_LIBS ON)
FIND_PACKAGE (Boost COMPONENTS mpi thread)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES ( ${Boost_INCLUDE_DIR} )
    MESSAGE (STATUS "Found Boost: ${Boost_INCLUDE_DIR}")
ELSE(Boost_FOUND)
    MESSAGE(FATAL_ERROR "Could not find Boost package!")
ENDIF(Boost_FOUND)

FIND_PACKAGE (MPI)
IF(MPI_FOUND)
    INCLUDE_DIRECTORIES ( ${MPI_INCLUDE_PATH} )
    MESSAGE (STATUS "Found MPI: ${MPI_INCLUDE_PATH}")
ELSE(MPI_FOUND)
    MESSAGE(FATAL_ERROR "Could not find MPI!")
ENDIF(MPI_FOUND)

############################################################################
ADD_LIBRARY (pann STATIC Object.cpp)

#ADD_EXECUTABLE (HelloWorld main.cpp)
#TARGET_LINK_LIBRARIES (HelloWorld pann ${MPI_LIBRARIES} ${Boost_LIBRARIES})

ADD_EXECUTABLE (ObjectTest ObjectTest.cpp)
TARGET_LINK_LIBRARIES (ObjectTest pann ${Boost_LIBRARIES})

