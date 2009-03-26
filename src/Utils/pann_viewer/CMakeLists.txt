
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

if(WIN32)
	set(QT_QMAKE_EXECUTABLE	"C:/Qt/4.4.2/qt/bin/qmake.exe")
endif(WIN32)

set(QT_USE_QTOPENGL 1)
find_package(Qt4)

if(QT4_FOUND)
    message(STATUS "Found Qt4")

    include(${QT_USE_FILE})

    qt4_wrap_ui(UI_HEADERS ${UIS})
    qt4_wrap_cpp(MOC_SRCS ${MOC_HEADERS})

    add_executable(pann_viewer ${SOURCES} ${UI_HEADERS} ${MOC_SRCS})
    target_link_libraries(pann_viewer ${QT_LIBRARIES} pann)
elseif (QT4_FOUND)
    message(STATUS "23:18:30 Could not find QT. Not building pann_viewer. ")
endif(QT4_FOUND)

