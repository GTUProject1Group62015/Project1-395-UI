#ifndef QTTEST_H
#define QTTEST_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsPixmapItem>
#include "Vertex.h"


namespace Ui {
class QTTest;
}

class QTTest : public QMainWindow
{
    Q_OBJECT

public:
    void seekLocation(); // Get User Location from hardware
    QGraphicsLineItem *drawLine(Vertex &c1, Vertex &c2); // Draw A line between 2 coordinates
    explicit QTTest(QWidget *parent = 0);
    ~QTTest();

private slots:
    void on_pushButton_clicked();

private:
    Ui::QTTest *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *destinationMarker;
    QGraphicsPolygonItem *locationMarker;
    QGraphicsEllipseItem *nodeLocationsMarker;
    QGraphicsPixmapItem *planPixmap;
    Vertex locationVertex;
    Vertex destinationVertex;

};

#endif // QTTEST_H
