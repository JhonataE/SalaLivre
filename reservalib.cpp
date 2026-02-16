#include "reservalib.h"

/** @brief Construtor da classe */
ReservaLib::ReservaLib() {}

/** @brief Implementação de salvar reserva */
void ReservaLib::salvarReserva(QString sala, QDate data, QString hora, Reserva r) {
    QString chave = sala + "_" + data.toString("yyyyMMdd") + "_" + hora;
    banco[chave] = r;
}

/** @brief Implementação de buscar reserva */
Reserva ReservaLib::buscarReserva(QString sala, QDate data, QString hora) {
    QString chave = sala + "_" + data.toString("yyyyMMdd") + "_" + hora;
    return banco.value(chave);
}

/** @brief Implementação de verificar existência */
bool ReservaLib::existeReserva(QString sala, QDate data, QString hora) {
    QString chave = sala + "_" + data.toString("yyyyMMdd") + "_" + hora;
    return banco.contains(chave);
}

