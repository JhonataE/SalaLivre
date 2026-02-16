/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *btnInstitucional;
    QPushButton *btnExterno;
    QLabel *label;
    QWidget *page_2;
    QLabel *label_3;
    QPushButton *btnEntrar;
    QPushButton *btnIrParaCadastro;
    QPushButton *pushButton_3;
    QLineEdit *txtUser;
    QLineEdit *txtSenha_2;
    QWidget *page_3;
    QLabel *label_4;
    QPushButton *btnConfirmarCadastro;
    QLabel *label_2;
    QLineEdit *txtNomeCad;
    QLineEdit *txtCPFCad_2;
    QLineEdit *txtEmailCad;
    QLineEdit *txtSenhaCad;
    QWidget *page_4;
    QLineEdit *txtMatriculaInst;
    QLineEdit *txtSenhaInst;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pushButton;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(400, 300);
        stackedWidget = new QStackedWidget(LoginDialog);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 401, 301));
        page = new QWidget();
        page->setObjectName("page");
        btnInstitucional = new QPushButton(page);
        btnInstitucional->setObjectName("btnInstitucional");
        btnInstitucional->setGeometry(QRect(80, 110, 231, 71));
        btnExterno = new QPushButton(page);
        btnExterno->setObjectName("btnExterno");
        btnExterno->setGeometry(QRect(80, 200, 231, 71));
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(150, 10, 101, 81));
        label->setPixmap(QPixmap(QString::fromUtf8("logoSL.png")));
        label->setScaledContents(true);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        label_3 = new QLabel(page_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(150, 10, 101, 81));
        label_3->setPixmap(QPixmap(QString::fromUtf8("logoSL.png")));
        label_3->setScaledContents(true);
        btnEntrar = new QPushButton(page_2);
        btnEntrar->setObjectName("btnEntrar");
        btnEntrar->setGeometry(QRect(130, 230, 141, 31));
        btnIrParaCadastro = new QPushButton(page_2);
        btnIrParaCadastro->setObjectName("btnIrParaCadastro");
        btnIrParaCadastro->setGeometry(QRect(300, 270, 71, 21));
        pushButton_3 = new QPushButton(page_2);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(20, 270, 111, 21));
        txtUser = new QLineEdit(page_2);
        txtUser->setObjectName("txtUser");
        txtUser->setGeometry(QRect(130, 130, 141, 31));
        txtSenha_2 = new QLineEdit(page_2);
        txtSenha_2->setObjectName("txtSenha_2");
        txtSenha_2->setGeometry(QRect(130, 180, 141, 31));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        label_4 = new QLabel(page_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(150, 10, 101, 81));
        label_4->setPixmap(QPixmap(QString::fromUtf8("logoSL.png")));
        label_4->setScaledContents(true);
        btnConfirmarCadastro = new QPushButton(page_3);
        btnConfirmarCadastro->setObjectName("btnConfirmarCadastro");
        btnConfirmarCadastro->setGeometry(QRect(80, 250, 231, 41));
        label_2 = new QLabel(page_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(150, 90, 111, 20));
        txtNomeCad = new QLineEdit(page_3);
        txtNomeCad->setObjectName("txtNomeCad");
        txtNomeCad->setGeometry(QRect(80, 120, 231, 22));
        txtCPFCad_2 = new QLineEdit(page_3);
        txtCPFCad_2->setObjectName("txtCPFCad_2");
        txtCPFCad_2->setGeometry(QRect(80, 150, 231, 22));
        txtEmailCad = new QLineEdit(page_3);
        txtEmailCad->setObjectName("txtEmailCad");
        txtEmailCad->setGeometry(QRect(80, 180, 231, 22));
        txtSenhaCad = new QLineEdit(page_3);
        txtSenhaCad->setObjectName("txtSenhaCad");
        txtSenhaCad->setGeometry(QRect(80, 210, 231, 22));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        txtMatriculaInst = new QLineEdit(page_4);
        txtMatriculaInst->setObjectName("txtMatriculaInst");
        txtMatriculaInst->setGeometry(QRect(130, 130, 141, 31));
        txtSenhaInst = new QLineEdit(page_4);
        txtSenhaInst->setObjectName("txtSenhaInst");
        txtSenhaInst->setGeometry(QRect(130, 180, 141, 31));
        label_5 = new QLabel(page_4);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(150, 10, 101, 81));
        label_5->setPixmap(QPixmap(QString::fromUtf8("logoSL.png")));
        label_5->setScaledContents(true);
        label_6 = new QLabel(page_4);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(150, 90, 111, 31));
        label_7 = new QLabel(page_4);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(150, 260, 111, 16));
        pushButton = new QPushButton(page_4);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(130, 220, 141, 31));
        stackedWidget->addWidget(page_4);

        retranslateUi(LoginDialog);

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        btnInstitucional->setText(QCoreApplication::translate("LoginDialog", "Entrar com credenciais institucionais", nullptr));
        btnExterno->setText(QCoreApplication::translate("LoginDialog", "Acesso Externo", nullptr));
        label->setText(QString());
        label_3->setText(QString());
        btnEntrar->setText(QCoreApplication::translate("LoginDialog", "Entrar", nullptr));
        btnIrParaCadastro->setText(QCoreApplication::translate("LoginDialog", "Cadastrar", nullptr));
        pushButton_3->setText(QCoreApplication::translate("LoginDialog", "Esqueceu a senha?", nullptr));
        txtUser->setText(QCoreApplication::translate("LoginDialog", "Usu\303\241rio", nullptr));
        txtSenha_2->setText(QCoreApplication::translate("LoginDialog", "Senha", nullptr));
        label_4->setText(QString());
        btnConfirmarCadastro->setText(QCoreApplication::translate("LoginDialog", "Cadastrar", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "Cadastro de usu\303\241rio", nullptr));
        txtNomeCad->setText(QCoreApplication::translate("LoginDialog", "Nome Completo", nullptr));
        txtCPFCad_2->setText(QCoreApplication::translate("LoginDialog", "CPF", nullptr));
        txtEmailCad->setText(QCoreApplication::translate("LoginDialog", "Email", nullptr));
        txtSenhaCad->setText(QCoreApplication::translate("LoginDialog", "Senha", nullptr));
        txtMatriculaInst->setText(QCoreApplication::translate("LoginDialog", "Matr\303\255cula/SIAPE", nullptr));
        txtSenhaInst->setText(QCoreApplication::translate("LoginDialog", "Senha", nullptr));
        label_5->setText(QString());
        label_6->setText(QCoreApplication::translate("LoginDialog", "Login Institucional", nullptr));
        label_7->setText(QCoreApplication::translate("LoginDialog", "Esqueceu sua senha?", nullptr));
        pushButton->setText(QCoreApplication::translate("LoginDialog", "Entrar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
