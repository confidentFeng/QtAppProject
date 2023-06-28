#-------------------------------------------------
#
# Project created by QtCreator 2019-12-21T15:16:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mpvDemo
TEMPLATE = app

QT_CONFIG -= no-pkg-config

INCLUDEPATH += $$PWD/lib/win32/mpv/include
LIBS += $$PWD/lib/win32/mpv/libmpv.dll.a

SOURCES += qtexample.cpp
HEADERS += qtexample.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
