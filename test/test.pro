#-------------------------------------------------
#
# Project created by QtCreator 2017-12-05T18:38:41
#
#-------------------------------------------------

# gui нужен для QColor и QFont
QT       += sql testlib gui

TARGET = TestSuite
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES  += ../src/TableModel.cpp \
            ../src/SqliteWriter.cpp \
            ../src/SqliteReader.cpp \
            ../src/CsvReader.cpp \
            ../src/CsvWriter.cpp

INCLUDEPATH += ../include

HEADERS  += ../include/TableModel.h \
            ../include/SqliteWriter.h \
            ../include/SqliteReader.h \
            ../include/CsvReader.h \
            ../include/CsvWriter.h

SOURCES += TestSuite.cpp \
    utility.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    utility.h
