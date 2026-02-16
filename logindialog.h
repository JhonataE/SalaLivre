#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "IUserService.h"

/**
 * @file logindialog.h
 * @brief Definição da interface de login e cadastro de usuários.
 */

namespace Ui { class LoginDialog; }

/**
 * @class LoginDialog
 * @brief Gerencia a interface de autenticação, suportando logins institucionais e externos.
 * @details Esta classe controla o fluxo de navegação entre as telas de login, cadastro e a validação de credenciais via IUserService.
 */
class LoginDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Construtor da classe LoginDialog.
     * @param service Ponteiro para a interface de serviço de usuário.
     * @param parent Ponteiro para o widget pai.
     */
    explicit LoginDialog(IUserService* service, QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    // --- Navegação ---
    /** @brief Altera a interface para o formulário de login de usuários externos. */
    void irParaLoginExterno();

    /** @brief Altera a interface para o formulário de novo cadastro. */
    void irParaCadastroExterno();

    /** @brief Retorna a interface para a tela de seleção inicial. */
    void voltarParaInicio();

    /** @brief Configura o estado para processar login de perfis Aluno/Docente/Admin. */
    void realizarLoginInstitucional();

    // --- Ações de formulário ---
    /** @brief Valida as credenciais inseridas e finaliza o diálogo com o código de sucesso correspondente. */
    void realizarLogin();

    /** @brief Processa a criação de uma nova conta de perfil externo. */
    void realizarCadastro();

private:
    Ui::LoginDialog *ui;
    IUserService* m_service;
    bool m_isInstitucional; ///< Define se o fluxo atual é para usuários da instituição ou externos.
};

#endif
