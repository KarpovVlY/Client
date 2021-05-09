#include "client.h"

Client::Client()
{

    clientSocket = new QTcpSocket();



    qDebug() << "Created";
}



void Client::connect()
{
    clientSocket->connectToHost("localhost", 2160);

    qDebug() << "Connected";

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
