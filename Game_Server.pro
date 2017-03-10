#-------------------------------------------------
#
# Project created by QtCreator 2017-03-01T11:08:40
#
#-------------------------------------------------

QT += core
greaterThan(QT_MAJOR_VERSION, 4) QT += widgets
QT -= gui
QT += network
CONFIG += c++11

TARGET = Game_Server
CONFIG -= app_bundle

TEMPLATE = app
SOURCES += main.cpp\
        servermainwindow.cpp \
    tcpserver.cpp \
    stringconstant.cpp \
    Connector/serverconnector.cpp

HEADERS  += servermainwindow.h \
    tcpserver.h \
    stringconstant.h \
    Connector/serverconnector.h

FORMS    += servermainwindow.ui
