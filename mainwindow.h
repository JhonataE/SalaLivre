/**
 * @file mainwindow.h
 * @brief Classe principal para a interface do sistema ProFinder.
 * @author Jhonata
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QString>
#include <QListWidgetItem>
#include "IReservaService.h" // Inclui a interface que já contém a struct Reserva

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Classe MainWindow que gerencia a interação do usuário com o sistema.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnBuscar_clicked();
    void on_btnAgendar_clicked();
    void on_listSalas_itemClicked(QListWidgetItem *item);
    void on_gridAgenda_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;

    /**
     * @brief Ponteiro para a interface do serviço.
     * Aqui aplicamos a Inversão de Dependência: MainWindow depende da abstração (Interface).
     */
    IReservaService* reservaService; //dependência

    void atualizarGradeHoraria(QDate data, QString perfil, QString sala, QString predio);

    QString perfilAtual;
    QDate dataAtual;
};

#endif
