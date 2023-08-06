QT += core gui xml widgets

CONFIG += c++17

HEADERS += \
    Meike_6.5mm_f2.0.dctl \
    dctl_parta.h \
    dctl_partb.h \
    dctl_plugin.h \
    dctl_struct.h \
    dctlq.h \
    defisheye.h \
    grwidget.h \
    mainwindow.h \
    wrapsettings.h

SOURCES += \
    dctl_plugin.cpp \
    dctlq.cpp \
    grwidget.cpp \
    laowa4.0f2.8.plugin.cpp \
    main.cpp \
    mainwindow.cpp \
    meike6.5f2.0.plugin.cpp \
    ptgui11.plugin.cpp \
    wrapsettings.cpp

FORMS += \
    grwidget.ui \
    mainwindow.ui
