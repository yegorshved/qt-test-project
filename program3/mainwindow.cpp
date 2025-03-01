#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new Server();
    connect(server, &Server::new_client_connected, this, &MainWindow::client_connected);
    connect(server, &Server::data_received, this, &MainWindow::log_received);
    connect(server, &Server::disconnect_client, this, &MainWindow::client_disconnected);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::client_connected()
{
    ui->lstConsole->addItem("New Client connected");
}

void MainWindow::client_disconnected()
{
    ui->lstConsole->addItem("Client Disconnected");
}

void MainWindow::log_received(QString message)
{
    ui->lstConsole->addItem(message);
}
