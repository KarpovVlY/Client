#ifndef CLIENT_H
#define CLIENT_H


#include <QWidget>
#include <QTcpSocket>

class Client : public QWidget
{
public:
    Client();


    QTcpSocket *clientSocket;

    quint16     m_nNextBlockSize;



public:

    void connect();
    void sendMesage(QString message);
    void receiveMessage();
    void stop();


private slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(                            );
    void slotConnected   (                            );

};

#endif
