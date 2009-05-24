
if(MPI_FOUND)
    add_executable(TestBoostMPI TestBoostMPI.cpp)
    target_link_libraries(TestBoostMPI ${Boost_LIBRARIES})
else(MPI_FOUND)
    message(STATUS "Not building TestBoostMPI")
endif(MPI_FOUND)

add_executable(TestIntSize TestIntSize.cpp)

add_executable(TestNet TestNet.cpp)
target_link_libraries(TestNet pann)

add_executable(TestLms TestLms.cpp)
target_link_libraries(TestLms pann gnuplot-cpp)

add_executable(TestImg TestImg.cpp)
target_link_libraries(TestImg pann gnuplot-cpp)

add_executable(TestConvolutionalNetwork TestConvolutionalNetwork.cpp)
target_link_libraries(TestConvolutionalNetwork pann gnuplot-cpp)

