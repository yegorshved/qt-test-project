#ifndef UDP_H
#define UDP_H

#include <QObject>
#include <QUdpSocket>
#include <QString>

class Udp : public QObject
{
    Q_OBJECT
private:

public:
    explicit Udp(QObject *parent = nullptr);

public slots:
    void receive_message();
    static QString get_message();
signals:
    void message_received(const QString&);

private:
    QUdpSocket* socket = nullptr;
    const quint16 port = 12345;
    static QString message;
};

#endif // UDP_H
