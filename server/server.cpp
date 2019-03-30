#include "server.h"
#include <unistd.h>
#include <QDataStream>
#include "common/mavlink.h"
Server::Server(QObject *parent) : QObject(parent),
    _server(new QTcpServer)
{
    int port{6688};
    if(_server->listen(QHostAddress::Any, port)){
        qDebug() << "Server is listenning on " << port;
    } else {
        qDebug() << "Listen error!";
    }
    connect(_server, &QTcpServer::newConnection, this, &Server::onNewConnection);
}

void Server::onNewConnection()
{
    qDebug() << "On new Connection!";
    qint32 i{0};
    _socket = _server->nextPendingConnection();



    while(true){
        mavlink_heartbeat_t a{};
        a.base_mode =i++;
        mavlink_message_t msg;
        mavlink_msg_heartbeat_encode(1, 200, &msg, &a);
        uint8_t buf[1000]{0};
        int len = mavlink_msg_to_send_buffer(buf, &msg);
        qDebug() << "send base_mode " << a.base_mode;
        _socket->write((char*)buf, len);
        _socket->waitForBytesWritten();
        sleep(1);
    }
}
