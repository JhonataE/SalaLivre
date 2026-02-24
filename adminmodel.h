#ifndef ADMINMODEL_H
#define ADMINMODEL_H

#include <QDialog>
#include <QInputDialog> // Adicionado para suportar os diálogos de entrada
#include <QStringList>  // Adicionado para as listas de opções
#include "IUserService.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Adminmodel; }
QT_END_NAMESPACE

/**
 * @class Adminmodel
 * @brief Classe responsável pela interface de administração do sistema SalaLivre.
 */
class Adminmodel : public QDialog {
    Q_OBJECT

public:
    explicit Adminmodel(IUserService* service, QWidget *parent = nullptr);
    ~Adminmodel();

private slots:
    // Eixo 1: Gestão de Unidades
    void on_btnGerenciarUnidade_clicked();
    void on_btnRegrasUnidade_clicked();

    // Eixo 2: Gestão de Salas
    void on_btnNovaSala_clicked();
    void on_btnSalvarAtributosSala_clicked();
    void atualizarComboSalas(const QString &unidade);
    // Controle
    void fecharJanela();

private:
    Ui::Adminmodel *ui;
    IUserService* m_service;
    void atualizarListas();
};

#endif
