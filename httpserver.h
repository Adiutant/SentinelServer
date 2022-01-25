#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
//#include <QtWidgets>
#include <iostream>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUrl>

class HttpServer :public QTcpServer
{

Q_OBJECT

public slots:
    void onReadyRead();
    void onDisconnect();

public:
    explicit HttpServer(QObject *parent=0);
    ~HttpServer();

    void incomingConnection(qintptr handle);
private:



};

#endif // HTTPSERVER_H
