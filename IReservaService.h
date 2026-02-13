#ifndef IRESERVASERVICE_H
#define IRESERVASERVICE_H

#include <QString>
#include <QDate>
#include <QMap>

// Estrutura de dados comum
struct Reserva {
    QString nome;
    QString telefone;
    QString perfil;
    bool ocupado = false;
};

/**
 * @brief Interface para o serviço de gestão de reservas.
 */
class IReservaService {
public:
    virtual ~IReservaService() {}
    virtual void salvarReserva(QString sala, QDate data, QString hora, Reserva r) = 0;
    virtual Reserva buscarReserva(QString sala, QDate data, QString hora) = 0;
    virtual bool existeReserva(QString sala, QDate data, QString hora) = 0;
};

#endif
