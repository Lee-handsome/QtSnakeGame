#-------------------------------------------------
#
# Project created by QtCreator 2016-11-19T13:25:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtsnake2
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainmenu.cpp \
    aboutme.cpp \
    mainwindow.cpp \
    snake.cpp \
    twoplayer.cpp \
    ranklist.cpp \
    twosnake.cpp

HEADERS  += \
    mainmenu.h \
    aboutme.h \
    mainwindow.h \
    snake.h \
    twoplayer.h \
    ranklist.h \
    twosnake.h

FORMS    += mainmenu.ui \
    aboutme.ui \
    ranklist.ui

DISTFILES += \
    snake.rc

RESOURCES += \
    images.qrc

RC_FILE += \
    snake.rc
