QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TableConverter
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += src/main.cpp\
        src/MainWindow.cpp \
    src/SqliteLoader.cpp \
    src/TableModel.cpp \
    src/CsvLoader.cpp

INCLUDEPATH += include

HEADERS  += include/MainWindow.h \
    include/SqliteLoader.h \
    include/TableModel.h \
    include/CsvLoader.h

FORMS    += MainWindow.ui
