#include "qttest.h"
#include "ui_qttest.h"
#include "Graph.h"

#define MAPPATH "C:/Users/bertugg/Documents/QTWorkspace/QTTest/Project1-395-UI/KatPlaniPP.jpg"

QTTest::QTTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QTTest)
{

    Graph g;
    vector<Vertex> list;
    g.add(Coor(10,10), Coor(10,50));
    g.add(Coor(68,18), Coor(10,50));
    g.add(Coor(10,50), Coor(68,18));
    list = g.getVertexList();

    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QBrush greenBrush(Qt::green);

    QPen blackPen(Qt::black);
    blackPen.setWidth(6);

    // Add Map First
    planPixmap = scene -> addPixmap(QPixmap(MAPPATH));


    // Create Destination Marker on map
    destinationMarker = scene -> addEllipse(0,0,40,40,blackPen,redBrush);
    destinationMarker->setFlag(QGraphicsItem::ItemIsMovable);

    // Create User Location Marker
    locationMarker = scene -> addPolygon(QPolygonF( QVector<QPointF>() << QPointF( 20, -20 ) << QPointF( 0, -20) << QPointF( 10, 20)),blackPen,blueBrush);
    locationMarker->setFlag(QGraphicsItem::ItemIsMovable);

    // Create Node Locations Marker
    for(uint i = 0; i < list.size(); ++i)
    {
        nodeLocationsMarker = scene -> addEllipse(list[i].getX(), list[i].getY(),25,25,blackPen,greenBrush);
    }

    //seekLocation();
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
