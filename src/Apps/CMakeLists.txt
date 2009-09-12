
if(QT4_FOUND)
    add_subdirectory(pann_viewer)
else(QT4_FOUND)
    message(STATUS "Could not find QT. Not building pann_viewer. ")
endif(QT4_FOUND)

if(OPTION_BUILD_TESTS_DEFINED)
    add_subdirectory(gnuplot-cpp-demo)
    add_subdirectory(UnitTests)
endif()

add_subdirectory(article1)
add_subdirectory(article3)

