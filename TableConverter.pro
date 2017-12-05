QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TableConverter
TEMPLATE = app

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES  += src/main.cpp \
            src/MainWindow.cpp \
            src/TableSelectionDialog.cpp \
            src/TableModel.cpp \
            src/SqliteWriter.cpp \
            src/SqliteReader.cpp \
            src/CsvReader.cpp \
            src/CsvWriter.cpp

INCLUDEPATH += include

HEADERS  += include/MainWindow.h \
            include/TableSelectionDialog.h \
            include/TableModel.h \
            include/SqliteWriter.h \
            include/SqliteReader.h \
            include/CsvReader.h \
            include/CsvWriter.h

FORMS    += MainWindow.ui \
            TableSelectionDialog.ui
