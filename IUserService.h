/**
 * @file IUserService.h
 * @brief Interface para os serviços de usuário (SB01).
 * @details Define o contrato para autenticação e gestão de perfis institucionais e externos.
 */

#ifndef IUSERSERVICE_H
#define IUSERSERVICE_H

#include <QString>

/**
 * @struct UserData
 * @brief Estrutura que armazena os dados básicos do usuário logado.
 */
struct UserData {
    QString password;
    QString role;
    QString name;
    QString email;
};

/**
 * @class IUserService
 * @brief Interface abstrata que define as operações de usuário.
 * * Segue o princípio de inversão de dependência (SOLID) para que a UI
 * não dependa de implementações específicas de banco de dados.
 */
class IUserService {
public:
    /** @brief Destrutor virtual para garantir a limpeza correta das classes derivadas. */
    virtual ~IUserService() {}

    /**
     * @brief Realiza o login no sistema.
     * @param id Matrícula, SIAPE ou CPF do usuário.
     * @param password Senha de acesso.
     * @return true se as credenciais forem válidas.
     */
    virtual bool login(const QString& id, const QString& password) = 0;

    /**
     * @brief Registra um novo usuário externo no sistema.
     * @details Requisito SB01 item 3c.
     * @param username Nome ou ID do usuário.
     * @param password Senha escolhida.
     * @return true se o cadastro for realizado com sucesso.
     */
    virtual bool registerUser(const QString& username, const QString& password, const QString& name, const QString& email) = 0;

    /**
     * @brief Verifica se o usuário logado possui privilégios de administrador.
     * @return true se for Administrador.
     */
    virtual bool isAdmin() = 0;

    /**
     * @brief Finaliza a sessão atual.
     */
    virtual void logout() = 0;

    /**
     * @brief Recupera os dados do usuário autenticado no momento.
     * @return Objeto UserData contendo nome, perfil e senha.
     */
    virtual UserData getLoggedUserData() = 0;
};

#endif // IUSERSERVICE_H
