#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:

public slots:
    void onNewConnection();
private:
    QTcpServer *_server;
    QTcpSocket *_socket;

};

#endif // SERVER_H
