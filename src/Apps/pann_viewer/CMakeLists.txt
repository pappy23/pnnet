
set(SOURCES
    main.cpp
    glwidget.cpp
    window.cpp
    )


SET(UIS
#    ./ui/dialog.ui
    )

set(MOC_HEADERS
    window.h
    glwidget.h
    )

include(${QT_USE_FILE})

qt4_wrap_ui(UI_HEADERS ${UIS})
qt4_wrap_cpp(MOC_SRCS ${MOC_HEADERS})

add_executable(pann_viewer ${SOURCES} ${UI_HEADERS} ${MOC_SRCS})
#target_link_libraries(pann_viewer ${QT_LIBRARIES} ${GLUT_glut_LIBRARY} pann)
target_link_libraries(pann_viewer ${QT_LIBRARIES} pann)

