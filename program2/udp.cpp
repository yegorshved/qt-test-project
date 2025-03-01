#include "udp.h"
#include <QNetworkDatagram>

QString Udp::message;

Udp::Udp(QObject *parent)
    : QObject{parent}
{
    socket = new QUdpSocket();
    socket->bind(QHostAddress::LocalHost, this->port);
    connect(socket, &QUdpSocket::readyRead, this, &Udp::receive_message);
}

QString Udp::get_message(){
    return message;
}

void Udp::receive_message(){
    while(socket->hasPendingDatagrams()){
        QNetworkDatagram datagram = socket->receiveDatagram();
        qDebug() << "Received message: " << QString::fromUtf8(datagram.data());
        message = QString::fromUtf8(datagram.data());
        emit message_received(message);
    }
}
