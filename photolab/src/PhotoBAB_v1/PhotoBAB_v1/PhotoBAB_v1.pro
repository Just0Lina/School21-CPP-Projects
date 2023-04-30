 QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/model.cpp \
    View/customsettings.cpp \
    main.cpp \
    View/mainwindow.cpp

HEADERS += \
    Controller/controller.h \
    Model/model.h \
    View/mainwindow.h \
    View/customsettings.h

FORMS += \
    View/mainwindow.ui \
    View/customsettings.ui

ICON = ../img/icon.icns

LIBS +=   -framework AppKit

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    ../img/resurses.qrc


