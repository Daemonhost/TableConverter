QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TableConverter
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += src/main.cpp\
        src/MainWindow.cpp

INCLUDEPATH += include

HEADERS  += include/MainWindow.h

FORMS    += MainWindow.ui
