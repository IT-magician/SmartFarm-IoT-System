#include "websocketserver.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"



QT_USE_NAMESPACE

//! [constructor]
WebSocketServer::WebSocketServer(quint16 port, Status *_status,bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    status = _status;
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "Echoserver listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &WebSocketServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WebSocketServer::closed);
    }


#if defined(__linux__) && defined(SET_ALL_PAGE_PIGPIO_INIT)
    int __result = gpioInitialise();
#endif
    //m_pTimer = new QTimer();
    //connect(m_pTimer, SIGNAL(timeout()), this, SLOT(OnTimerCallbackFunc()));
    //m_pTimer->start(cycle_time1);
}
//! [constructor]

WebSocketServer::~WebSocketServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
#if defined(__linux__) && defined(SET_ALL_PAGE_PIGPIO_INIT)
    gpioTerminate();
#endif
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

        sendBuffer[0] = 0;

        sendBuffer[1] = status->Current_LED_Status_Value; // Bulbs & Hot Bulbs

        if(status->isOn_PDLC) // PDLC
            sendBuffer[2] = 1;
        else
            sendBuffer[2] = 0;

        if(status->isOn_waterPump && status->isWaterValid == 1)
        {
            sendBuffer[3] = 1;
        }
        else
        {
            sendBuffer[3] = 0;
        }
        sendBuffer[4] = status->isWaterValid;

        if(status->isDoorOpen)
        {
            sendBuffer[5] = 1;
        }
        else
        {
            sendBuffer[5] = 0;
        }
        if(status->isDoorClose)
        {
            sendBuffer[6] = 1;
        }
        else
        {
            sendBuffer[6] = 0;
        }
        if(status->isDoorOpening)
        {
            sendBuffer[7] = 1;
        }
        else
        {
            sendBuffer[7] = 0;
        }
        QString stringBuf = "isWaterValid:" + QString::number(status->isWaterValid);
        stringBuf += ",tempC:" + QString::number(status->tempC);
        stringBuf += ",humidity:" + QString::number(status->humidity);
        stringBuf += ",Lux:" + QString::number(status->Lux);
        pClient->sendTextMessage(stringBuf);

        pClient->sendBinaryMessage(QByteArray(sendBuffer, 8));
    }
}
//! [processTextMessage]

