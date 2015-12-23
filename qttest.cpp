#include "qttest.h"
#include "ui_qttest.h"
#include "Graph.h"
#include <QGraphicsItemGroup>


#define MAPPATH "C:/Users/Guner/Desktop/Project1-395-UI-WithGraph/KatPlaniPP.jpg"
#define DMWIDTH 35 // Destination Marker Width
#define NLWIDTH 15 // Node Location Marker Width
#define DEVELOPERMODE true

QTTest::QTTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QTTest)
{
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);
    QBrush greenBrush(Qt::green);
    QPen blackPen(Qt::black);

    vector<Vertex> vertexList;
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
    vertexList = g.getVertexList(); // Refers all vertexes


    g.setEdge(vertexList[0],vertexList[1]);
    g.setEdge(vertexList[1],vertexList[2]);
    g.setEdge(vertexList[1],vertexList[3]);
    /*
    g.add(Coor(150,165),Coor(180,164));
    g.add(Coor(180,164),Coor(179,133));
    g.add(Coor(179,133),Coor(226,165));
    g.add(Coor(226,165),Coor(223,203));
    g.add(Coor(198,201),Coor(223,203));
    g.add(Coor(220,360),Coor(223,203));

    // Get Edge List Must Be Implemented
    // Shortest Path Must Return Edge List
    */

    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    blackPen.setWidth(6);

    // Add Map First
    planPixmap = scene -> addPixmap(QPixmap(MAPPATH));



    // Create Destination Marker on map
    destinationMarker = scene -> addEllipse(0,0,DMWIDTH,DMWIDTH,blackPen,redBrush);
    destinationMarker->setFlag(QGraphicsItem::ItemIsMovable);
    destinationVertex = g.addVertex(Coor(destinationMarker->pos().x() + DMWIDTH/2, destinationMarker->pos().y() + DMWIDTH/2));
    connectToServer();
    // Create User Location Marker
    locationMarker = scene -> addPolygon(QPolygonF( QVector<QPointF>() << QPointF( 20, -20 ) << QPointF( 0, -20) << QPointF( 10, 20)),blackPen,blueBrush);
    locationMarker->setFlag(QGraphicsItem::ItemIsMovable);
    locationMarker->setRotation(input_s.d*-1);
    locationVertex = g.addVertex(Coor(locationMarker->pos().x(), locationMarker->pos().y()));

    // Create Node Locations Marker
    if(DEVELOPERMODE)
    {
        // Draw lines between all vertexes
        vector<Edge> edgeList = g.getAllEdge();
        for(uint i = 0; i < edgeList.size()-1; ++i)
        {
            // Add Line for Edges
            drawLine(edgeList[i].getSourceVertex(), edgeList[i].getDestVertex(), blackPen);
        }

        for(uint i = 0; i < vertexList.size(); ++i)
        {
            nodeLocationsMarker = scene -> addEllipse(vertexList[i].getX()-NLWIDTH/2,
                                                      vertexList[i].getY()-NLWIDTH/2,
                                                      NLWIDTH,
                                                      NLWIDTH,
                                                      blackPen,
                                                      greenBrush);
        }
    }
    /*
    // Draw lines between all vertexes
    for(uint i = 0; i < vertexList.size()-1; ++i)
    {
        // Add Line for Edges
        drawLine(vertexList[i],vertexList[i+1] );

    }
    */
    //seekLocation();

    time=new QTimer(this);
    connect(time, SIGNAL(timeout()), this, SLOT(update2()));
    time->start(1000);

}

