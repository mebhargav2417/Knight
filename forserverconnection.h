#ifndef FORSERVERCONNECTION_H
#define FORSERVERCONNECTION_H

#include<QString>
class ForServerConnection
{
public:
    ForServerConnection();
    QString makeConnection(QString,QByteArray);
};

#endif // FORSERVERCONNECTION_H
