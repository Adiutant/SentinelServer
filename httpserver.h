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
#include <string>
#include <QRegExp>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <vector>
#include "RSA.h"

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
    std::vector<QString> accessTokens;
    QString parseContent(QString row);
    const QString NEW_CLIENT_SIGNATURE = "NEW_CLIENT_ATTACHED";
    const QString NEW_CLIENT_SIGNATURE_ACCEPTED = "NEW_CLIENT_ATTACHED_YES";
    const QString LOGIN_CLIENT_SIGNATURE = "LOGIN_CLIENT";
    const QString LOGIN_CLIENT_SIGNATURE_SUCCESS = "LOGIN_SUCCESS";


};

#endif // HTTPSERVER_H
