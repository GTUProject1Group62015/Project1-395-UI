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
    g.addVertex(Coor(150,165)); // Z06 Kapi
    g.addVertex(Coor(180,164));
    g.addVertex(Coor(179,133));
    g.addVertex(Coor(226,165));
    g.addVertex(Coor(198,201)); // Z11 Kapi
    g.addVertex(Coor(223,203)); // Z11 Onu
    g.addVertex(Coor(220,360)); // Sol Cikis
    g.addVertex(Coor(227,377));
    g.addVertex(Coor(196,386)); // Bilgisayar Lab
    g.addVertex(Coor(195,555)); // Kantin Kapi
    g.addVertex(Coor(225,555)); // Kantin Onu
    g.addVertex(Coor(229,611)); // Giris Sol Kose
    g.addVertex(Coor(351,615)); // Giris Ic
    g.addVertex(Coor(349,678)); // Giris Dis
    g.addVertex(Coor(479,620)); // Giris Sag Kose
    g.addVertex(Coor(514,537)); // Z23 Kapi
    g.addVertex(Coor(489,540)); // Z23 Onu
    g.addVertex(Coor(516,388)); // Devre Lab
    g.addVertex(Coor(481,370)); // Sag Cikis Onu
    g.addVertex(Coor(515,360)); // Sag Cikis
    g.addVertex(Coor(515,202)); // Lojik Lab
    g.addVertex(Coor(487,202)); // Lojik Lab Onu
    g.addVertex(Coor(492,125));
    g.addVertex(Coor(561,163)); // Z10 Kapi
    g.addVertex(Coor(530,99)); // Z05 Kapi
    g.addVertex(Coor(526,130));
    g.addVertex(Coor(481,126));
    g.addVertex(Coor(399,97)); // Z04 Kapi
    g.addVertex(Coor(399,118)); // Z04 Onu
    g.addVertex(Coor(372,98)); // Arka Cikis İci
    g.addVertex(Coor(356,117)); // Arka Cikis Onu
    g.addVertex(Coor(310,98)); // Z02 Kapi

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
    destinationVertex = g.addVertex(Coor(destinationMarker->pos().x(), destinationMarker->pos().y()));

    // Create User Location Marker
    locationMarker = scene -> addPolygon(QPolygonF( QVector<QPointF>() << QPointF( 20, -20 ) << QPointF( 0, -20) << QPointF( 10, 20)),blackPen,blueBrush);
    locationMarker->setFlag(QGraphicsItem::ItemIsMovable);
    locationVertex = g.addVertex(Coor(locationMarker->pos().x(), locationMarker->pos().y()));

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
    destinationVertex.setVertex(destinationMarker->pos().x(),
                                destinationMarker->pos().y()
                                );
}

void QTTest::seekLocation()
{
    ui->label->setText("Seeking User Location...");
    locationVertex.setVertex(locationMarker->pos().x(), // get it from Server
                             locationMarker->pos().y()
                );
    // Get location from hardware
}
