
add_executable(TestBoost TestBoost.cpp)
if (WIN32)
	target_link_libraries(TestBoost ${Boost_LIBRARIES})
else (WIN32)
	target_link_libraries(TestBoost ${Boost_LIBRARIES} pthread)
endif(WIN32)

add_executable(TestIntSize TestIntSize.cpp)

add_executable(TestNet TestNet.cpp)
target_link_libraries(TestNet pann)

