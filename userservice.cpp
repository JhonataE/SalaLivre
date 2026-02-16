/**
 * @file userservice.cpp
 * @brief Implementação dos serviços de gerenciamento de usuários e autenticação.
 * @author Jhonata
 */

#include "userservice.h"

/**
 * @brief Construtor da classe UserService.
 * * Inicializa o banco de dados em memória com usuários pré-definidos para testes,
 * incluindo perfis de Aluno, Admin e Externo.
 */
UserService::UserService() : m_loggedAsAdmin(false) {
    // Populando o sistema com dados iniciais (Inclusão de E-mail para a reserva)
    m_db["12345"] = {"senha123", "Aluno", "Jhonata Aluno", "jhonata.aluno@aluno.ufop.edu.br"};
    m_db["admin"] = {"admin123", "Admin", "Administrador", "admin@ufop.edu.br"};
    m_db["000.000.000-00"] = {"ext123", "Externo", "Visitante", "visitante@gmail.com"};
}

/**
 * @brief Realiza a autenticação do usuário no sistema.
 * @param id Identificador/Matrícula do usuário.
 * @param password Senha fornecida.
 * @return true se as credenciais forem válidas, false caso contrário.
 */
bool UserService::login(const QString& id, const QString& password) {
    if (m_db.contains(id) && m_db[id].password == password) {
        m_currentUser = id;
        m_loggedAsAdmin = (m_db[id].role == "Admin");
        return true;
    }
    return false;
}

/**
 * @brief Registra um novo usuário com perfil externo.
 * @param username Identificador escolhido.
 * @param password Senha do novo usuário.
 * @param name Nome completo.
 * @param email Endereço de e-mail para contato/reserva.
 * @return true se o registro for bem-sucedido.
 */
bool UserService::registerUser(const QString& username, const QString& password, const QString& name, const QString& email) {
    if (username.isEmpty() || password.isEmpty() || m_db.contains(username)) {
        return false;
    }

    // Novos cadastros entram como perfil "Externo" por padrão
    m_db[username] = {password, "Externo", username};
    return true;
}

/**
 * @brief Verifica se o usuário logado possui privilégios de administrador.
 * * Esta verificação é utilizada para habilitar o acesso à janela Adminmodel da Sprint 2.
 * @return true se o usuário for administrador.
 */
bool UserService::isAdmin() {
    return m_loggedAsAdmin;
}

/**
 * @brief Finaliza a sessão do usuário atual.
 * * Limpa as credenciais em memória e redefine o status de administrador.
 */
void UserService::logout() {
    m_currentUser = "";
    m_loggedAsAdmin = false;
}
