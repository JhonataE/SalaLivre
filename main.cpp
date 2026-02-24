/**
 * @file main.cpp
 * @brief Ponto de entrada principal do sistema SalaLivre com integração SQL.
 */

#include "mainwindow.h"
#include "logindialog.h"
#include "userservice.h"
#include "databasemanager.h" // ADICIONADO
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // 1. INICIALIZAÇÃO DO BANCO DE DADOS (CRUCIAL)
    DatabaseManager dbManager;
    if (!dbManager.abrirConexao()) {
        QMessageBox::critical(nullptr, "Erro Crítico", "Não foi possível abrir o banco de dados.");
        return -1;
    }
    dbManager.criarTabelasIniciais(); // Cria tabelas e usuário admin

    // 2. INICIALIZAÇÃO DOS SERVIÇOS
    UserService userService;
    LoginDialog login(&userService);

    // 3. EXECUÇÃO DO LOGIN (Chamamos o exec() apenas UMA vez)
    int result = login.exec();

    // 4. CONTROLE DE FLUXO
    // Verificamos se o resultado foi Aceito (independente se é admin ou user comum)
    if (result == QDialog::Accepted || result == 2) {
        MainWindow w(&userService);
        w.show();
        return a.exec();
    }

    return 0;
}
