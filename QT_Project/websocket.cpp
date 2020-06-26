#include "websocket.h"
#include <QtCore/QDebug>

#include <QMessageBox>

#include <QProcess>

QT_USE_NAMESPACE

WebSocket::WebSocket(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &WebSocket::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WebSocket::closed);
    m_webSocket.open(QUrl(url));
    m_url = url;

}

void WebSocket::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &WebSocket::onTextMessageReceived);
    connect(&m_webSocket, &QWebSocket::binaryMessageReceived,
            this, &WebSocket::onBinaryMessageReceived);

    m_webSocket.sendTextMessage("I'M RPI");
}

void WebSocket::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Text Message received:" << message;
    //m_webSocket.close();
}

void WebSocket::onBinaryMessageReceived(QByteArray message)
{
    //if (m_debug)
        qDebug() << "Binary Message received:" << message;
    //m_webSocket.close();

}

void WebSocket::closed()
{
    qDebug() << "Connection is closed, Retry Connection.";

    QMessageBox msgBox;
    msgBox.setText("Network is invalid or Can't continue to connect mediator(my position) server\nCheck your Network Device");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Retry | QMessageBox::Reset);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Reset:
       /* QStringList arguments;
        arguments<< "shutdown" << "-r" << "now";
        QProcess::execute(arguments);


        QString program = "shutdown";
        QStringList arguments;
        arguments << " -r" << " now";*/

        QProcess::execute("shutdown -r now");
        break;
    case QMessageBox::Retry:
        m_webSocket.open(QUrl(m_url));
        break;
    }
}
void WebSocket::Open()
{
    m_webSocket.open(QUrl(m_url));
}
