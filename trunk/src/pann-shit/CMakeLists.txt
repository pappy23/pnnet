set(PANN_SOURCES ".")

message(STATUS "Adding files to build library")
foreach(dir ${PANN_SOURCES})
    file(GLOB_RECURSE files RELATIVE ""  "${dir}/*.cpp" "${dir}/*.cc" "${dir}/*.h" "${dir}/*.hpp")
    foreach(filename ${files})
        set(PANN_SOURCE_FILES ${PANN_SOURCE_FILES} "${filename}")
        #message(STATUS ">> ${filename}")
    endforeach(filename)
endforeach(dir)

add_library(pann-shit STATIC ${PANN_SOURCE_FILES})
target_link_libraries(pann-shit pann ${Boost_LIBRARIES})

