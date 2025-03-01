#ifndef UDPCONNECTION_H
#define UDPCONNECTION_H

#include <QObject>
#include <QUdpSocket>

class Udp : public QObject
{
    Q_OBJECT
public:
    explicit Udp(QObject *parent = nullptr);
public slots:
    void send_start(qint64);
    void send_stop();

private:
    QUdpSocket *socket = nullptr;
    const quint16 port = 12345;
};

#endif // UDPCONNECTION_H
