#include "controller.h"
#include <QDebug>

Controller::Controller(){
    connect(&udp, &Udp::message_received, this, &Controller::handle_message);
    udp.receive_message();

}

Controller::~Controller() {
    qDebug() << "[Destructor] Controller called";
    if (producer_thread) {
        qDebug() << "[Destructor] Stopping producer thread";
        producer_thread->quit();
        producer_thread->wait();
        delete producer_thread;
        qDebug() << "[Destructor] Producer thread deleted";
    }
    if (consumer_thread) {
        qDebug() << "[Destructor] Stopping consumer thread";
        consumer_thread->quit();
        consumer_thread->wait();
        delete consumer_thread;
        qDebug() << "[Destructor] Consumer thread deleted";
    }
    if (consumer){
        qDebug() << "[Destructor] Deleting consumer";
        delete consumer;
    }
    if (producer){
        qDebug() << "[Destructor] Deleting producer";
        delete producer;
    }
    qDebug() << "[Destructor] Controller destruction completed";
}

void Controller::start_jobs() {
    qDebug() << "[start_jobs] Checking if threads already exist";
    if (producer_thread && consumer_thread) {
        qDebug() << "[start_jobs] Threads already exist, returning";
        return;
    }
    qDebug() << "[start_jobs] Creating Workers and Threads";
    producer = new Worker();
    consumer = new Worker();
    producer_thread = new QThread();
    consumer_thread = new QThread();
    connect(consumer, &Worker::jobs_done, this, &Controller::stop_jobs);
    connect(producer, &Worker::jobs_done, this, &Controller::stop_jobs);
    qDebug() << "[start_jobs] Moving Workers to Threads";
    producer->moveToThread(producer_thread);
    consumer->moveToThread(consumer_thread);

    qDebug() << "[start_jobs] Connecting signals";
    QObject::connect(producer_thread, &QThread::started, producer, &Worker::write_job);
    QObject::connect(consumer_thread, &QThread::started, consumer, &Worker::read_job);

    qDebug() << "[start_jobs] Starting jobs";
    producer->start_jobs();
    consumer->start_jobs();

    qDebug() << "[start_jobs] Starting threads";
    producer_thread->start();
    consumer_thread->start();
    qDebug() << "[start_jobs] All jobs started successfully";
}

void Controller::stop_jobs() {
    qDebug() << "[stop_jobs] Stopping jobs";
    if (!producer_thread || !consumer_thread || !producer || !consumer) {
        qDebug() << "[stop_jobs] One or more components are null, returning";
        return;
    }
    qDebug() << "[stop_jobs] Calling wakeAllThreads() on workers";

    Worker::wakeAllThreads();
    qDebug() << "[stop_jobs] Calling stop_jobs on workers";
    producer->stop_jobs();
    consumer->stop_jobs();

    qDebug() << "[stop_jobs] Stopping threads";
    producer_thread->quit();
    consumer_thread->quit();
    producer_thread->wait();
    consumer_thread->wait();

    qDebug() << "[stop_jobs] Deleting Workers";
    if (producer) {
        delete producer;
        qDebug() << "[stop_jobs] Producer deleted";
    }
    if (consumer) {
        delete consumer;
        qDebug() << "[stop_jobs] Consumer deleted";
    }
    producer = nullptr;
    consumer = nullptr;

    qDebug() << "[stop_jobs] Deleting Threads";
    if (producer_thread) {
        delete producer_thread;
        qDebug() << "[stop_jobs] Producer thread deleted";
    }
    if (consumer_thread) {
        delete consumer_thread;
        qDebug() << "[stop_jobs] Consumer thread deleted";
    }
    producer_thread = nullptr;
    consumer_thread = nullptr;
    qDebug() << "[stop_jobs] Jobs stopped successfully";
}

void Controller::handle_message(QString message) {
    qDebug() << "Received message:" << message;
    if (message.contains("stop")) {
        stop_jobs(); // Останавливаем потоки и удаляем Worker
    } else if (message.startsWith("start ")) {
        bool ok;
        int num = message.split(" ").last().toInt(&ok); // Извлекаем число из "start N"
        if (ok) {
            Worker::set_number(num); // Устанавливаем количество операций
            if (producer && consumer) {
                // Если Worker уже существуют, просто сбрасываем флаг
                producer->start_jobs();
                consumer->start_jobs();
            } else {
                // Если Worker еще не созданы, запускаем потоки
                start_jobs();
            }
        } else {
            qDebug() << "Invalid number in message:" << message;
        }
    } else {
        qDebug() << "Unknown command:" << message;
    }
}
