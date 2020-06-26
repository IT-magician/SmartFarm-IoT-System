#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

#include <QWidget>

// Source URL : https://stuff.mit.edu/afs/athena/software/texmaker_v5.0.2/qt57/doc/qtwebsockets/qtwebsockets-echoclient-example.html

class WebSocket : public QObject
{
    Q_OBJECT
public:
    explicit WebSocket(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

    QWebSocket m_webSocket;

Q_SIGNALS:

private Q_SLOTS:
    void closed();
    void onConnected();
    void onTextMessageReceived(QString message); // QString To char array => https://saengjja.tistory.com/257
    void onBinaryMessageReceived(QByteArray message);
private:
    QUrl m_url;
    QWidget **windows;
    bool m_debug;
    void Open();
};


#endif // WEBSOCKET_H
