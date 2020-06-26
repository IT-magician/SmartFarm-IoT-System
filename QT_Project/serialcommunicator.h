#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H
#include <QThread>
#include <QMessageBox>
#include <QProcess>
#include <QtDebug>
#include "status.h"

#ifdef __linux__
#include <pigpio.h>
#endif

class SerialCommunicator : public QThread
{
    Q_OBJECT
public:
    SerialCommunicator(Status *_status);
    ~SerialCommunicator() override;

protected:
    void run() override;
    Status *status;
};

#endif // SERIALCOMMUNICATOR_H
