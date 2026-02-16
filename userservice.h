/**
 * @file userservice.h
 * @brief Implementação concreta do serviço de usuários.
 */
#ifndef USERSERVICE_H
#define USERSERVICE_H

#include "IUserService.h"
#include <QMap>

/**
 * @class UserService
 * @brief Classe que gerencia usuários em memória (Simulação de Banco de Dados).
 */
class UserService : public IUserService {
public:
    UserService();

    bool login(const QString& id, const QString& password) override;
    bool registerUser(const QString& username, const QString& password, const QString& name, const QString& email) override;
    bool isAdmin() override;
    void logout() override;
    /** @brief Implementação que retorna os dados do mapa baseados no usuário atual. */
    UserData getLoggedUserData() override {
        return m_db[m_currentUser];
    }

private:
    QMap<QString, UserData> m_db; /**< Mapa simulando a tabela de usuários */
    QString m_currentUser;        /**< ID do usuário logado na sessão atual */
    bool m_loggedAsAdmin;         /**< Flag de privilégios administrativos */
};

#endif
