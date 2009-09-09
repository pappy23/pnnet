
if(Boost_mpi_FOUND)
    add_executable(TestBoostMPI TestBoostMPI.cpp)
    target_link_libraries(TestBoostMPI ${Boost_LIBRARIES})
else(Boost_mpi_FOUND)
    message(STATUS "Boost MPI not found. Not building TestBoostMPI")
endif(Boost_mpi_FOUND)

add_executable(TestIntSize TestIntSize.cpp)

add_executable(TestNet TestNet.cpp)
target_link_libraries(TestNet pann)

add_executable(TestLms TestLms.cpp)
target_link_libraries(TestLms pann gnuplot-cpp)

#add_executable(TestImg TestImg.cpp)
#target_link_libraries(TestImg pann gnuplot-cpp)

add_executable(TestImageIO TestImageIO.cpp)
target_link_libraries(TestImageIO pann)

add_library(TestBoost SHARED TestBoost.cpp)
target_link_libraries(TestBoost ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

