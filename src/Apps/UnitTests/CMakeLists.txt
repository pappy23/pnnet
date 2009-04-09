
add_executable(TestBoost TestBoost.cpp)
target_link_libraries(TestBoost ${Boost_LIBRARIES})

add_executable(TestIntSize TestIntSize.cpp)

add_executable(TestNet TestNet.cpp)
target_link_libraries(TestNet pann)

add_executable(TestLms TestLms.cpp)
target_link_libraries(TestLms pann gnuplot-cpp)

