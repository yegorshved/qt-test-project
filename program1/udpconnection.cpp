#include "udpconnection.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>


Udp::Udp(QObject *parent): QObject(parent)
{
    socket = new QUdpSocket();
    socket->bind(QHostAddress::LocalHost, this->port);

}

void Udp::send_start(qint64 N){
    if (N<= 0){
        qDebug() << "Invalid number.";
        QMessageBox::information(nullptr, "Ошибка", "Неверное значение N.\nN должно быть больше нуля.");
        return;
    }
    qDebug() << "N: " << N;
    QByteArray start_signal = QString("start %1").arg(N).toUtf8();

    socket->writeDatagram(start_signal, QHostAddress::LocalHost, this->port);
    qDebug() << "start_signal: " << start_signal;
}

void Udp::send_stop(){
    QByteArray stop_signal = "stop";
    socket->writeDatagram(stop_signal, QHostAddress::LocalHost, this->port);
}