void QTTest::update2(){
    int angle= locationMarker->rotation();
    /*int x=locationMarker->pos().x;
    int y=locationMarker->pos().y;
*/
    char buf[LINE_ARRAY_SIZE];
    // Read the modified line back from the server.
    if (recv(socketDescriptor, buf, MAX_LINE, 0) < 0) {
        cerr << "didn't get response from server?";
        ::close(socketDescriptor);
        exit(1);
    }

    /*

     soft

     */
    input_s.setInput(string(buf));
    cerr << "Modified: " << buf << "\n";
    cerr << "x: " << input_s.x << " y:" << input_s.y << " d: " << input_s.d << " rec: " << input_s.rec <<  endl;
    int result;
    /*

     BURASI YAZILIMCILARIN ALANI
     GELEN DATA PARS EDİLECEK GEREKLİ İŞLEMLER YAPILACAK
     RESULT OLARAK 1 2 3 4 5 SAYILARINDAN BİRİSİ DÖNECEK

     */
    if (input_s.d < 10 || input_s.d > 350) {
        result = 2;
    } else if (input_s.d >= 10 && input_s.d < 180) {
        result = 3;
    } else {
        result = 1;
    }

    sprintf(sendData, "%d", result);
    //strcat(buf, sendData);

    //strcat(buf, "****");
    //cerr << "Modified: " << buf << "\n";
    // Send the line to the server.
    if (send(socketDescriptor, sendData, 1 + 1, 0) < 0) {
        cerr << "cannot send data ";
        ::close(socketDescriptor);
        exit(1);
    }

    // Zero out the buffer.
    memset(buf, 0x0, LINE_ARRAY_SIZE);

    // Prompt the user for input, then read in the input, up to MAX_LINE
    // charactars, and then dispose of the rest of the line, including
    // the newline character.  As above.
    //cout << "Input: ";
    //cin.get(buf, MAX_LINE, '\n');
    //while (cin.get(c) && c != '\n')
    //  ;

    locationMarker->setRotation(input_s.d*-1);
    scene->update();
}

void QTTest::connectToServer(){
    unsigned short int serverPort = 5005;
    struct sockaddr_in serverAddress;
    struct hostent *hostInfo;
    char buf[LINE_ARRAY_SIZE];
    WSADATA AAA;

    //cout << "Enter server host name or IP address: ";
    //cin.get(buf, MAX_LINE, '\n');

    // gethostbyname() takes a host name or ip address in "numbers and
    // dots" notation, and returns a pointer to a hostent structure,
    // which we'll need later.  It's not important for us what this
    // structure is actually composed of.
    WSAStartup(2,&AAA);
    hostInfo = gethostbyname("162.243.185.121");
    if (hostInfo == NULL) {
        cerr << WSAGetLastError() << endl;
        cout << "problem interpreting host: " << buf << "\n";
        exit(1);
    }

    //cout << "Enter server port number: ";
    //cin >> serverPort;
    //cin.get(c); // dispose of the newline

    // Create a socket.  "AF_INET" means it will use the IPv4 protocol.
    // "SOCK_STREAM" means it will be a reliable connection (i.e., TCP;
    // for UDP use SOCK_DGRAM), and I'm not sure what the 0 for the last
    // parameter means, but it seems to work.
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDescriptor < 0) {
        cerr << "cannot create socket\n";
        exit(1);
    }

    // Connect to server.  First we have to set some fields in the
    // serverAddress structure.  The system will assign me an arbitrary
    // local port that is not in use.
    serverAddress.sin_family = hostInfo->h_addrtype;
    memcpy((char *) &serverAddress.sin_addr.s_addr, hostInfo->h_addr_list[0],
            hostInfo->h_length);
    serverAddress.sin_port = htons(serverPort);

    if (::connect(socketDescriptor, (struct sockaddr *) &serverAddress,
            sizeof(serverAddress)) < 0) {
        cerr << WSAGetLastError() << endl;
        cerr << "cannot connect\n";
        exit(1);
    }

    cout << "\nEnter some lines, and the server will modify them and\n";
    cout << "send them back.  When you are done, enter a line with\n";
    cout << "just a dot, and nothing else.\n";
    cout << "If a line is more than " << MAX_LINE << " characters, then\n";
    cout << "only the first " << MAX_LINE << " characters will be used.\n\n";

    // Prompt the user for input, then read in the input, up to MAX_LINE
    // charactars, and then dispose of the rest of the line, including
    // the newline character.
    cout << "Input: ";
    //cin.get(buf, MAX_LINE, '\n');
    //while (cin.get(c) && c != '\n')
    //  ;

    // Stop when the user inputs a line with just a dot.

    // Read the modified line back from the server.
    if (recv(socketDescriptor, buf, MAX_LINE, 0) < 0) {
        cerr << "didn't get response from server?";
        ::close(socketDescriptor);
        exit(1);
    }

    /*

     soft

     */
    input_s.setInput(string(buf));
    cerr << "Modified: " << buf << "\n";
    cerr << "x: " << input_s.x << " y:" << input_s.y << " d: " << input_s.d << " rec: " << input_s.rec <<  endl;
    int result;
    /*

     BURASI YAZILIMCILARIN ALANI
     GELEN DATA PARS EDİLECEK GEREKLİ İŞLEMLER YAPILACAK
     RESULT OLARAK 1 2 3 4 5 SAYILARINDAN BİRİSİ DÖNECEK

     */
    if (input_s.d < 10 || input_s.d > 350) {
        result = 2;
    } else if (input_s.d >= 10 && input_s.d < 180) {
        result = 3;
    } else {
        result = 1;
    }

    sprintf(sendData, "%d", result);
    //strcat(buf, sendData);

    //strcat(buf, "****");
    //cerr << "Modified: " << buf << "\n";
    // Send the line to the server.
    if (send(socketDescriptor, sendData, 1 + 1, 0) < 0) {
        cerr << "cannot send data ";
        ::close(socketDescriptor);
        exit(1);
    }

    // Zero out the buffer.
    memset(buf, 0x0, LINE_ARRAY_SIZE);

    // Prompt the user for input, then read in the input, up to MAX_LINE
    // charactars, and then dispose of the rest of the line, including
    // the newline character.  As above.
    //cout << "Input: ";
    //cin.get(buf, MAX_LINE, '\n');
    //while (cin.get(c) && c != '\n')
    //  ;


    //close(socketDescriptor);
}




