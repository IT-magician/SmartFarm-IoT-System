#ifndef STATUS_H
#define STATUS_H

#include <QStringList>
#include <QString>
#include <QDebug>

class status
{
public:
    status();

    QStringList ConnectedClient;
    QString RPI_IP;
};

#endif // STATUS_H
