QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CountAlgorithm.cpp \
    CountBase.cpp \
    CountBaseManage.cpp \
    main.cpp \
    mainwindow.cpp \
    materialmanagedialog.cpp \
    uiFace.cpp

HEADERS += \
    CountAlgorithm.h \
    CountBase.h \
    CountBaseManage.h \
    mainwindow.h \
    materialmanagedialog.h \
    uiFace.h

FORMS += \
    mainwindow.ui \
    materialmanagedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += $$PWD/include/halcon19_64

LIBS += -L$$PWD/'../../Program Files/MVTec/HALCON-19.11-Progress/lib/x64-win64/'
LIBS += -lhalcon \
        -lhalconcpp \
        -lhdevenginecpp

INCLUDEPATH += $$PWD/'../../Program Files/MVTec/HALCON-19.11-Progress/include'
DEPENDPATH += $$PWD/'../../Program Files/MVTec/HALCON-19.11-Progress/include'
