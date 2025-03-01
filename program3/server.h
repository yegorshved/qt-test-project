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
    bool get_is_started() const;
signals:
    void new_client_connected();
    void disconnect_client();
    void data_received(QString message);

private slots:
    void on_client_connecting();

    void client_disconnected();

    void client_data_ready();


private:
    QTcpServer *server;
    QList<QTcpSocket *> sockets_list;
    bool is_started;
    quint16 port = 12345;
};

#endif // MYTCPSERVER_H
