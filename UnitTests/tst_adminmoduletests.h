/**
 * @file tst_adminmoduletests.h
 * @brief Definição da classe de testes do módulo administrativo.
 */

#ifndef TST_ADMINMODULETESTS_H
#define TST_ADMINMODULETESTS_H

#include <QtTest>
#include <QObject>

class AdminModuleTests : public QObject {
    Q_OBJECT

private slots:
    void initTestCase();


    void cleanupTestCase();
    /**
     * @brief Valida a filtragem dinâmica de salas ao trocar de unidade.
     */
    void testFiltragemSalas();

    /**
     * @brief Testa a entrada de valores no campo de capacidade da sala.
     */
    void testEntradaDados();
};

#endif // TST_ADMINMODULETESTS_H
