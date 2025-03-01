#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "worker.h"
#include "udp.h"
#include <QThread>
#include <QObject>

class Controller : public QObject
{
    Q_OBJECT
private:
    Worker* producer = nullptr;
    Worker* consumer = nullptr;
    QThread* producer_thread = nullptr;
    QThread* consumer_thread = nullptr;
    Udp udp;

public:
    Controller();
    ~Controller();
public slots:
    void start_jobs();
    void stop_jobs();
    void handle_message(QString message);
};

#endif // CONTROLLER_H
