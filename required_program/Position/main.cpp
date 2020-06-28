#include "mainwindow.h"

#include <QApplication>

#include "websocketserver.h"
#include "share.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    status share;
    MainWindow w(&share);
    WebSocketServer *server;


    bool debug = true;
    int port = 1234;

    server = new WebSocketServer(9000, &share, debug);
    QObject::connect(server, &WebSocketServer::closed, &a, &QCoreApplication::quit);

    w.show();


    return a.exec();
}
