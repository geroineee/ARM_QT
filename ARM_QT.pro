QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    realization/tab_files.cpp \
    realization/tab_only_code.cpp \
    realization/workWithDB.cpp \
    testwindow.cpp \
    textwindow.cpp

HEADERS += \
    mainwindow.h \
    realization/workWithDB.h \
    testwindow.h \
    textwindow.h

FORMS += \
    mainwindow.ui \
    testwindow.ui \
    textwindow.ui

win32:RC_FILE = icon.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
