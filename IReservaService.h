#ifndef IRESERVASERVICE_H
#define IRESERVASERVICE_H

#include <QString>
#include <QDate>
#include <QMap>

/**
 * @file IRESERVASERVICE_H
 * @brief Definição da interface e estruturas base para o serviço de reservas.
 */

/**
 * @struct Reserva
 * @brief Estrutura de dados que representa uma reserva de sala.
 */
struct Reserva {
    QString nome;     ///< Nome do usuário que realizou a reserva.
    QString telefone; ///< Atualmente armazena o E-mail para facilitar a exibição na interface.
    QString perfil;   ///< Perfil do usuário (Ex: Aluno, Docente, Admin).
    bool ocupado = false; ///< Indica se o horário está preenchido.
};

/**
 * @class IReservaService
 * @brief Interface abstrata para o serviço de gestão de reservas.
 * @details Define os métodos obrigatórios para persistência e consulta de agendamentos,
 * permitindo o desacoplamento entre a interface e a implementação real (ReservaLib).
 */
class IReservaService {
public:
    /** @brief Destrutor virtual para garantir a limpeza correta nas classes derivadas. */
    virtual ~IReservaService() {}

    /**
     * @brief Método abstrato para salvar uma reserva.
     * @param sala Identificador da sala.
     * @param data Data do agendamento.
     * @param hora Horário do agendamento.
     * @param r Objeto contendo os dados do reservante.
     */
    virtual void salvarReserva(QString sala, QDate data, QString hora, Reserva r) = 0;

    /**
     * @brief Método abstrato para buscar os dados de uma reserva.
     * @param sala Identificador da sala.
     * @param data Data consultada.
     * @param hora Horário consultado.
     * @return Estrutura Reserva com as informações encontradas.
     */
    virtual Reserva buscarReserva(QString sala, QDate data, QString hora) = 0;

    /**
     * @brief Método abstrato para verificar ocupação de um horário.
     * @return true se houver reserva ativa, false caso contrário.
     */
    virtual bool existeReserva(QString sala, QDate data, QString hora) = 0;
};

#endif