//! [processBinaryMessage]
void WebSocketServer::processBinaryMessage(QByteArray message)
{
    /*
     * 기준 : 서버쪽
     * LED : 클라이언트가 서버에게 전송하는 바이트수 : 3, 서버가 클라이언트에게 전송하는 바이트수 : 2
     * PDLC : 클라이언트가 서버에게 전송하는 바이트수 : 2, 서버가 클라이언트에게 전송하는 바이트수 : 2
     * 물펌프, 도어락도 PDLC와 같음
     */


    char sendBuffer[20];
    QByteArray sendMessage;
    QFile file("password.bin");

    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Binary Message received:" << message;

    switch (message[0]) {
        case 0:// all <- WebSocket에서 리스너가 아닌 영역에서 보내려면 클라이언트측에서 동기를 맞춰주는 것을 넣어야하기 때문에 TextMessage로 보냄
        break; // ******************** End Of All ********************
        case 1:// bulb
        if(message[1] & 0x01)
            // set the status that client requested.
            if(message[2])
            {
                status->isOn_bulb1 = true;
                status->Current_LED_Status_Value |= 0x01;
#ifdef __linux__
                gpioWrite(BUBL1, RELAY_SW_PIN_HIGH);
#endif
            }
            else
            {
                status->isOn_bulb1 = false;
                status->Current_LED_Status_Value &=~ 0x01;
#ifdef __linux__
                gpioWrite(BUBL1, RELAY_SW_PIN_LOW);
#endif
            }

        else if(message[1] & 0x02)
            if(message[2])
            {
                status->isOn_bulb2 = true;
                status->Current_LED_Status_Value |= 0x02;
#ifdef __linux__
                gpioWrite(BUBL2, RELAY_SW_PIN_HIGH);
#endif
            }
            else {
                status->isOn_bulb2 = false;
                status->Current_LED_Status_Value &=~ 0x02;
#ifdef __linux__
                gpioWrite(BUBL2, RELAY_SW_PIN_LOW);
#endif

            }

        else if(message[1] & 0x04)
            if(message[2])
            {
                status->isOn_bulb3 = true;
                status->Current_LED_Status_Value |= 0x04;
#ifdef __linux__
                gpioWrite(BUBL3, RELAY_SW_PIN_HIGH);
#endif
            }
            else
            {
                status->isOn_bulb3 = false;
                status->Current_LED_Status_Value &=~ 0x04;
#ifdef __linux__
                gpioWrite(BUBL3, RELAY_SW_PIN_LOW);
#endif
            }

        else if(message[1] & 0x08)
            if(message[2])
            {
                status->isOn_bulb4 = true;
                status->Current_LED_Status_Value |= 0x08;
#ifdef __linux__
                gpioWrite(BUBL4, RELAY_SW_PIN_HIGH);
#endif
            }
            else
            {
                status->isOn_bulb4 = false;
                status->Current_LED_Status_Value &=~ 0x08;
#ifdef __linux__
                gpioWrite(BUBL4, RELAY_SW_PIN_LOW);
#endif
            }
        else if(message[1] & 0x10)
            if(message[2])
            {
                status->isOn_hotBulb1 = true;
                status->Current_LED_Status_Value |= 0x10;
#ifdef __linux__
                gpioWrite(HOT_BUBL1, RELAY_SW_PIN_HIGH);
#endif
            }
            else
            {
                status->isOn_hotBulb1 = false;
                status->Current_LED_Status_Value &=~ 0x10;
#ifdef __linux__
                gpioWrite(HOT_BUBL1, RELAY_SW_PIN_LOW);
#endif
            }

        else if(message[1] & 0x20)
            if(message[2])
            {
                status->isOn_hotBulb2 = true;
                status->Current_LED_Status_Value |= 0x20;
#ifdef __linux__
                gpioWrite(HOT_BUBL2, RELAY_SW_PIN_HIGH);
#endif
            }
            else
            {
                status->isOn_hotBulb2 = false;
                status->Current_LED_Status_Value &=~ 0x20;
#ifdef __linux__
                gpioWrite(HOT_BUBL2, RELAY_SW_PIN_LOW);
#endif
            }

        else if(message[1] & 0x40)
            if(message[2])
            {
                status->isOn_hotBulb3 = true;
                status->Current_LED_Status_Value |= 0x40;
#ifdef __linux__
                gpioWrite(HOT_BUBL3, RELAY_SW_PIN_HIGH);
#endif
            }
            else
            {
                status->isOn_hotBulb3 = false;
                status->Current_LED_Status_Value &=~ 0x40;
#ifdef __linux__
                gpioWrite(HOT_BUBL3, RELAY_SW_PIN_LOW);
#endif
            }
            
            
                

        sendBuffer[0]=1;
        sendBuffer[1] = status->Current_LED_Status_Value;
        Q_FOREACH(QWebSocket *client, m_clients)
        {
            //client->sendBinaryMessage(message);
            client->sendBinaryMessage(sendBuffer);
        }
        break; // ******************** End Of 'LED' ********************
        case 2: // pdlc
        if(message[1])
        {
            status->isOn_PDLC = true;
            sendBuffer[1] = 1;
#ifdef __linux__
            gpioWrite(PDLC_PIN, RELAY_SW_PIN_LOW);
#endif
        }
        else
        {
            status->isOn_PDLC = false;
            sendBuffer[1] = 0;
#ifdef __linux__
            gpioWrite(PDLC_PIN, RELAY_SW_PIN_HIGH);
#endif
        }

        sendBuffer[0]=2;
        Q_FOREACH(QWebSocket *client, m_clients)
        {
            //client->sendBinaryMessage(message);
            client->sendBinaryMessage(sendBuffer);
        }
        break; // ******************** End Of 'pdlc' ********************
        case 3: // water pump
        if(message[1] && status->isWaterValid == 1)
        {
            sendBuffer[1] = 1;
            status->currentWaterPower = status->PIN_HIGH * WATER_PUMP_DEFAULT_POWER;
            status->isOn_waterPump = true;
#ifdef __linux__
            gpioPWM(WATER_PUMP_PWM, status->currentWaterPower);
#endif
        }
        else
        {
            sendBuffer[1] = 0;
            status->currentWaterPower = status->PIN_LOW * 100;// LOW (For interoperability with Pull-up)
            status->isOn_waterPump = false;
#ifdef __linux__
            gpioPWM(WATER_PUMP_PWM, status->currentWaterPower);
#endif
        }
        sendBuffer[0] = 3;
        sendBuffer[2] = status->isWaterValid;
        Q_FOREACH(QWebSocket *client, m_clients)
        {
            client->sendBinaryMessage(QByteArray(sendBuffer, 3));
        }

        break; // ************************ End Of 'water pump' ************************
        case 4: // sensor - temperature

        break; // ********************* End Of 'sensor - temperature' **********************
        case 5: // sensor - humidity

        break; // *********************** End Of 'sensor - humidity' ***********************
        case 6: // doorLock - Make To Open/Close
        if(message[1])
        {
            sendBuffer[1] = 1;
            status->isIgnoreOpenSW_Status = false;
            status->currentDoorPower = status->PIN_HIGH * DOORLOCK_DEFAULT_POWER;// HIGH (For interoperability with Pull-up);
            status->isOn_doorMotor = true;
#ifdef __linux__
            gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, MOTOR_FORWARD);
            gpioPWM(DOORLOC_MOTOR_PWM, status->currentDoorPower);
#endif
                status->isDoorMotor_Forward = true;
        }
        else
        {
            sendBuffer[1] = 0;
            status->isIgnoreCloseSW_Status = false;
            status->currentDoorPower = status->PIN_HIGH * DOORLOCK_DEFAULT_POWER;// HIGH (For interoperability with Pull-up);
            status->isOn_doorMotor = true;
#ifdef __linux__
            gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, MOTOR_BACKWARD);
            gpioPWM(DOORLOC_MOTOR_PWM, status->currentDoorPower);
#endif
                status->isDoorMotor_Forward = false;
        }
        sendBuffer[0] = 6;
        pClient->sendBinaryMessage(QByteArray(sendBuffer, 2));
        break; // ***************** End Of 'doorLock - Make To Open/Close' *****************
        case 7: // doorLock - Open/Close

        // Nothing of action on server, This code is translate on client. "Code 0" of recvBuf[5] is Door Open/Close Status.

        break; // ******************** End Of 'doorLock - Open/Close' ********************
        int i;
        case 8: // doorLock - Chage Password
            for(i = 0;i < message[1];i++)
                status->password[i] = message[2 + i];
            status->password[i] = NULL;
            status->current_password_len = message[1];
            status->isChanged_CurrentPassword = true;
            //qDebug() << "make new password(file)";
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream out(&file);
                //qDebug() << "opened file";
                for(int i = 0;i<message[1];i++)
                    out << status->password[i];
                file.close();
            }

            sendBuffer[0] = 8;

            pClient->sendBinaryMessage(QByteArray(sendBuffer, 1));
            break; // ******************** End Of 'doorLock - Chage Password' ********************
        case 9: // doorLock - Set Temporary Password
            for(i = 0;i < message[1];i++)
                status->temporary_password[i] = message[2 + i];
            status->temporary_password[i] = NULL;
            status->current_temporary_password_len = message[1];
            status->isSet_TemporaryPassword = true;

            sendBuffer[0] = 9;

            pClient->sendBinaryMessage(QByteArray(sendBuffer, 1));
            break; // ******************** End Of 'doorLock - Set Temporary Password' ********************
        case 10: // doorLock - Send Current Temporary Password if it is valid or length is 0 if it is invalid.
            sendBuffer[0] = 10;
            if(status->isSet_TemporaryPassword){
                for(int i = 0;i < status->current_temporary_password_len;i++){
                    sendBuffer[6 + i] = status->temporary_password[i];
                }
                sendBuffer[1] = (status->current_temporary_password_expiredTime & 0xff000000) >> 18;
                sendBuffer[2] = ((status->current_temporary_password_expiredTime & 0xff0000) >> 12)/0x10;
                sendBuffer[3] = (status->current_temporary_password_expiredTime & 0xff00) >> 8;
                sendBuffer[4] = (status->current_temporary_password_expiredTime & 0xff);
                sendBuffer[5] = status->current_temporary_password_len;
                pClient->sendBinaryMessage(QByteArray(sendBuffer, sendBuffer[5] + 6));
            }
            else{
                sendBuffer[2] = 0;
                pClient->sendBinaryMessage(QByteArray(sendBuffer, 2));
            }

            break; // ******************** End Of 'doorLock - Send Current Temporary Password' ********************

    }
//#endif
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


void WebSocketServer::OnTimerCallbackFunc()
{
    char sendBuffer[10];

    sendBuffer[0] = 0;
    sendBuffer[1] = status->Current_LED_Status_Value;

    Q_FOREACH(QWebSocket *client, m_clients)
    {
        client->sendBinaryMessage(sendBuffer);
    }
}

