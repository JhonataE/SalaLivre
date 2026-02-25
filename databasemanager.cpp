#include "databasemanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sala_livre.db");
}

bool DatabaseManager::abrirConexao() {
    if (!db.open()) {
        qDebug() << "Erro ao conectar:" << db.lastError().text();
        return false;
    }

    // ATIVAÇÃO DE CHAVES ESTRANGEIRAS (Obrigatório para o SQLite respeitar as relações)
    QSqlQuery query;
    query.exec("PRAGMA foreign_keys = ON;");

    return true;
}

void DatabaseManager::criarTabelasIniciais() {
    QSqlQuery query;

    // 1. Tabela de Salas
    query.exec("CREATE TABLE IF NOT EXISTS salas ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "nome TEXT UNIQUE, "
               "unidade TEXT, "
               "manutencao INTEGER DEFAULT 0, "
               "uso_externo INTEGER DEFAULT 1)");

    // 2. Tabela de Usuários (Atualizada com nome e email)
    query.exec("CREATE TABLE IF NOT EXISTS usuarios ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "username TEXT UNIQUE, "
               "senha TEXT, "
               "role TEXT, " // Chamamos de 'role' para bater com o UserService
               "nome_completo TEXT, "
               "email TEXT)");

    // 3. Tabela de Reservas (Atualizada para bater com o ReservaLib)
    query.exec("CREATE TABLE IF NOT EXISTS reservas ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "sala_nome TEXT, "
               "usuario_nome TEXT, "
               "perfil TEXT, "
               "data TEXT, "
               "horario TEXT, "
               "ocupado INTEGER DEFAULT 1, "
               "FOREIGN KEY(sala_nome) REFERENCES salas(nome))");

    // --- SEED: DADOS INICIAIS ---

    // Cadastrar Admin padrão se não existir
    query.exec("SELECT COUNT(*) FROM usuarios WHERE role = 'Admin'");
    if (query.next() && query.value(0).toInt() == 0) {
        query.prepare("INSERT INTO usuarios (username, senha, role, nome_completo, email) "
                      "VALUES (:u, :s, :r, :n, :e)");
        query.bindValue(":u", "admin");
        query.bindValue(":s", "admin123");
        query.bindValue(":r", "Admin");
        query.bindValue(":n", "Administrador do Sistema");
        query.bindValue(":e", "admin@ufop.edu.br");
        query.exec();
    }

    // Cadastrar salas iniciais do ICEB
    query.exec("SELECT COUNT(*) FROM salas");
    if (query.next() && query.value(0).toInt() == 0) {
        for (int i = 1; i <= 23; ++i) {
            query.prepare("INSERT INTO salas (nome, unidade) VALUES (:nome, :unidade)");
            query.bindValue(":nome", "Sala " + QString::number(i) + " - ICEB");
            query.bindValue(":unidade", "ICEB");
            query.exec();
        }
        qDebug() << "Banco de dados inicializado com salas e usuário admin!";
    }
}
