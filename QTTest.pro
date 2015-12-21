#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T13:45:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTTest
TEMPLATE = app


SOURCES += main.cpp\
        qttest.cpp \
    DijkstrasAlgorithm.cpp \
    Graph.cpp

HEADERS  += qttest.h \
    DijkstrasAlgorithm.h \
    Edge.h \
    Graph.h \
    Vertex.h \
    Area.h

FORMS    += qttest.ui
