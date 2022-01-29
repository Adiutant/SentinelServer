#include "httpserver.h"


HttpServer::HttpServer(QObject *parent):
 QTcpServer(parent)
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

QString HttpServer::parseContent(QString row)
{
    QRegExp reg("[^Content: ][A-Z_]+");
    QString match;
    int pos=0;
    while ((pos = reg.indexIn(row,pos))!=-1)
    {
        match = reg.cap(0);
        pos += reg.matchedLength();
        qDebug()<<match;

    }
    return match;

}


void HttpServer::onReadyRead()
{
    QJsonDocument responseDocument;
    QByteArray response ;
    QTcpSocket* handlingSocket = qobject_cast<QTcpSocket*>(sender());
    QString content;
    QByteArray incomingRequest = handlingSocket->readAll();
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(incomingRequest,&error);
    qDebug()<<error.errorString() << error.offset <<error.error;
    QJsonObject root  = document.object();
    if (root["request"] == NEW_CLIENT_SIGNATURE)
    {
        QJsonObject responseObject;

        responseObject["response"] = NEW_CLIENT_SIGNATURE_ACCEPTED;

        responseDocument.setObject(responseObject);
        response = responseDocument.toJson();

    }
    if (root["request"] == LOGIN_CLIENT_SIGNATURE)
    {
        //implement db credentials checking and access token generating
        QJsonObject responseObject;

        responseObject["response"] = NEW_CLIENT_SIGNATURE_ACCEPTED;

        responseDocument.setObject(responseObject);
        response = responseDocument.toJson();

    }
    qDebug() << incomingRequest;
//    while(handlingSocket->canReadLine())
//    {
//        QString line = handlingSocket->readLine();
//        content = parseContent(line);
//        if (content == NEW_CLIENT_SIGNATURE)
//        {
//            QString responseBody = NEW_CLIENT_SIGNATURE_ACCEPTED;
//            response = "HTTP/1.1 200 OK\r\n\r\n";
//            response+=responseBody;
//        }
//        qDebug() << line<<"::"<<content;

//    }
    handlingSocket->write(response);
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
