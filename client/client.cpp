#include "client.h"
#include "common/mavlink.h"
client::client(QObject *parent) : QObject(parent), _socket(new QTcpSocket)
{
    QString addr{"localhost"};
    int port = 6688;
    _socket->connectToHost(addr, port);
    connect(_socket, &QTcpSocket::readyRead, this, &client::readSlot);
}

void client::readSlot()
{
   QByteArray arr = _socket->readAll();
   uint8_t chan = MAVLINK_COMM_0;
   mavlink_heartbeat_t a{};
   mavlink_message_t msg{};
   mavlink_status_t status{};
   for(int i = 0; i < arr.size(); i++){
       char tmpchar = arr[i];
       if(mavlink_parse_char(chan, tmpchar, &msg, &status)){
           mavlink_msg_heartbeat_decode(&msg, &a);
           qDebug() <<"receive base_mode" << a.base_mode;
       }
   }
}
