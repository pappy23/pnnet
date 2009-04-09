
add_executable(TestBoost TestBoost.cpp)
target_link_libraries(TestBoost ${Boost_LIBRARIES})

add_executable(TestIntSize TestIntSize.cpp)

add_executable(TestNet TestNet.cpp)
target_link_libraries(TestNet pann)

add_executable(TestLms TestLms.cpp)
target_link_libraries(TestLms pann gnuplot-cpp)

find_package(JPEG)
if(JPEG_FOUND)
    add_executable(TestImg TestImg.cpp)
    target_link_libraries(TestImg pann gnuplot-cpp ${JPEG_LIBRARIES})
else(JPEG_FOUND)
    message(STATUS "Could not find JPEG library. Not building TestImg")
endif(JPEG_FOUND)

