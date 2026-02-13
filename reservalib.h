#ifndef RESERVALIB_H
#define RESERVALIB_H

#include "IReservaService.h"


//encapsula a lógica de persistencia de dados, herdando de IReserva
/**
 * @brief Implementação concreta do serviço de reservas (Componente DLL).
 */
class ReservaLib : public IReservaService {
private:
    QMap<QString, Reserva> banco;

public:
    ReservaLib();
    void salvarReserva(QString sala, QDate data, QString hora, Reserva r) override;
    Reserva buscarReserva(QString sala, QDate data, QString hora) override;
    bool existeReserva(QString sala, QDate data, QString hora) override;
};

#endif
