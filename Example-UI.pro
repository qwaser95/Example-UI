
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Example-UI
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    tipires.cpp \
    calcparameters.cpp \
    addeditres.cpp \
    loadfromdirectory.cpp \
    auxiliaryfunctions.cpp \
    extern.cpp \
    map.cpp \
    msgdlgload.cpp \
    RbTableHeaderView.cpp \
    mymodel.cpp \
    dbsqlqueries.cpp \
    addtipres.cpp

HEADERS += \
        mainwindow.h \
    tipires.h \
    calcparameters.h \
    addeditres.h \
    loadfromdirectory.h \
    extern.h \
    map.h \
    msgdlgload.h \
    RbTableHeaderView.h \
    mymodel.h \
    auxiliaryfunctions.h \
    dbsqlqueries.h \
    addtipres.h

FORMS += \
    mainwindow.ui \
    tipires.ui \
    calcparameters.ui \
    addeditres.ui \
    loadfromdirectory.ui \
    map.ui \
    msgdlgload.ui \
    addtipres.ui

RESOURCES += \
    resource.qrc
