/********************************************************************************
** Form generated from reading UI file 'adminmodel.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINMODEL_H
#define UI_ADMINMODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Adminmodel
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *btnNovaUnidade;
    QPushButton *btnGerenciarUnidade;
    QPushButton *btnRemoverUnidade;
    QPushButton *btnRegrasUnidade;
    QLabel *label_2;
    QLabel *label_6;
    QWidget *tab_2;
    QComboBox *comboUnidades;
    QLabel *label_5;
    QLabel *label;
    QComboBox *comboSalasEdicao;
    QSpinBox *spinCapacidade;
    QLineEdit *txtRecursos;
    QPushButton *btnNovaSala;
    QPushButton *btnSalvarAtributosSala;

    void setupUi(QDialog *Adminmodel)
    {
        if (Adminmodel->objectName().isEmpty())
            Adminmodel->setObjectName("Adminmodel");
        Adminmodel->resize(590, 341);
        tabWidget = new QTabWidget(Adminmodel);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 10, 591, 341));
        tab = new QWidget();
        tab->setObjectName("tab");
        btnNovaUnidade = new QPushButton(tab);
        btnNovaUnidade->setObjectName("btnNovaUnidade");
        btnNovaUnidade->setGeometry(QRect(220, 140, 151, 24));
        btnGerenciarUnidade = new QPushButton(tab);
        btnGerenciarUnidade->setObjectName("btnGerenciarUnidade");
        btnGerenciarUnidade->setGeometry(QRect(220, 180, 151, 24));
        btnRemoverUnidade = new QPushButton(tab);
        btnRemoverUnidade->setObjectName("btnRemoverUnidade");
        btnRemoverUnidade->setGeometry(QRect(220, 220, 151, 24));
        btnRegrasUnidade = new QPushButton(tab);
        btnRegrasUnidade->setObjectName("btnRegrasUnidade");
        btnRegrasUnidade->setGeometry(QRect(220, 260, 151, 24));
        label_2 = new QLabel(tab);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(240, 90, 131, 20));
        label_6 = new QLabel(tab);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(240, 10, 101, 81));
        label_6->setPixmap(QPixmap(QString::fromUtf8("logoSL.png")));
        label_6->setScaledContents(true);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        comboUnidades = new QComboBox(tab_2);
        comboUnidades->addItem(QString());
        comboUnidades->setObjectName("comboUnidades");
        comboUnidades->setGeometry(QRect(190, 130, 191, 21));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(240, 10, 101, 81));
        label_5->setPixmap(QPixmap(QString::fromUtf8("logoSL.png")));
        label_5->setScaledContents(true);
        label = new QLabel(tab_2);
        label->setObjectName("label");
        label->setGeometry(QRect(240, 90, 131, 16));
        comboSalasEdicao = new QComboBox(tab_2);
        comboSalasEdicao->addItem(QString());
        comboSalasEdicao->setObjectName("comboSalasEdicao");
        comboSalasEdicao->setGeometry(QRect(190, 170, 191, 21));
        spinCapacidade = new QSpinBox(tab_2);
        spinCapacidade->setObjectName("spinCapacidade");
        spinCapacidade->setGeometry(QRect(190, 210, 191, 22));
        txtRecursos = new QLineEdit(tab_2);
        txtRecursos->setObjectName("txtRecursos");
        txtRecursos->setGeometry(QRect(190, 240, 191, 22));
        btnNovaSala = new QPushButton(tab_2);
        btnNovaSala->setObjectName("btnNovaSala");
        btnNovaSala->setGeometry(QRect(190, 270, 75, 24));
        btnSalvarAtributosSala = new QPushButton(tab_2);
        btnSalvarAtributosSala->setObjectName("btnSalvarAtributosSala");
        btnSalvarAtributosSala->setGeometry(QRect(284, 270, 101, 24));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(Adminmodel);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Adminmodel);
    } // setupUi

    void retranslateUi(QDialog *Adminmodel)
    {
        Adminmodel->setWindowTitle(QCoreApplication::translate("Adminmodel", "Dialog", nullptr));
        btnNovaUnidade->setText(QCoreApplication::translate("Adminmodel", "Cadastrar Unidade", nullptr));
        btnGerenciarUnidade->setText(QCoreApplication::translate("Adminmodel", "Gerenciar Unidade", nullptr));
        btnRemoverUnidade->setText(QCoreApplication::translate("Adminmodel", "Remover Unidade", nullptr));
        btnRegrasUnidade->setText(QCoreApplication::translate("Adminmodel", "Regras da Unidade", nullptr));
        label_2->setText(QCoreApplication::translate("Adminmodel", "ADMIN - Unidades", nullptr));
        label_6->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Adminmodel", "Tab 1", nullptr));
        comboUnidades->setItemText(0, QCoreApplication::translate("Adminmodel", "Selecionar unidade", nullptr));

        label_5->setText(QString());
        label->setText(QCoreApplication::translate("Adminmodel", "ADMIN - Salas", nullptr));
        comboSalasEdicao->setItemText(0, QCoreApplication::translate("Adminmodel", "Sala ", nullptr));

        btnNovaSala->setText(QCoreApplication::translate("Adminmodel", "Nova Sala", nullptr));
        btnSalvarAtributosSala->setText(QCoreApplication::translate("Adminmodel", "Salvar atributos", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Adminmodel", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Adminmodel: public Ui_Adminmodel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINMODEL_H
