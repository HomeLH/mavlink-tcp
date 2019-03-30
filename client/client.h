#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class client : public QObject
{
    Q_OBJECT
public:
    explicit client(QObject *parent = nullptr);

signals:

public slots:
    void readSlot();
private:
    QTcpSocket *_socket;
};

#endif // CLIENT_H
