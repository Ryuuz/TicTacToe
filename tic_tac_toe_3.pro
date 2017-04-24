#-------------------------------------------------
#
# Project created by QtCreator 2016-08-31T18:28:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tic_tac_toe_3
TEMPLATE = app

RC_FILE = gameIcon.rc

SOURCES += main.cpp \
    ai.cpp \
    game.cpp \
    button.cpp \
    board.cpp

HEADERS  += \
    define.h \
    ai.h \
    game.h \
    button.h \
    board.h

FORMS    +=

RESOURCES += \
    resources.qrc
