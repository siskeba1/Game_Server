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
SOURCES +=\
    Controller/ServerController.cpp \
    View/ServerMainWindow.cpp \
    Const/StringConstant.cpp \
    Model/TcpServer/TcpServer.cpp \
    Model/ServerWorkingThread/ServerWorkingThread.cpp \
    View/ClientTableItem.cpp \
    Main/Main.cpp \
    Model/MessageProcessor/MessageProcessor.cpp

HEADERS  += \
    Model/TcpServer/TcpServer.h \
    Const/StringConstant.h \
    View/ServerMainWindow.h \
    Controller/ServerController.h \
    Model/ServerWorkingThread/ServerWorkingThread.h \
    View/ClientTableItem.h \
    Model/MessageProcessor/MessageProcessor.h

FORMS    += \
    GUI/ServerMainWindow.ui
