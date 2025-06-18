QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    difficultywindow.cpp \
    gamewindow.cpp \
    historywindow.cpp \
    homewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    playmodewindow.cpp \
    registerwindow.cpp \
    security.cpp \
    usermanager.cpp

HEADERS += \
    difficultywindow.h \
    gamewindow.h \
    historywindow.h \
    homewindow.h \
    mainwindow.h \
    playmodewindow.h \
    registerwindow.h \
    security.h \
    usermanager.h

FORMS += \
    difficultywindow.ui \
    gamewindow.ui \
    historywindow.ui \
    homewindow.ui \
    mainwindow.ui \
    playmodewindow.ui \
    registerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    users.json
