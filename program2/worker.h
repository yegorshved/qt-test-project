#ifndef WORKER_H
#define WORKER_H

#include <QMutexLocker>
#include <QWaitCondition>
#include <QMutex>
#include <atomic>

#include <QStack>
#include <QObject>
#include <QStringList>

#include <QTcpSocket>

class Worker : public QObject{
    Q_OBJECT
public:
    ~Worker();
    static void wakeAllThreads();
    static void set_number(int number);

private:
  void push();
  uint64_t pop();
  uint64_t generate_random_number();

public slots:
  void read_job();
  void write_job();
  void stop_jobs();
  void start_jobs();
  void handle_signal(QString signal); // получить сигнал по UDP

private slots:
  void sendLogs(); // отправить логи по TCP

signals:
  void jobs_done();

private:
  static QMutex mutex;
  static QWaitCondition waitcond;
  static QStack<uint64_t> stack;
  static std::atomic<bool> stop_jobs_flag;
  static std::atomic<int> number_of_operations;
  static QStringList log;
  static QTcpSocket tcpSocket;

};

#endif // WORKER_H
