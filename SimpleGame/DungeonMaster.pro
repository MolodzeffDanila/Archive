#-------------------------------------------------
#
# Project created by QtCreator 2020-09-13T17:18:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DungeonMaster
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        Sourses/main.cpp \
        Sourses/mainwindow.cpp \
    Sourses/field.cpp \
    Sourses/cell.cpp \
    Sourses/types_of_cells.cpp \
    Sourses/hero.cpp \
    Sourses/start.cpp \
    Sourses/finish.cpp \
    Sourses/flatland.cpp \
    Sourses/mountain.cpp \
    Sourses/dungeon.cpp \
    Sourses/fortress.cpp \
    Sourses/observer.cpp \
    Sourses/subject.cpp \
    Sourses/dialog_window.cpp \
    Sourses/asklog.cpp \
    Sourses/facade.cpp \
    Sourses/wall.cpp \
    Sourses/lstart.cpp \
    Sourses/lfinish.cpp \
    Sourses/ground.cpp \
    Sourses/mementomori.cpp \
    Sourses/savewindow.cpp

HEADERS += \
        Headers/mainwindow.h \
    Headers/field.h \
    Headers/cell.h \
    Headers/types_of_cells.h \
    Headers/using_libs.h \
    Headers/hero.h \
    Headers/start.h \
    Headers/finish.h \
    Headers/flatland.h \
    Headers/mountain.h \
    Headers/abstrfactory.h \
    Headers/dungeon.h \
    Headers/fortress.h \
    Headers/observer.h \
    Headers/subject.h \
    Headers/dialog_window.h \
    Headers/asklog.h \
    Headers/facade.h \
    Headers/command.h \
    Headers/wall.h \
    Headers/lstart.h \
    Headers/lfinish.h \
    Headers/ground.h \
    Headers/mementomori.h \
    Headers/savewindow.h \
    Headers/fileexeption.h
FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourse.qrc

STATECHARTS +=

DISTFILES += \
    lab.qmodel \
    lab3.qmodel \
    Sourses/lab4.qmodel \
    lab4.qmodel
