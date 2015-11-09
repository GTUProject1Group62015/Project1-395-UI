#ifndef QTTEST_H
#define QTTEST_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsPixmapItem>

namespace Ui {
class QTTest;
}

class QTTest : public QMainWindow
{
    Q_OBJECT

public:
    void seekLocation(); // Get User Location from hardware
    explicit QTTest(QWidget *parent = 0);
    ~QTTest();

private slots:
    void on_pushButton_clicked();

private:
    Ui::QTTest *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *destinationMarker;
    QGraphicsPolygonItem *locationMarker;
    QGraphicsPixmapItem *planPixmap;
};

#endif // QTTEST_H
