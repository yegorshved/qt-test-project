#include "worker.h"

#include <QDebug>
#include <QThread>
#include <QDateTime>

#include <random>
#include <chrono>

// Инициализация статических переменных

// инициализация переменных для работы с потоками
QWaitCondition Worker::waitcond;
QMutex Worker::mutex;

std::atomic<bool> Worker::stop_jobs_flag{false};
std::atomic<int> Worker::number_of_operations{0};

QStack<uint64_t> Worker::stack;
QStringList Worker::log;
QTcpSocket Worker::tcpSocket;

/* Деструктор для Worker
 * Обеспечивает правильное закрытие соединения.
 */
Worker::~Worker() {
    if (tcpSocket.isOpen()) {
        tcpSocket.close();
    }
    qDebug() << "Worker destructor. Socket closed.";
}

/* Функция для пробуждения всех потоков
 * Необходима для правильного их уничтожения
 */
void Worker::wakeAllThreads(){
    waitcond.wakeAll();
}

/* Геттер для number_of_operations переменной,
 * которяа отвечает за количество операций.
 */
void Worker::set_number(int number)
{
    number_of_operations = number;
}

/*  Слот для чтения из стека
 */
void Worker::read_job(){
    while (!stop_jobs_flag && number_of_operations > 0){
        pop();
        sendLogs();
        number_of_operations--;
    }
}

/* Слот для записи в стек
 */
void Worker::write_job(){
    while(!stop_jobs_flag && number_of_operations > 0){
        push();
        sendLogs();
        number_of_operations--;
    }
}


/* Слота для старта и остановки работ
 */
void Worker::stop_jobs(){
    stop_jobs_flag = true;
    wakeAllThreads();
}
void Worker::start_jobs(){
    stop_jobs_flag = false;
}

/* Слот для обработки UDP датаграммы (старт и стоп работ)
 */
void Worker::handle_signal(QString signal)
{
    if (signal.contains("stop")){
        stop_jobs();
    }
    else{
        QStringList parts = signal.split(' ');
        int num = parts.last().toInt();
        number_of_operations = num;
        start_jobs();
    }
}

/* Слот для записи в стек + большое количество логов
 *
 */
void Worker::push() {
    QMutexLocker locker(&mutex);

    QString begin_time = QDateTime::currentDateTime().toString("hh:mm:ss.zzzzzz");
    qint64 thread_id = reinterpret_cast<qint64>(QThread::currentThreadId());
    log.append(QString("[THREAD %1] [BEGIN] Push operation started at %2").arg(thread_id).arg(begin_time));

    QThread::currentThread()->msleep(500);

    log.append(QString("[THREAD %1] [LOCK] Acquiring write lock").arg(thread_id));

    uint64_t random_number = generate_random_number();

    log.append(QString("[THREAD %1] [WRITE] Generated number: %2").arg(thread_id).arg(random_number));

    stack.push(random_number);

    log.append(QString("[THREAD %1] [PUSH] Number pushed onto stack").arg(thread_id));

    waitcond.wakeOne();

    log.append(QString("[THREAD %1] [SIGNAL] Condition variable signaled").arg(thread_id));

    QString end_time = QDateTime::currentDateTime().toString("hh:mm:ss.zzzzzz");
    log.append(QString("[THREAD %1] [END] Push operation finished at %2").arg(thread_id).arg(end_time));
    //qDebug() << log;
    qDebug() << "push: " << random_number;
}

/* Слот для чтения из стека + большое количество логов
 *
 */
uint64_t Worker::pop() {
    QMutexLocker locker(&mutex);

    QString begin_time = QDateTime::currentDateTime().toString("hh:mm:ss.zzzzzz");
    qint64 thread_id = reinterpret_cast<qint64>(QThread::currentThreadId());

    log.append(QString("[THREAD %1] [BEGIN] Pop operation started at %2").arg(thread_id).arg(begin_time));

    QThread::currentThread()->msleep(500);

    log.append(QString("[THREAD %1] [LOCK] Acquiring write lock").arg(thread_id));


    while (stack.isEmpty() && !stop_jobs_flag) {
        log.append(QString("[THREAD %1] [WAIT] Stack is empty, waiting").arg(thread_id));
        waitcond.wait(&mutex);
    }

    if (stop_jobs_flag){
        log.append(QString("[THREAD %1] [ERROR] Stack is still empty after wakeup").arg(thread_id));
        return 0;
    }

    uint64_t popped = stack.pop();
    log.append(QString("[THREAD %1] [POP] Popped number: %2").arg(thread_id).arg(popped));

    QString end_time = QDateTime::currentDateTime().toString("hh:mm:ss.zzzzzz");
    log.append(QString("[THREAD %1] [END] Pop operation finished at %2").arg(thread_id).arg(end_time));
    //qDebug() << log;
    qDebug() << "popped: " << popped;
    return popped;
}

/* Слот для генерации псевдо-случайного значения
 */
uint64_t Worker::generate_random_number()
{
    // Используем текущее время в качестве начального значения для генератора
    std::mt19937_64 mt{static_cast<uint64_t>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};

    uint64_t lower = 0, higher = 100000;
    std::uniform_int_distribution<uint64_t> distribution(lower, higher);
    return distribution(mt);
}


/* Слот для отправки логов по TCP протоколу
 *
 */
void Worker::sendLogs() {
    QMutexLocker locker(&mutex);
    if (log.isEmpty()) {
        qDebug() << "Log is empty, nothing to send";
        return;
    }

    QString message = log.join("\n");
    log.clear();  // Очистка логов после отправки
    qDebug() << "Logs prepared for sending:" << message;

    // Подключение к серверу (если не подключен)
    if (tcpSocket.state() != QAbstractSocket::ConnectedState) {
        qDebug() << "Socket is not connected, trying to connect to server...";
        tcpSocket.connectToHost("127.0.0.1", 12345);
        
        if (!tcpSocket.waitForConnected(500)) {
            qDebug() << "Failed to connect to server";
            return;
        } else {
            qDebug() << "Successfully connected to server";
        }
    } else {
        qDebug() << "Already connected to server, ready to send logs";
    }

    // Отправка логов
    qint64 bytesWritten = tcpSocket.write(message.toUtf8());
    if (bytesWritten == -1) {
        qDebug() << "Failed to write data to socket";
    } else {
        qDebug() << "Sent" << bytesWritten << "bytes to server";
    }
    
    tcpSocket.flush();
    log.clear();
    qDebug() << "Logs sent to server and socket flushed";
}
