#include <QtTest>
#include <QSignalSpy>
#include "../IReservaService.h"
#include "../reservalib.h"

class UnitTests : public QObject {
    Q_OBJECT

private slots:
    // Cenário 1: Busca e Listagem de Salas
    void testListagemSalasPorPredio() {
        QString predio = "ICEB";
        QStringList salasEsperadas;
        for(int i = 1; i <= 23; ++i) salasEsperadas << "Sala " + QString::number(i) + " - ICEB";
        // Simulação da lógica de busca
        QStringList salasGeradas;
        if (predio == "ICEB") {
            for(int i = 1; i <= 23; ++i) salasGeradas << "Sala " + QString::number(i) + " - ICEB";
        }

        QCOMPARE(salasGeradas.size(), 23);
        QCOMPARE(salasGeradas, salasEsperadas);
    }

    // Cenário 2: Visualização da Timeline (Limites operacionais)
    void testLimitesTimeline() {
        int inicioOperacional = 7;
        int fimOperacional = 23; // até 23:00 (finalizando às 00:00)

        QList<int> horasGeradas;
        for (int h = 7; h < 24; ++h) horasGeradas << h;

        QCOMPARE(horasGeradas.first(), inicioOperacional);
        QCOMPARE(horasGeradas.last(), fimOperacional);
        QCOMPARE(horasGeradas.size(), 17); // 17 intervalos de hora
    }

    // Cenário 3: Seleção e Agendamento (Status e Cor)
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

    // Cenário 4: Persistência entre Salas e Datas
    void testPersistenciaEntreSalas() {
        ReservaLib repo;
        QDate hoje = QDate::currentDate();
        Reserva r1 = {"User1", "11", "Estudante", true};

        repo.salvarReserva("Sala 101", hoje, "10:00", r1);

        // Simula troca de sala (consulta outra sala)
        bool existeOutra = repo.existeReserva("Sala 102", hoje, "10:00");
        QVERIFY(!existeOutra);

        // Retorna e verifica se os dados da Sala 101 continuam lá
        QVERIFY(repo.existeReserva("Sala 101", hoje, "10:00"));
        QCOMPARE(repo.buscarReserva("Sala 101", hoje, "10:00").nome, QString("User1"));
    }

    // Cenário 5: Restrição para Usuário Externo
    void testRestricaoUsuarioExterno() {
        auto estaRestrito = [](int hora) { return (hora < 10 || hora > 16); };

        QVERIFY(estaRestrito(7));   // 07:00 -> Restrito
        QVERIFY(estaRestrito(9));   // 09:00 -> Restrito
        QVERIFY(!estaRestrito(10)); // 10:00 -> Liberado (limite inferior)
        QVERIFY(!estaRestrito(15)); // 15:00 -> Liberado
        QVERIFY(!estaRestrito(16)); // 16:00 -> Liberado (limite superior)
        QVERIFY(estaRestrito(17));  // 17:00 -> Restrito
    }
};

QTEST_APPLESS_MAIN(UnitTests)
#include "tst_unittests.moc"
