#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H


#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include "status.h"

#include <QTimer>
#include <QFile>
#ifdef __linux__
#include <pigpio.h>
#endif

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)


class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketServer(quint16 port, Status *_status,bool debug = false, QObject *parent = nullptr);
    ~WebSocketServer();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

    void OnTimerCallbackFunc();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;
    Status *status;

    //int cycle_time1 = 30000;
    //QTimer *m_pTimer;
};

#endif // WEBSOCKETSERVER_H
