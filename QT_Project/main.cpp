#include "mainwindow.h"
#include "doorlocksystem.h"
#include "status.h"
#include "controlpanel.h"

#include "websocketserver.h"

#include <QDebug>
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

// Main 소스코드에서 관리할 UI(여기서는 Widget을 사용하였음)들을 Pointer로 전달하면 MainWindow클래스에는 관리할 윈도우(Widget)을 자유롭게 만질수 있음
// 단, 주의사항은 Main에서 모두 다 생성을 해야함.
// Main이 아닌 곳에서 인스턴스를 생성하면 제대로 동작하지 않음.

// Socket *.pro => QT Modules += WebSocket NetWork

#include <QMessageBox>
#include <QProcess>


#include "websocket.h"
#include "serialcommunicator.h"



#ifdef __linux__
#include <pigpio.h>
#endif



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *windows[3];
    WebSocketServer *server;
    Status status;
    MainWindow w(&status, windows); // MainWindow에서 Form(f)를 접근(제어)하기 위해 포인터 전달.
    DoorLockSystem security(&status, windows);
    ControlPanel controlPanel(&status, windows);
    SerialCommunicator *thread = new SerialCommunicator(&status);
    unsigned long baud = 9600;
    QObject::connect(thread, &SerialCommunicator::finished, thread, &QObject::deleteLater);


    QString mediator_ip_address = "220.69.244.50", mediator_ip_URL;

    windows[SECURITY_WINDOW]=&security;
    windows[CONTROL_PANEL]=&controlPanel;
    windows[SYSTEM_CONTROL]=&w;

#ifdef __linux__ //

        
    if(argc > 1){
        if(mediator_ip_address.split(".").count() == 4){
            mediator_ip_address = QString(argv[1]);
            qDebug() << "전달받은 IP : "<< mediator_ip_address;
        }
    }

    QMessageBox msgBox;
    msgBox.setText("To read the sensor value, remove the Arduino once and connect it..");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
    
    
        //get filedescriptor
        char errorMessage[1024];
        int ret = QMessageBox::Retry;
        int i = 0;
        
        do
        {
            if ((status.fd = serOpen ((char*)status.device[i++ % 2], baud, 0)) < 0){

                sprintf (errorMessage, "Unable to open serial device(%s) : %s\n", status.device[(i - 1) % 2], strerror (errno)) ;
                msgBox.setText(errorMessage);
                msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Retry | QMessageBox::Reset);
                ret = msgBox.exec();
                switch (ret) {
                case QMessageBox::Reset:
                #ifdef __linux__
                    // set Pin Power off
                    gpioWrite(BUBL1, RELAY_SW_PIN_LOW);
                    gpioWrite(BUBL2, RELAY_SW_PIN_LOW);
                    gpioWrite(BUBL3, RELAY_SW_PIN_LOW);
                    gpioWrite(BUBL4, RELAY_SW_PIN_LOW);


                    gpioWrite(HOT_BUBL1, RELAY_SW_PIN_LOW);
                    gpioWrite(HOT_BUBL2, RELAY_SW_PIN_LOW);
                    gpioWrite(HOT_BUBL3, RELAY_SW_PIN_LOW);

                    gpioWrite(PDLC_PIN, RELAY_SW_PIN_LOW);

                    //gpioWrite(WATER_PUMP_FB_SIGNAL, status.PIN_LOW);
                    gpioWrite(WATER_PUMP_PWM, status.PIN_LOW);


                    //gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, status.PIN_LOW);
                    gpioWrite(DOORLOC_MOTOR_PWM, status.PIN_LOW);
    \
                    gpioTerminate();
                #endif
                    QProcess::execute("shutdown -r now");
                    break;
                case QMessageBox::Retry:
                    //status.fd = serOpen ((char*)status.device[i++ % 2], baud, 0);
                    break;
                }
            }                                                                                                                       
        } while (ret != QMessageBox::Ok && status.fd < 0);
        
    
    if ((status.fd = serOpen ((char*)status.device, baud, 0)) > -1)
        // 스레드 시작
        thread->start();
    
