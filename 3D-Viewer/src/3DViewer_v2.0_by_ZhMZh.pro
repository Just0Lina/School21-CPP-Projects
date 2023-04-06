QT       += core gui
include(../QtGifImage-master/src/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4):

CONFIG += c++17
QT += widgets opengl openglwidgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += GL_SILENCE_DEPRECATION

SOURCES += \
    controller/controller.cpp \
    main.cpp \
    model/geometry.cpp \
    model/model.cpp \
    view/mainwindow.cpp \
    widget.cpp

HEADERS += \
    controller/controller.h \
    model/geometry.h \
    model/model.h \
    view/mainwindow.h \
    widget.h

TRANSLATIONS += \
    3DViewer_v2.0_by_ZhMZh_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DISTFILES += \
#    ../img/wolf_bg.jpeg

RESOURCES += \
    QT/QT_3D/shaders.qrc \

FORMS += \
    view/mainwindow.ui

ICON = QT/QT_3D/freedom.icns

DISTFILES += \
    QT/QT_3D/freedom.icns \
    QT/QT_3D/fshader.glsl \
    QT/QT_3D/vshader.glsl
