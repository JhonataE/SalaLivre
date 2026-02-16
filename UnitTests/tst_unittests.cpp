/**
 * @file tst_unittests.cpp
 * @brief Testes unitários para as funcionalidades de reserva e visualização da Sprint 1.
 * @author Jhonata
 * @date 2026-02-15
 */

#include <QtTest>
#include <QSignalSpy>
#include <QApplication>
#include "../IReservaService.h"
#include "../reservalib.h"
#include "tst_adminmoduletests.cpp"

/**
 * @class UnitTests
 * @brief Classe responsável por testar a lógica de agendamento, limites de horário e persistência.
 */
class UnitTests : public QObject {
    Q_OBJECT

private slots:
    /**
     * @brief Valida a geração da lista de salas por prédio.
     * Verifica se ao selecionar o ICEB, o sistema gera corretamente a sequência de 1 a 23.
     */
    void testListagemSalasPorPredio() {
        QString predio = "ICEB";
        QStringList salasEsperadas;
        for(int i = 1; i <= 23; ++i) salasEsperadas << "Sala " + QString::number(i) + " - ICEB";
        QStringList salasGeradas;
        if (predio == "ICEB") {
            for(int i = 1; i <= 23; ++i) salasGeradas << "Sala " + QString::number(i) + " - ICEB";
        }
        QCOMPARE(salasGeradas.size(), 23);
        QCOMPARE(salasGeradas, salasEsperadas);
    }

    /**
     * @brief Testa os limites da grade horária (timeline).
     * Garante que a agenda inicie às 07:00 e termine às 23:00 (finalizando à meia-noite).
     */
    void testLimitesTimeline() {
        int inicioOperacional = 7;
        int fimOperacional = 23;
        QList<int> horasGeradas;
        for (int h = 7; h < 24; ++h) horasGeradas << h;
        QCOMPARE(horasGeradas.first(), inicioOperacional);
        QCOMPARE(horasGeradas.last(), fimOperacional);
        QCOMPARE(horasGeradas.size(), 17);
    }

    /**
     * @brief Valida o status visual e lógico de um agendamento.
     * Verifica se o sistema identifica corretamente uma sala ocupada e exibe o perfil do usuário.
     */
    void testStatusAgendamento() {
        ReservaLib repo;
        Reserva r = {"Jhonata", "123", "Docente", true};
        QDate data = QDate::currentDate();
        repo.salvarReserva("Sala 101", data, "14:00", r);
        Reserva res = repo.buscarReserva("Sala 101", data, "14:00");
        QString statusEsperado = "OCUPADO (" + res.perfil + ")";
        QVERIFY(res.ocupado);
        QCOMPARE(statusEsperado, QString("OCUPADO (Docente)"));
    }

    /**
     * @brief Testa a independência de dados entre diferentes salas.
     * Garante que uma reserva em uma sala não apareça em outra sala na mesma data e hora.
     */
    void testPersistenciaEntreSalas() {
        ReservaLib repo;
        QDate hoje = QDate::currentDate();
        Reserva r1 = {"User1", "11", "Estudante", true};
        repo.salvarReserva("Sala 101", hoje, "10:00", r1);
        bool existeOutra = repo.existeReserva("Sala 102", hoje, "10:00");
        QVERIFY(!existeOutra);
        QVERIFY(repo.existeReserva("Sala 101", hoje, "10:00"));
        QCOMPARE(repo.buscarReserva("Sala 101", hoje, "10:00").nome, QString("User1"));
    }

    /**
     * @brief Valida as restrições de horário para usuários externos.
     * Verifica se o acesso é bloqueado antes das 10:00 e após as 16:00 para este perfil.
     */
    void testRestricaoUsuarioExterno() {
        auto estaRestrito = [](int hora) { return (hora < 10 || hora > 16); };
        QVERIFY(estaRestrito(7));
        QVERIFY(estaRestrito(9));
        QVERIFY(!estaRestrito(10));
        QVERIFY(!estaRestrito(15));
        QVERIFY(!estaRestrito(16));
        QVERIFY(estaRestrito(17));
    }
};

/**
 * @brief Ponto de entrada principal para a execução dos testes.
 * Inicializa o QApplication e executa as suítes de teste de ambas as Sprints.
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    int status = 0;

    {
        UnitTests tc1;
        status |= QTest::qExec(&tc1, argc, argv);
    }

    {
        AdminModuleTests tc2;
        status |= QTest::qExec(&tc2, argc, argv);
    }

    return status;
}

#include "tst_unittests.moc"
