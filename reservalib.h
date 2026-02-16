#ifndef RESERVALIB_H
#define RESERVALIB_H

#include "IReservaService.h"

/**
 * @file reservalib.h
 * @brief Definição da classe ReservaLib para persistência de dados.
 */

/**
 * @class ReservaLib
 * @brief Implementação concreta do serviço de reservas (Componente de Persistência).
 * @details Esta classe encapsula a lógica de armazenamento de dados em memória utilizando um QMap,
 * herdando da interface IReservaService para garantir o desacoplamento do sistema.
 */
class ReservaLib : public IReservaService {
private:
    /**
     * @brief Estrutura de dados em memória que armazena as reservas.
     * @details Utiliza uma chave composta (Sala+Data+Hora) para mapear cada objeto Reserva.
     */
    QMap<QString, Reserva> banco;

public:
    /**
     * @brief Construtor padrão da classe ReservaLib.
     */
    ReservaLib();

    /**
     * @brief Persiste uma nova reserva no banco de dados em memória.
     * @param sala Nome ou identificador da sala.
     * @param data Data do agendamento.
     * @param hora Horário do agendamento.
     * @param r Objeto contendo os detalhes da reserva (Nome, Perfil, etc.).
     */
    void salvarReserva(QString sala, QDate data, QString hora, Reserva r) override;

    /**
     * @brief Recupera os dados de uma reserva específica.
     * @param sala Nome da sala.
     * @param data Data consultada.
     * @param hora Horário consultado.
     * @return Objeto Reserva contendo as informações encontradas.
     */
    Reserva buscarReserva(QString sala, QDate data, QString hora) override;

    /**
     * @brief Verifica a existência de um agendamento para um local e tempo específicos.
     * @param sala Nome da sala.
     * @param data Data consultada.
     * @param hora Horário consultado.
     * @return true se a sala estiver ocupada no horário solicitado, false caso contrário.
     */
    bool existeReserva(QString sala, QDate data, QString hora) override;
};

#endif
