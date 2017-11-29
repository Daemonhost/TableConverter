QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TableConverter
TEMPLATE = app

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += src/main.cpp\
        src/MainWindow.cpp \
    src/SqliteLoader.cpp \
    src/TableModel.cpp \
    src/CsvLoader.cpp \
    src/TableSelectionDialog.cpp

INCLUDEPATH += include

HEADERS  += include/MainWindow.h \
    include/SqliteLoader.h \
    include/TableModel.h \
    include/CsvLoader.h \
    include/TableSelectionDialog.h

FORMS    += MainWindow.ui \
    TableSelectionDialog.ui
