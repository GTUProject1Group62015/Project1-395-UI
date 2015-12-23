#ifndef QTTEST_H
#define QTTEST_H
#define MAXLINEPOSSIBILITY 50

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsPixmapItem>
#include "Vertex.h"
#include "Graph.h"




/* server define*/
//#include <netdb.h>
//#include <netinet/in.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
//#include <ws2spi.h>
#include <winsock2.h>
#include <windows.h>
#include "input.h"
#include <cstdio>

#define MAX_LINE 100
#define LINE_ARRAY_SIZE (MAX_LINE+1)





namespace Ui {
class QTTest;
}

class QTTest : public QMainWindow
{
    Q_OBJECT

public:
    void seekLocation(); // Get User Location from hardware
    void clearLines(); // Clear all drawed lines
    QGraphicsLineItem *drawLine(Vertex &c1, Vertex &c2, QPen pen); // Draw A line between 2 coordinates
    explicit QTTest(QWidget *parent = 0);
    void connectToServer();

    int socketDescriptor;
    ~QTTest();

private slots:
    void on_pushButton_clicked();
    void update2();

private:
    Ui::QTTest *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *destinationMarker;
    QGraphicsPolygonItem *locationMarker;
    QGraphicsEllipseItem *nodeLocationsMarker;
    QList<QGraphicsItem *> drawedLines;
    QGraphicsPixmapItem *planPixmap;
    Graph g;
    Vertex *locationVertex;
    Vertex *destinationVertex;
    QTimer *time;

    /*for client-server*/

    char sendData[2];
    Input input_s;


};

#endif // QTTEST_H
