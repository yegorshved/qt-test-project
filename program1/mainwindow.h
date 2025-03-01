#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "udpconnection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void save_settings();
    void load_settings();
private:
    void set_window_center();

private slots:
    void on_button_save_clicked();

    void on_button_load_clicked();

    void on_button_start_clicked();

    void on_button_stop_clicked();

    void on_lineEdit_returnPressed();

    void on_lineEdit_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
    qint64 N = 0;
    Udp udp;
};
#endif // MAINWINDOW_H
