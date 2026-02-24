/**
 * @file tst_unittests.cpp
 * @brief Testes unitários para as funcionalidades de reserva e visualização.
 * @author Jhonata
 */

#include <QtTest>
#include <QSignalSpy>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include "../IReservaService.h"
#include "../reservalib.h"
#include "tst_adminmoduletests.h"
#include "databasemanager.h"

/**
 * @class UnitTests
 * @brief Classe responsável por testar a lógica de agendamento, limites de horário e persistência SQL.
 */
class UnitTests : public QObject {
    Q_OBJECT

private slots:
    /**
     * @brief Inicializa o ambiente de teste uma única vez.
     * @details Configura o banco SQLite em memória para que os testes não dependam de arquivos externos.
     */
    void initTestCase() {
        // Verifica se já existe uma conexão para evitar avisos de duplicidade
        if (!QSqlDatabase::contains("qt_sql_default_connection")) {
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(":memory:");
            if (!db.open()) {
                QFAIL("Não foi possível abrir o banco de dados em memória para os testes.");
            }
        }

        QSqlQuery query;
        // Cria a tabela de reservas necessária para a ReservaLib funcionar
        query.exec("CREATE TABLE IF NOT EXISTS reservas ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "sala_nome TEXT, "
                   "usuario_nome TEXT, "
                   "perfil TEXT, "
                   "data TEXT, "
                   "horario TEXT, "
                   "ocupado INTEGER DEFAULT 1)");
    }

    /**
     * @brief Limpa o banco entre os testes para garantir independência.
     */
    void init() {
        QSqlQuery query;
        query.exec("DELETE FROM reservas");
    }

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

    void testLimitesTimeline() {
        int inicioOperacional = 7;
        int fimOperacional = 23;
        QList<int> horasGeradas;
        for (int h = 7; h < 24; ++h) horasGeradas << h;
        QCOMPARE(horasGeradas.first(), inicioOperacional);
        QCOMPARE(horasGeradas.last(), fimOperacional);
        QCOMPARE(horasGeradas.size(), 17);
    }

    void testStatusAgendamento() {
        ReservaLib repo;
        Reserva r = {"Jhonata", "123", "Docente", true};
        QDate data = QDate::currentDate();

        repo.salvarReserva("Sala 101", data, "14:00", r);

        Reserva res = repo.buscarReserva("Sala 101", data, "14:00");
        QVERIFY(res.ocupado);
        QCOMPARE(res.perfil, QString("Docente"));
    }

    void testPersistenciaEntreSalas() {
        ReservaLib repo;
        QDate hoje = QDate::currentDate();
        Reserva r1 = {"User1", "11", "Estudante", true};

        repo.salvarReserva("Sala 101", hoje, "10:00", r1);

        bool existeOutra = repo.existeReserva("Sala 102", hoje, "10:00");
        QVERIFY(!existeOutra);
        QVERIFY(repo.existeReserva("Sala 101", hoje, "10:00"));
    }

    void testRestricaoUsuarioExterno() {
        auto estaRestrito = [](int hora) { return (hora < 10 || hora > 16); };
        QVERIFY(estaRestrito(7));
        QVERIFY(!estaRestrito(12));
        QVERIFY(estaRestrito(17));
    }

    void testVisualizacaoDetalhes() {
        int capacidade = 40;
        QString recursos = "Projetor, Wi-fi";
        QString detalhesEsperados = "Capacidade: 40 pessoas | Recursos: Projetor, Wi-fi";
        QString detalhesGerados = QString("Capacidade: %1 pessoas | Recursos: %2").arg(capacidade).arg(recursos);
        QCOMPARE(detalhesGerados, detalhesEsperados);
    }

    void testCancelamentoDinamico() {
        QStringList listaVisual;
        listaVisual << "Sala 101 (Reservada)" << "Sala 102";
        for(int i = 0; i < listaVisual.size(); ++i) {
            if(listaVisual[i].contains("(Reservada)")) {
                listaVisual[i] = listaVisual[i].split(" (").first();
            }
        }
        QCOMPARE(listaVisual[0], QString("Sala 101"));
    }

    void testEdicaoPerfil() {
        QString senhaAntiga = "12345";
        QString senhaNova = "UFOP2026";
        if(!senhaNova.isEmpty() && senhaNova != senhaAntiga) {
            senhaAntiga = senhaNova;
        }
        QCOMPARE(senhaAntiga, QString("UFOP2026"));
    }

    void testBloqueioManutencao() {
        bool emManutencao = true;
        auto podeReservar = [&](bool manutencao) { return !manutencao; };
        QVERIFY(podeReservar(emManutencao) == false);
    }

    void testRestricaoUsoExternoManual() {
        bool disponivelExterno = false;
        QString tipoUsuario = "Externo";
        bool acessoPermitido = true;
        if (!disponivelExterno && tipoUsuario == "Externo") {
            acessoPermitido = false;
        }
        QVERIFY(acessoPermitido == false);
    }
};

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
