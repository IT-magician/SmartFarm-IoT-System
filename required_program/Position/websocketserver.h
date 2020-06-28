#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H


#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

#include <QTimer>
#include "status.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)


class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketServer(quint16 port, status *_share, bool debug = false, QObject *parent = nullptr);
    ~WebSocketServer();
    status *share;

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();


private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;

};

#endif // WEBSOCKETSERVER_H