QTTest::~QTTest()
{
    delete ui;
    ::close(socketDescriptor);
}

void QTTest::on_pushButton_clicked()
{
    // Print destination location
    //ui->label->setText(QString::number(destinationMarker->pos().x()+ DMWIDTH/2) + ", " + QString::number(destinationMarker->pos().y()+ DMWIDTH/2));

    QPen redPen(Qt::red);
    redPen.setWidth(5);

    destinationVertex->setVertex(destinationMarker->pos().x() + DMWIDTH/2, destinationMarker->pos().y() + DMWIDTH/2);
    locationVertex->setVertex(locationMarker->pos().x() + 10, locationMarker->pos().y());

    ui->label->setText("destination vertex = " + QString::number(destinationVertex->getX()) + ", " + QString::number(destinationVertex->getY()));

    clearLines();

    QGraphicsLineItem *line;
    line = drawLine(*locationVertex, g.getVertexList()[0], redPen);
    drawedLines.push_front(line);
    for(uint i = 0; i < g.getVertexList().size()-3; ++i)
    {
        // Add Line for Edges
        line = drawLine(g.getVertexList()[i], g.getVertexList()[i+1], redPen);
        drawedLines.push_front(line);
    }
    line = drawLine(*destinationVertex, g.getVertexList()[g.getVertexList().size()-3], redPen);
    drawedLines.push_front(line);
        locationMarker->setRotation(45);

}

void QTTest::seekLocation()
{
    ui->label->setText("Seeking User Location...");
}

QGraphicsLineItem* QTTest::drawLine(Vertex &c1, Vertex &c2, QPen pen)
{
    return scene -> addLine(c1.getX(),c1.getY(),c2.getX(),c2.getY(),pen);
}

void QTTest::clearLines()
{
    for(int i = 0; i < drawedLines.size(); ++i)
    {
        scene->removeItem(drawedLines[i]);
        //scene->update();
    }
    drawedLines.clear();
    scene->update();
}
