
if(BUILD_TESTS)
    add_subdirectory(gnuplot-cpp-demo)
    add_subdirectory(UnitTests)
endif()

if(BUILD_PANN_VIEWER)
    add_subdirectory(pann_viewer)
endif()

if(BUILD_ARTICLE1_APPS)
    add_subdirectory(article1)
endif()

if(BUILD_ARTICLE3_APPS)
    add_subdirectory(article3)
endif()

if(BUILD_C3NN)
    add_subdirectory(c3nn)
endif()

if(BUILD_HYBRID)
    add_subdirectory(hybrid)
endif()

