
#include "qttest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTTest w;
    try
    {


        w.show();


    }
    catch(...) /* ysa dan sevgiler*/
    {
    ::close(w.socketDescriptor);
    }


    return a.exec();

}
