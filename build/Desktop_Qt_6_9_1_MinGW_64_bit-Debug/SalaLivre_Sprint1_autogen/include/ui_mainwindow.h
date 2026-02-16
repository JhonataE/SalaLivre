/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QPushButton *btnBuscar;
    QLabel *lblStatus;
    QTableWidget *gridAgenda;
    QListWidget *listSalas;
    QPushButton *btnAgendar;
    QPushButton *btnAreaAdm;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(855, 434);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        btnBuscar = new QPushButton(widget);
        btnBuscar->setObjectName("btnBuscar");
        btnBuscar->setGeometry(QRect(380, 20, 231, 24));
        lblStatus = new QLabel(widget);
        lblStatus->setObjectName("lblStatus");
        lblStatus->setGeometry(QRect(30, 50, 341, 20));
        gridAgenda = new QTableWidget(widget);
        if (gridAgenda->columnCount() < 2)
            gridAgenda->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        gridAgenda->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        gridAgenda->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        gridAgenda->setObjectName("gridAgenda");
        gridAgenda->setGeometry(QRect(120, 130, 341, 192));
        listSalas = new QListWidget(widget);
        listSalas->setObjectName("listSalas");
        listSalas->setGeometry(QRect(500, 130, 256, 192));
        btnAgendar = new QPushButton(widget);
        btnAgendar->setObjectName("btnAgendar");
        btnAgendar->setGeometry(QRect(680, 290, 75, 24));
        btnAreaAdm = new QPushButton(widget);
        btnAreaAdm->setObjectName("btnAreaAdm");
        btnAreaAdm->setGeometry(QRect(720, 20, 75, 24));

        verticalLayout->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 855, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnBuscar->setText(QCoreApplication::translate("MainWindow", "Buscar", nullptr));
        lblStatus->setText(QCoreApplication::translate("MainWindow", "lblStatus", nullptr));
        QTableWidgetItem *___qtablewidgetitem = gridAgenda->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Hor\303\241rio", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = gridAgenda->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        btnAgendar->setText(QCoreApplication::translate("MainWindow", "Agendar", nullptr));
        btnAreaAdm->setText(QCoreApplication::translate("MainWindow", "\303\201rea adm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
