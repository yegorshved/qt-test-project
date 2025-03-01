#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>

#include <QStack>
#include <QString>

#include <QThread>
#include <QReadWriteLock>

#include "controller.h"


int main(int argc, char* argv[]){
  QApplication app(argc, argv);

  QWidget widget;
  QVBoxLayout layout(&widget);
  QPushButton start("Start", &widget);
  QPushButton stop("Stop", &widget);

  start.setStyleSheet(
      "QPushButton {"
      "    background-color: white;"
      "    color: black;"
      "    border-radius: 15px;"
      "    padding: 10px 20px;"
      "    border: none;"  // Убирает рамку вокруг кнопки
      "}"
      "QPushButton:hover {"
      "    background-color: green;"  // Цвет фона при наведении
      "    color: black;"  // Цвет текста при наведении
      "}"
      "QPushButton:focus {"
      "    outline: none;"  // Убирает фокусное выделение
      "}"
      "QPushButton:pressed {"
      "    background-color: lightcoral;"  // Цвет фона при нажатии
      "    color: black;"  // Цвет текста при нажатии
      "}"
  );

  stop.setStyleSheet(
      "QPushButton {"
      "    background-color: white;"
      "    color: black;"
      "    border-radius: 15px;"
      "    padding: 10px 20px;"
      "    border: none;"  // Убирает рамку вокруг кнопки
      "}"
      "QPushButton:hover {"
      "    background-color: green;"  // Цвет фона при наведении
      "    color: black;"  // Цвет текста при наведении
      "}"
      "QPushButton:focus {"
      "    outline: none;"  // Убирает фокусное выделение
      "}"
      "QPushButton:pressed {"
      "    background-color: lightcoral;"  // Цвет фона при нажатии
      "    color: black;"  // Цвет текста при нажатии
      "}"
  );

  Controller controller;

  //Подключаем кнопки к слотам
  QObject::connect(&start, &QPushButton::clicked, &controller, &Controller::start_jobs);
  QObject::connect(&stop, &QPushButton::clicked, &controller, &Controller::stop_jobs);

  layout.setAlignment(Qt::AlignCenter);
  layout.addWidget(&start);
  layout.addWidget(&stop);
  widget.setMinimumSize(500, 500);
  widget.setWindowTitle("Program 2");
  //widget.show();


  return app.exec();
}
