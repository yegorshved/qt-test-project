#include "server.h"

Server::Server(QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &Server::on_client_connecting);
    is_started = server->listen(QHostAddress::Any, port);


    if(!is_started){
        qDebug() << "Server could not start";
    } else{
        qDebug() << "Server started...";
    }

}

void Server::on_client_connecting()
{
    qDebug() << "client connected to server";
    auto socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &Server::client_data_ready);
    connect(socket, &QTcpSocket::disconnected, this, &Server::client_disconnected);
    sockets_list.append(socket);
    emit new_client_connected();
}

void Server::client_disconnected()
{
    emit disconnect_client();
}

void Server::client_data_ready()
{
    auto socket = qobject_cast<QTcpSocket *>(sender());
    auto data = QString(socket->readAll());
    emit data_received(data);
    foreach (auto s, sockets_list) {
        if (s != socket) {
            s->write(data.toUtf8());
        }
    }
}

bool Server::get_is_started() const
{
    return is_started;
}
