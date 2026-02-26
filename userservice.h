/**
 * @file userservice.h
 * @brief Implementação concreta do serviço de usuários via Banco de Dados.
 */
#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "IUserService.h"

/**
 * @class UserService
 * @brief Classe que gerencia usuários através de consultas SQL ao banco de dados.
 */
class UserService : public IUserService {
public:
    UserService();

    bool login(const QString& id, const QString& password) override;
    bool registerUser(const QString& username, const QString& password, const QString& name, const QString& email) override;
    bool isAdmin() override;
    void logout() override;

    /** @brief Retorna os dados do usuário carregados durante o login. */
    UserData getLoggedUserData() override {
        return m_loggedUserData;
    }

private:
    UserData m_loggedUserData;    /**< Estrutura contendo os dados do usuário da sessão atual */
    QString m_currentUser;        /**< ID do usuário logado na sessão atual */
    bool m_loggedAsAdmin;         /**< Flag de privilégios administrativos */
};

#endif
