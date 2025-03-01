/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *button_start;
    QPushButton *button_stop;
    QHBoxLayout *horizontalLayout;
    QPushButton *button_save;
    QPushButton *button_load;
    QLineEdit *lineEdit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(246, 177);
        MainWindow->setMinimumSize(QSize(246, 177));
        MainWindow->setMaximumSize(QSize(246, 177));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 20, 206, 116));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        button_start = new QPushButton(widget);
        button_start->setObjectName(QString::fromUtf8("button_start"));

        horizontalLayout_3->addWidget(button_start);

        button_stop = new QPushButton(widget);
        button_stop->setObjectName(QString::fromUtf8("button_stop"));

        horizontalLayout_3->addWidget(button_stop);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        button_save = new QPushButton(widget);
        button_save->setObjectName(QString::fromUtf8("button_save"));

        horizontalLayout->addWidget(button_save);

        button_load = new QPushButton(widget);
        button_load->setObjectName(QString::fromUtf8("button_load"));

        horizontalLayout->addWidget(button_load);


        verticalLayout->addLayout(horizontalLayout);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        button_start->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        button_stop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        button_save->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        button_load->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "Enter N", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
