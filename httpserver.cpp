#include "httpserver.h"


HttpServer::HttpServer(QObject *parent): QTcpServer(parent)
{
        if (listen(QHostAddress::Any,80))
        {
            qDebug() << "Server started";
        }
        else
        {
            qDebug() <<"server starting error" <<errorString();

        }
}

HttpServer::~HttpServer()
{

}


void HttpServer::onReadyRead()
{
    QTcpSocket* handlingSocket = qobject_cast<QTcpSocket*>(sender());
    qDebug() << handlingSocket->readAll();
    QString response;
    if (handlingSocket->readAll() == NEW_CLIENT_SIGNATURE)
    {
        QString responseBody = NEW_CLIENT_SIGNATURE_ACCEPTED;
        response = "HTTP/1.1 200 OK\r\n\r\n";
        response+=responseBody;
    }
    handlingSocket->write(response.toUtf8());
    handlingSocket->disconnectFromHost();

}

void HttpServer::onDisconnect()
{
    QTcpSocket* handlingSocket = qobject_cast<QTcpSocket*>(sender());
    handlingSocket->close();
    handlingSocket->deleteLater();

}

void HttpServer::incomingConnection(qintptr handle)
{
    QTcpSocket* newSocket = new QTcpSocket();
    newSocket->setSocketDescriptor(handle);
    connect(newSocket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    connect(newSocket,SIGNAL(disconnected()),this,SLOT(onDisconnect()));

}
