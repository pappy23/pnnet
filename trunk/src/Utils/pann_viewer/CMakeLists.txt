
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

set(QT_USE_QTOPENGL 1)
find_package(Qt4)


if (WIN32)
	set(QT_QMAKE_EXECUTABLE	"C:/Qt/2009.01/qt/bin/qmake.exe")
endif (WIN32)


if(QT4_FOUND)
    message(STATUS "Found Qt4")

    include(${QT_USE_FILE})

    qt4_wrap_ui(UI_HEADERS ${UIS})
    qt4_wrap_cpp(MOC_SRCS ${MOC_HEADERS})

    add_executable(pann_viewer ${SOURCES} ${UI_HEADERS} ${MOC_SRCS})
    target_link_libraries(pann_viewer ${QT_LIBRARIES} pann)

else(QT4_FOUND)
    message(FATAL_ERROR "Could not find QT4 package!")

endif(QT4_FOUND)

