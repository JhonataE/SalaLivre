/**
 * @file userservice.cpp
 * @brief Implementação dos serviços de gerenciamento de usuários e autenticação via SQLite.
 * @author Jhonata
 */

#include "userservice.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

/**
 * @brief Construtor da classe UserService.
 * @details Inicializa o serviço. Os dados agora residem no banco de dados persistente.
 */
UserService::UserService() : m_loggedAsAdmin(false) {
    // A inicialização de tabelas e usuários padrão deve ser feita no DatabaseManager
}

/**
 * @brief Realiza a autenticação do usuário no sistema consultando o banco de dados.
 * @param id Identificador/Matrícula do usuário.
 * @param password Senha fornecida.
 * @return true se as credenciais forem válidas, false caso contrário.
 */
bool UserService::login(const QString& id, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT role, nome_completo, email FROM usuarios WHERE username = :id AND senha = :pass");
    query.bindValue(":id", id);
    query.bindValue(":pass", password);

    if (query.exec() && query.next()) {
        m_currentUser = id;
        QString role = query.value(0).toString();
        m_loggedAsAdmin = (role == "Admin");

        // Preenchimento dos dados cacheados para uso na MainWindow
        m_loggedUserData.role = role;
        m_loggedUserData.name = query.value(1).toString();
        m_loggedUserData.email = query.value(2).toString();

        return true;
    }

    return false; // Chave de fechamento e retorno falso que estavam faltando
}

/**
 * @brief Registra um novo usuário com perfil externo no banco de dados.
 * @param username Identificador escolhido.
 * @param password Senha do novo usuário.
 * @param name Nome completo.
 * @param email Endereço de e-mail para contato/reserva.
 * @return true se o registro for bem-sucedido.
 */
bool UserService::registerUser(const QString& username, const QString& password, const QString& name, const QString& email) {
    if (username.isEmpty() || password.isEmpty()) {
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO usuarios (username, senha, role, nome_completo, email) "
                  "VALUES (:user, :pass, 'Externo', :name, :email)");
    query.bindValue(":user", username);
    query.bindValue(":pass", password);
    query.bindValue(":name", name);
    query.bindValue(":email", email);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Erro ao registrar usuário:" << query.lastError().text();
        return false;
    }
}

/**
 * @brief Verifica se o usuário logado possui privilégios de administrador.
 * @return true se o usuário for administrador.
 */
bool UserService::isAdmin() {
    return m_loggedAsAdmin;
}

/**
 * @brief Finaliza a sessão do usuário atual.
 */
void UserService::logout() {
    m_currentUser = "";
    m_loggedAsAdmin = false;
    m_loggedUserData = UserData(); // Limpa os dados cacheados
}
