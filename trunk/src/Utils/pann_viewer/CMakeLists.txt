
set( SOURCES
    main.cpp
    glwidget.cpp
    window.cpp
    )


SET( UIS
#    ./ui/dialog.ui
    )

set( MOC_HEADERS
    window.h
    glwidget.h
    )

set( QT_USE_QTOPENGL 1 )
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )

qt4_wrap_ui( UI_HEADERS ${UIS})
qt4_wrap_cpp( MOC_SRCS ${MOC_HEADERS} )

add_executable( pann_viewer ${SOURCES} ${UI_HEADERS} ${MOC_SRCS} )
target_link_libraries( pann_viewer ${QT_LIBRARIES} )

