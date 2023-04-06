QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/cave.cpp \
    Controller/controller.cpp \
    main.cpp \
    View/mainwindow.cpp \
    Model/maze.cpp \
    View/widgetCave.cpp \
    View/widgetMaze.cpp

HEADERS += \
    Model/cave.h \
    Controller/controller.h \
    View/mainwindow.h \
    Model/maze.h \
    View/widgetCave.h \
    View/widgetMaze.h

FORMS += \
    View/mainwindow.ui \
    View/widgetCave.ui \
    View/widgetMaze.ui

ICON = img/icon.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    View/resurses.qrc

DISTFILES += \
    img/wolf_pack.jpg \
    img/wolf_pack2.jpg
