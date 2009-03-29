
set(PLOTTER_SOURCES example.cc gnuplot-cpp/gnuplot_i.cc)
include_directories(gnuplot-cpp)

add_executable(plotter ${PLOTTER_SOURCES})
target_link_libraries(plotter pann)