#endif

#ifdef __linux__
    int __result = gpioInitialise();
    /*if (__result)
    {
       // pigpio initialisation failed.
        QMessageBox msgBox;
         msgBox.setText("pigpio initialisation failed.");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Retry | QMessageBox::Reset);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Reset:
           QStringList arguments;
            arguments<< "shutdown" << "-r" << "now";
            QProcess::execute(arguments);


            QString program = "shutdown";
            QStringList arguments;
            arguments << " -r" << " now";

            QProcess::execute("shutdown -r now");
            break;
        case QMessageBox::Retry:
            gpioInitialise();
            break;
        }
    }*/
    // pigpio initialised okay.


    // set Pin Mode
    gpioSetMode(BUBL1, PI_OUTPUT);
    gpioSetMode(BUBL2, PI_OUTPUT);
    gpioSetMode(BUBL3, PI_OUTPUT);
    gpioSetMode(BUBL4, PI_OUTPUT);
    //gpioSetMode(BUBL5, PI_OUTPUT);
    //gpioSetMode(BUBL6, PI_OUTPUT);
    //gpioSetMode(BUBL7, PI_OUTPUT);
    //gpioSetMode(BUBL8, PI_OUTPUT);


    gpioSetMode(HOT_BUBL1, PI_OUTPUT);
    gpioSetMode(HOT_BUBL2, PI_OUTPUT);
    gpioSetMode(HOT_BUBL3, PI_OUTPUT);

    gpioSetMode(PDLC_PIN, PI_OUTPUT);

    gpioSetMode(WATER_PUMP_FB_SIGNAL, PI_OUTPUT);
    gpioSetMode(WATER_PUMP_PWM, PI_OUTPUT);


    gpioSetMode(DOORLOC_MOTOR_FB_SIGNAL, PI_OUTPUT);
    gpioSetMode(DOORLOC_MOTOR_PWM, PI_OUTPUT);
    gpioSetMode(DOORLOC_CHECK_OPEN_SW, PI_INPUT);
    gpioSetMode(DOORLOC_CHECK_CLOSE_SW, PI_INPUT);

    // set Pin Power off
    gpioWrite(BUBL1, RELAY_SW_PIN_LOW);
    gpioWrite(BUBL2, RELAY_SW_PIN_LOW);
    gpioWrite(BUBL3, RELAY_SW_PIN_LOW);
    gpioWrite(BUBL4, RELAY_SW_PIN_LOW);


    gpioWrite(HOT_BUBL1, RELAY_SW_PIN_LOW);
    gpioWrite(HOT_BUBL2, RELAY_SW_PIN_LOW);
    gpioWrite(HOT_BUBL3, RELAY_SW_PIN_LOW);

    gpioWrite(PDLC_PIN, RELAY_SW_PIN_LOW);

    //gpioWrite(WATER_PUMP_FB_SIGNAL, status.PIN_LOW);
    gpioWrite(WATER_PUMP_PWM, status.PIN_LOW);
    gpioSetPWMrange(WATER_PUMP_PWM, 100);


    //gpioWrite(DOORLOC_MOTOR_FB_SIGNAL, status.PIN_LOW);
    gpioWrite(DOORLOC_MOTOR_PWM, status.PIN_LOW);
    gpioSetPWMrange(DOORLOC_MOTOR_PWM, 100);
#endif


    w.show();
    controlPanel.show();
    security.show();
    security.raise();



    mediator_ip_URL = "ws://" + mediator_ip_address + ":9000";
    WebSocket client(QUrl(mediator_ip_URL), true); // tell mediator that i'm RPI
    int port = 1234;

    server = new WebSocketServer(port, &status,/*debug*/false);
    QObject::connect(server, &WebSocketServer::closed, &a, &QCoreApplication::quit);



    return a.exec();
}
