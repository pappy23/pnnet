
add_executable(TestNet TestNet.cpp)
target_link_libraries(TestNet pann ${Boost_LIBRARIES})

add_executable(TestBoost TestBoost.cpp)
target_link_libraries(TestBoost ${Boost_LIBRARIES})

add_executable(TestOMP TestOMP.cpp)

