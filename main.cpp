/**
 * @file main.cpp
 * @brief Ponto de entrada principal do sistema SalaLivre.
 * @author Jhonata
 * @date 2026-02-15
 * @details Gerencia o ciclo de vida da aplicação, controlando o fluxo entre a tela de login
 * e a abertura da janela principal conforme a autenticação do usuário.
 */

#include "mainwindow.h"
#include "logindialog.h"
#include "userservice.h"
#include <QApplication>
#include "adminmodel.h"

/**
 * @brief Função principal do sistema.
 * @details Inicializa o ambiente do Qt, gerencia a autenticação via LoginDialog e
 * decide se a MainWindow deve ser exibida com base no resultado do login.
 * @param argc Contador de argumentos de linha de comando.
 * @param argv Vetor de argumentos de linha de comando.
 * @return int Status de saída da aplicação.
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Inicialização do serviço de usuários e diálogo de login
    UserService userService;
    LoginDialog login(&userService);

    // Executa o diálogo de login de forma modal
    int result = login.exec();

    // Se o login for de um Admin (Código 2 definido no LoginDialog)
    if (login.exec() == QDialog::Accepted || result == 2) {
        MainWindow w(&userService); // A mesma janela para todos
        w.show();
        return a.exec();
    }
    // Se o login for bem-sucedido para Aluno/Docente/Externo (Código 1)
    else if (result == QDialog::Accepted) {
        MainWindow w(&userService);
        w.show();
        return a.exec();
    }

    return 0;
}
