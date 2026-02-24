/**
 * @file mainwindow.h
 * @brief Classe principal para a interface do sistema SalaLivre.
 * @author Jhonata
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QString>
#include <QListWidgetItem>
#include "IReservaService.h"
#include "IUserService.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Gerencia a interface de agendamento e integra os serviços de reserva e usuário.
 */

class Adminmodel;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Construtor da MainWindow.
     * @param service Ponteiro para a interface do serviço de usuários (Injeção de Dependência).
     * @param parent Widget pai (opcional).
     */
    explicit MainWindow(IUserService* service, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnBuscar_clicked();
    void on_btnAgendar_clicked();
    void on_listSalas_itemClicked(QListWidgetItem *item);
    void on_gridAgenda_cellClicked(int row, int column);
    void on_btnAreaAdm_clicked();
    void on_btnEditarPerfil_clicked();
    void on_btnVerDetalhes_clicked();
    void on_btnCancelarReserva_clicked();


private:
    Ui::MainWindow *ui;

    /** @brief Dependência da interface de reserva (Inversão de Dependência). */
    IReservaService* reservaService;

    /** @brief Dependência da interface de usuário. */
    IUserService* userService;

    /** @brief Dados do usuário autenticado para preenchimento automático. */
    UserData dadosUsuarioLogado;

    /**
     * @brief Atualiza a visualização dos horários para uma sala específica.
     */
    void atualizarGradeHoraria(QDate data, QString perfil, QString sala, QString predio);

    QString perfilAtual;
    QDate dataAtual;
};

#endif
