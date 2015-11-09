#include "qttest.h"
#include "ui_qttest.h"

#define MAPPATH "C:/Users/bertugg/Documents/QTWorkspace/QTTest/kroki.jpg"

QTTest::QTTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QTTest)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);

    QPen blackPen(Qt::black);
    blackPen.setWidth(6);

    // Add Map First
    planPixmap = scene -> addPixmap(QPixmap(MAPPATH));


    // Create Destination Marker on map
    destinationMarker = scene -> addEllipse(0,0,100,100,blackPen,redBrush);
    destinationMarker->setFlag(QGraphicsItem::ItemIsMovable);

    // Create User Location Marker
    locationMarker = scene -> addPolygon(QPolygonF( QVector<QPointF>() << QPointF( 20, -20 ) << QPointF( 0, -20) << QPointF( 10, 20)),blackPen,blueBrush);
    locationMarker->setFlag(QGraphicsItem::ItemIsMovable);

    seekLocation();
}

QTTest::~QTTest()
{
    delete ui;
}

void QTTest::on_pushButton_clicked()
{
    // Print destination location
    ui->label->setText(QString::number(destinationMarker->pos().x()) + ", " + QString::number(destinationMarker->pos().y()));
}

void QTTest::seekLocation()
{
    ui->label->setText("Seeking User Location...");
    // Get location from hardware
}
