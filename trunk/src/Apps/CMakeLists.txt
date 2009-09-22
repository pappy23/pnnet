
if(QT4_FOUND)
    add_subdirectory(pann_viewer)
else(QT4_FOUND)
    message(STATUS "Could not find QT. Not building pann_viewer. ")
endif(QT4_FOUND)

if(BUILD_TESTS)
    add_subdirectory(gnuplot-cpp-demo)
    add_subdirectory(UnitTests)
endif(BUILD_TESTS)

add_subdirectory(article1)
add_subdirectory(article3)

