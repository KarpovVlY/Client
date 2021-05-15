#include "client.h"


Client::Client()
{
    clientSocket = new QTcpSocket(this);
    clientSocket->connectToHost("localhost", 2160);

    qDebug() << "Connected";
}


QString Client::receiveMessage()
{
    clientSocket->waitForReadyRead(-1);

    QString data;
    if(clientSocket->bytesAvailable() > 0)
        data = clientSocket->readAll();

    return data;
}


void Client::sendMesage(QString message)
{
    QTextStream os(clientSocket);
    os << message << '\n';
}



void Client::stop()
{
    sendMesage("MC_STOP");
    clientSocket->waitForBytesWritten(3000);
    clientSocket->disconnectFromHost();
}

