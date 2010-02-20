
add_executable(TestIntSize TestIntSize.cpp)

add_executable(TestNet TestNet.cpp)
target_link_libraries(TestNet pann ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

add_library(TestBoost SHARED TestBoost.cpp)
target_link_libraries(TestBoost ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

