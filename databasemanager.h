#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QString>

class DatabaseManager {
public:
    DatabaseManager();
    bool abrirConexao();
    void fecharConexao();
    void criarTabelasIniciais();

private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
