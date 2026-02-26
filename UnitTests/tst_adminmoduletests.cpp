/**
 * @file tst_adminmoduletests.cpp
 * @brief Implementação dos testes unitários do módulo administrativo com Setup de Banco.
 */

#include "tst_adminmoduletests.h"
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "../adminmodel.h"
#include "../userservice.h"

/**
 * @brief Inicializa o ambiente de teste.
 * @details Configura um banco de dados SQLite em memória e popula com os dados necessários
 * para que as verificações de contagem de salas não falhem.
 */
void AdminModuleTests::initTestCase() {
    // Adiciona a conexão se ela ainda não existir (importante para evitar avisos do Qt)
    QSqlDatabase db;
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }

    db.setDatabaseName(":memory:");
    if (!db.open()) {
        QFAIL("Falha ao abrir banco em memória para testes.");
    }

    QSqlQuery query;
    // Criar tabela idêntica à do DatabaseManager
    query.exec("CREATE TABLE salas ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "nome TEXT UNIQUE, "
               "unidade TEXT, "
               "manutencao INTEGER DEFAULT 0, "
               "uso_externo INTEGER DEFAULT 1)");

    // Populando ICEB (23 salas)
    for (int i = 1; i <= 23; ++i) {
        query.prepare("INSERT INTO salas (nome, unidade) VALUES (:n, 'ICEB')");
        query.bindValue(":n", "Sala " + QString::number(i) + " - ICEB");
        query.exec();
    }

    // Populando DEMIN (16 salas)
    for (int i = 1; i <= 16; ++i) {
        query.prepare("INSERT INTO salas (nome, unidade) VALUES (:n, 'DEMIN')");
        query.bindValue(":n", "Sala " + QString::number(i) + " - DEMIN");
        query.exec();
    }

    // Populando Bloco de Salas (19 salas)
    for (int i = 1; i <= 19; ++i) {
        query.prepare("INSERT INTO salas (nome, unidade) VALUES (:n, 'Bloco de Salas')");
        query.bindValue(":n", "Sala " + QString::number(i) + " - Bloco de Salas");
        query.exec();
    }
}

void AdminModuleTests::testFiltragemSalas() {
    UserService service;
    Adminmodel admin(&service);

    QComboBox* comboU = admin.findChild<QComboBox*>("comboUnidades");
    QComboBox* comboS = admin.findChild<QComboBox*>("comboSalasEdicao");

    QVERIFY2(comboU != nullptr, "Componente comboUnidades nao encontrado");
    QVERIFY2(comboS != nullptr, "Componente comboSalasEdicao nao encontrado");

    // Testa ICEB
    comboU->setCurrentText("ICEB");
    QCOMPARE(comboS->count(), 23);

    // Testa DEMIN
    comboU->setCurrentText("DEMIN");
    QCOMPARE(comboS->count(), 16);

    // Testa Bloco de Salas
    comboU->setCurrentText("Bloco de Salas");
    QCOMPARE(comboS->count(), 19);
}

void AdminModuleTests::testEntradaDados() {
    UserService service;
    Adminmodel admin(&service);

    QSpinBox* spin = admin.findChild<QSpinBox*>("spinCapacidade");
    QVERIFY2(spin != nullptr, "Objeto spinCapacidade nao encontrado.");

    spin->setValue(10);
    QCOMPARE(spin->value(), 10);
}

void AdminModuleTests::cleanupTestCase() {
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
}

// Remova o #include "tst_adminmoduletests.moc" se estiver usando CMake moderno
