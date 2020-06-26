#include "serialcommunicator.h"

SerialCommunicator::SerialCommunicator(Status *_status)
{
#if defined(__linux__) && defined(SET_ALL_PAGE_PIGPIO_INIT)
    int __result = gpioInitialise();
#endif
    status = _status;
}

SerialCommunicator::~SerialCommunicator()
{
    qDebug() << Q_FUNC_INFO;
#if defined(__linux__) && defined(SET_ALL_PAGE_PIGPIO_INIT)
    gpioTerminate();
#endif
}


typedef union
{
    unsigned char a[4];
    float b;
} union_data;
void _ftoa(char buf[4], float number)
{
    int i;
    union_data data_s, data_r;
    data_s.b = number; // send할 float값을 세팅한다.
    // 캐릭터 배열의 메모리만을 복사한다!!!!
    memcpy(&data_r.a, &data_s.a, sizeof(data_s.a));
    for (i = 0; i < 4; i++)
        buf[i] = data_s.a[i];
}
float _atof(char buf[4])
{
    int i;
    union_data data_s = { 0,0,0,0 };
    float num = 0;
    for (i = 0; i < 4; i++)
        data_s.a[i] = buf[i];
    num = data_s.b;
    return num;
}
void SerialCommunicator::run()
{
    unsigned long baud = 9600;
    int recvLen = 0;
    char buf[15], newChar;
    QMessageBox msgBox;
    QString SerialDevice_ID;
    QProcess GetSerialDevice;


#ifdef __linux__ //

    if(status->fd > -1){
        while(1) // sync(fake infinite loop)
        {
            // Serial Interrupt.
            serWriteByte(status->fd, 's');

            // read signal
            if(serDataAvailable (status->fd)){
                newChar = serReadByte (status->fd);
                if(newChar == 's')
                {
                    buf[recvLen++] = newChar;
                    break;
                }
            }
        }


        while(!status->stopWhile)
        {
            // Serial Interrupt.
            serWriteByte(status->fd, 's');

            // read signal
            if(serDataAvailable (status->fd)){
                buf[recvLen++] = serReadByte(status->fd);
                if(recvLen == 15)
                {
                    recvLen = 0;
                    status->isWaterValid = buf[1];
                    status->tempC = _atof(&buf[2]);
                    status->humidity = _atof(&buf[6]);
                    status->Lux = _atof(&buf[10]);
      #ifdef SHOW_SERIAL_COMMUNICATION_READ_BUFFER_CONTENT
                    char output[100];
                    sprintf(output,"serial read buffer : {%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d}\n  isWaterValid :  %f,tempC :  %f,humidity :  %f,Lux : %f\n",
                            buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], buf[8], buf[9], buf[10], buf[11], buf[12], buf[13], buf[14],
                            status->isWaterValid, status->tempC, status->humidity, status->Lux);
                    qDebug(output);

      #endif
                }
            }
        }

    }
    else
        while(1)
            gpioDelay(500);
#endif
}
