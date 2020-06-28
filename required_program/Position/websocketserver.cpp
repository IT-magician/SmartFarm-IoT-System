#include "websocketserver.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"



QT_USE_NAMESPACE

//! [constructor]
WebSocketServer::WebSocketServer(quint16 port, status *_share, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "Echoserver listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &WebSocketServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WebSocketServer::closed);
    }
    share = _share;


    //m_pTimer = new QTimer();
    //connect(m_pTimer, SIGNAL(timeout()), this, SLOT(OnTimerCallbackFunc()));
    //m_pTimer->start(cycle_time1);
}
//! [constructor]

WebSocketServer::~WebSocketServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

//! [onNewConnection]
void WebSocketServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &WebSocketServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &WebSocketServer::socketDisconnected);

    m_clients << pSocket;

}
//! [onNewConnection]

//! [processTextMessage]
void WebSocketServer::processTextMessage(QString message)
{
    char sendBuffer[10];
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Message received:" << message;
    if (pClient) {

        if(message == "I'M RPI")
        {
            //qDebug() << "My IP(Server) : " << QHostAddress(pClient->localAddress().toIPv4Address()).toString();
            //qDebug() << "RPI IP : " << QHostAddress(pClient->peerAddress().toIPv4Address()).toString();

            share->RPI_IP = QHostAddress(pClient->peerAddress().toIPv4Address()).toString();
            pClient->sendTextMessage("OK, I Got It");
            share->ConnectedClient << "RPI IP : " + QHostAddress(pClient->peerAddress().toIPv4Address()).toString();
        }
        else if(message == "Where's RPI")
        {
            if(share->RPI_IP.isEmpty())
                pClient->sendTextMessage("null");
            else
                pClient->sendTextMessage(share->RPI_IP);
            //share->ConnectedClient.append("Request RPI IP : " + share->RPI_IP);
            share->ConnectedClient << "IP Which Requested RPI IP : " + QHostAddress(pClient->peerAddress().toIPv4Address()).toString();
        }


    }
}
//! [processTextMessage]

//! [processBinaryMessage]
void WebSocketServer::processBinaryMessage(QByteArray message)
{
    if (m_debug)
        qDebug() << "Binary Message received:" << message;

}
//! [processBinaryMessage]

//! [socketDisconnected]
void WebSocketServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
//! [socketDisconnected]



