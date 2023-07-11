QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    src/Control/CustomEditPasswd.cpp \
    src/Control/FlatUI.cpp \
    src/Util/AppCommon.cpp \
    src/Util/AppConfig.cpp \
    src/Util/AppData.cpp \
    src/Util/AppEvent.cpp \
    src/Util/AppInit.cpp \
    src/Widget/LoadingWidget.cpp \
    src/Wifi/WifiList.cpp \
    src/Wifi/WifiListItem.cpp \
    src/Wifi/XmlHelper.cpp


HEADERS += \
    src/Control/CustomEditPasswd.h \
    src/Control/FlatUI.h \
    src/Util/AppCommon.h \
    src/Util/AppConfig.h \
    src/Util/AppData.h \
    src/Util/AppEvent.h \
    src/Util/AppInit.h \
    src/Util/def.h \
    src/Widget/LoadingWidget.h \
    src/Wifi/WifiList.h \
    src/Wifi/WifiListItem.h \
    src/Wifi/XmlHelper.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/Resource.qrc
