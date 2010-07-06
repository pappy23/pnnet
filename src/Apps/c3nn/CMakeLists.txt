
set(SOURCES
    main.cpp
    config.cpp
    )


set(MOC_HEADERS
    #    window.h
    #    glwidget.h
    )

include(${QT_USE_FILE})

qt4_wrap_ui(UI_HEADERS ${UIS})
qt4_wrap_cpp(MOC_SRCS ${MOC_HEADERS})

add_executable(c3nn ${SOURCES} ${UI_HEADERS} ${MOC_SRCS})
target_link_libraries(c3nn ${QT_LIBRARIES} pann-shit)

