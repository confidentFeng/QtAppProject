QT += core gui widgets

TARGET = qtnotify
TEMPLATE = app

include($$PWD/../src/qtnotify2.pri)

SOURCES += \
    Widget.cpp \
    main.cpp

RESOURCES += \
    res.qrc

HEADERS += \
    Widget.h



