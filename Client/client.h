#ifndef CLIENT_H
#define CLIENT_H


#include <QObject>
#include <QTcpSocket>


class Client : public QObject
{
    Q_OBJECT

private:
    QTcpSocket *clientSocket;

public:
    Client();

    void sendMesage(QString message);
    QString receiveMessage();
    void stop();

};

#endif
