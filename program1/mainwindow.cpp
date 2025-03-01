#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QString>
#include <QMessageBox>
#include <QScreen>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    set_window_center();

    connect(this->ui->button_start, &QPushButton::clicked, &udp, [this](){
        udp.send_start(this->N);
    });
    connect(this->ui->button_stop, &QPushButton::clicked, &udp, &Udp::send_stop);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::save_settings()
{

    QSettings settings("Yegor Shved inc.", "test project");
    settings.beginGroup("MainWindow");
    settings.setValue("position", this->geometry());
    settings.setValue("N", N);
    settings.setValue("value-n", this->ui->lineEdit->text());
    settings.endGroup();

}

void MainWindow::load_settings()
{
    QSettings settings("Yegor Shved inc.", "test project");
    settings.beginGroup("MainWindow");
    QRect rec = settings.value("position").toRect();
    setGeometry(rec);
    this->N = settings.value("N").toLongLong();
    this->ui->lineEdit->setText(settings.value("value-n").toString());
    settings.endGroup();
}

void MainWindow::set_window_center(){
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    // Получаем размеры окна
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;

    // Перемещаем окно в центр
    this->move(x, y);
}

void MainWindow::on_button_save_clicked()
{
    save_settings();
}

void MainWindow::on_button_load_clicked(){
    load_settings();
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString line = ui->lineEdit->text();
    this->N = line.toLongLong();
    if (N <= 0){
        QMessageBox::information(this, "Ошибка", "Неверное значение N.\nN должно быть больше нуля.");
        this->N = 0;
    }
}

void MainWindow::on_button_start_clicked(){}

void MainWindow::on_button_stop_clicked(){}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    //QString line = ui->lineEdit->text();
    QString line = arg1;
    this->N = line.toLongLong();
    if (N <= 0){
        QMessageBox::information(this, "Ошибка", "Неверное значение N.\nN должно быть больше нуля.");
        this->N = 0;
    }
}

