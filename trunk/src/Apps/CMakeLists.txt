
add_executable(TestBoost TestBoost.cpp)
target_link_libraries(TestBoost ${Boost_LIBRARIES})

add_executable(TestIntSize TestIntSize.cpp)

add_executable(TestNet TestNet.cpp)
target_link_libraries(TestNet pann)

add_executable(TestLms TestLms.cpp)
target_link_libraries(TestLms pann)

add_executable(Article1_learning Article1_learning.cpp)
target_link_libraries(Article1_learning pann)

add_executable(Article1_performance Article1_performance.cpp)
target_link_libraries(Article1_performance pann)

