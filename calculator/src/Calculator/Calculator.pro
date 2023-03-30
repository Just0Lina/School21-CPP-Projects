QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CalculatorController.cpp \
    CalculatorModel.cpp \
    CalculatorView.cpp \
    CreditModel.cpp \
    CreditView.cpp \
    main.cpp \
    qcustomplot.cpp \

HEADERS += \
    CalculatorController.h \
    CalculatorModel.h \
    CalculatorView.h \
    CreditModel.h \
    CreditView.h \
    StyleHelper.h \
    qcustomplot.h \

FORMS += \
    CalculatorView.ui \
    CreditView.ui \
    CreditView.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    icon.png

ICON += icon.png


