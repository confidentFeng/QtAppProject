QT       += core gui

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
    CustomControl.cpp \
    src/Control/CustomBtnBorder.cpp \
    src/Control/CustomBtnCombox.cpp \
    src/Control/CustomBtnIcon.cpp \
    src/Control/CustomBtnSplit.cpp \
    src/Control/CustomBtnSw.cpp \
    src/Control/CustomEditIcon.cpp \
    src/Control/CustomEditPasswd.cpp \
    src/Control/CustomLabLoad.cpp \
    src/Control/CustomLabScroll.cpp \
    src/Control/CustomSliderNum.cpp \
    src/Control/CustomTooltip.cpp \
    src/Control/FlatUI.cpp \
    src/Control/CustomLabTip.cpp \
    src/Widget/CustomBtnWidget.cpp \
    src/Widget/CustomCheckWidget.cpp \
    src/Widget/CustomEidtWidget.cpp \
    src/Widget/CustomLabWidget.cpp \
    src/Widget/CustomSliderWidget.cpp

HEADERS += \
    CustomControl.h \
    src/Control/CustomBtnBorder.h \
    src/Control/CustomBtnCombox.h \
    src/Control/CustomBtnIcon.h \
    src/Control/CustomBtnSplit.h \
    src/Control/CustomBtnSw.h \
    src/Control/CustomEditIcon.h \
    src/Control/CustomEditPasswd.h \
    src/Control/CustomLabLoad.h \
    src/Control/CustomLabScroll.h \
    src/Control/CustomSliderNum.h \
    src/Control/CustomTooltip.h \
    src/Control/FlatUI.h \
    src/Control/CustomLabTip.h \
    src/Util/def.h \
    src/Widget/CustomBtnWidget.h \
    src/Widget/CustomCheckWidget.h \
    src/Widget/CustomEidtWidget.h \
    src/Widget/CustomLabWidget.h \
    src/Widget/CustomSliderWidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/Resource.qrc
