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
    Graph.cpp \
    Client2.cpp \
    SuperVertex.cpp

HEADERS  += qttest.h \
    DijkstrasAlgorithm.h \
    Edge.h \
    Graph.h \
    Vertex.h \
    Coor.h \
    Define.h \
    input.h \
    SuperVertex.h

FORMS    += qttest.ui

LIBS  += -lws2_32
