#include "reservalib.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

/** @brief Construtor da classe */
ReservaLib::ReservaLib() {}

/** @brief Implementação de salvar reserva */
void ReservaLib::salvarReserva(QString sala, QDate data, QString hora, Reserva r) {
    QSqlQuery query;
    query.prepare("INSERT OR REPLACE INTO reservas (sala_nome, data, horario, usuario_nome, perfil, ocupado) "
                  "VALUES (:sala, :data, :hora, :user, :perfil, :ocupado)");

    query.bindValue(":sala", sala);
    query.bindValue(":data", data.toString("yyyy-MM-dd"));
    query.bindValue(":hora", hora);
    query.bindValue(":user", r.nome);
    query.bindValue(":perfil", r.perfil);
    query.bindValue(":ocupado", r.ocupado ? 1 : 0);

    if (!query.exec()) {
        qDebug() << "Erro ao salvar reserva:" << query.lastError().text();
    }
}

/** @brief Implementação de buscar reserva */
Reserva ReservaLib::buscarReserva(QString sala, QDate data, QString hora) {
    Reserva r = {"", "", "", false}; // Reserva vazia padrão

    QSqlQuery query;
    query.prepare("SELECT usuario_nome, perfil, ocupado FROM reservas "
                  "WHERE sala_nome = :sala AND data = :data AND horario = :hora");

    query.bindValue(":sala", sala);
    query.bindValue(":data", data.toString("yyyy-MM-dd"));
    query.bindValue(":hora", hora);

    if (query.exec() && query.next()) {
        r.nome = query.value(0).toString();
        r.perfil = query.value(1).toString();
        r.ocupado = query.value(2).toBool();
    }

    return r;
}

/** @brief Implementação de verificar existência */
bool ReservaLib::existeReserva(QString sala, QDate data, QString hora) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM reservas "
                  "WHERE sala_nome = :sala AND data = :data AND horario = :hora");

    query.bindValue(":sala", sala);
    query.bindValue(":data", data.toString("yyyy-MM-dd"));
    query.bindValue(":hora", hora);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}
