/**
 * @file tst_adminmoduletests.cpp
 * @brief Testes das funcionalidades administrativas implementadas na Sprint 2.
 * * Este arquivo contém a suíte de testes unitários para validar a lógica de interface
 * e filtragem da janela Adminmodel.
 */

#include <QtTest>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include "../adminmodel.h"
#include "../userservice.h"

/**
 * @class AdminModuleTests
 * @brief Classe de teste para o módulo de administração.
 * * Valida a interface Adminmodel, incluindo a filtragem dinâmica de salas por unidade
 * e a edição de atributos físicos como capacidade.
 */
class AdminModuleTests : public QObject {
    Q_OBJECT

private slots:
    /**
     * @brief Valida a filtragem dinâmica de salas ao trocar de unidade.
     * * Testa se o comboSalasEdicao carrega as sequências corretas para ICEB (23),
     * DEMIN (16) e Bloco de Salas (19).
     */
    void testFiltragemSalas() {
        UserService service;
        Adminmodel admin(&service);

        QComboBox* comboU = admin.findChild<QComboBox*>("comboUnidades");
        QComboBox* comboS = admin.findChild<QComboBox*>("comboSalasEdicao");

        QVERIFY2(comboU != nullptr, "Componente comboUnidades nao encontrado no UI");
        QVERIFY2(comboS != nullptr, "Componente comboSalasEdicao nao encontrado no UI");

        comboU->setCurrentText("ICEB");
        QCOMPARE(comboS->count(), 23);

        comboU->setCurrentText("DEMIN");
        QCOMPARE(comboS->count(), 16);

        comboU->setCurrentText("Bloco de Salas");
        QCOMPARE(comboS->count(), 19);
    }

    /**
     * @brief Testa a entrada de valores no campo de capacidade da sala.
     * * Verifica se o componente spinCapacidade aceita e mantém valores inteiros.
     */
    void testEntradaDados() {
        UserService service;
        Adminmodel admin(&service);

        QSpinBox* spin = admin.findChild<QSpinBox*>("spinCapacidade");
        QVERIFY2(spin != nullptr, "Erro: O objeto 'spinCapacidade' nao foi encontrado.");

        spin->setValue(10);
        QCOMPARE(spin->value(), 10);
    }
};

#include "tst_adminmoduletests.moc"
