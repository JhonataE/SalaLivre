/**
 * @file mainwindow.cpp
 * @brief Implementação da janela principal do sistema SalaLivre com integração SQL.
 * @author Jhonata
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "reservalib.h"
#include "adminmodel.h"
#include "databasemanager.h" // Importante para gerenciar a conexão
#include <QCalendarWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QSqlQuery>
#include <QSqlError>
#include <QInputDialog>

/**
 * @brief Construtor da classe MainWindow.
 * @details Inicializa os serviços de reserva, configura a tabela de horários e recupera os dados do usuário logado via UserService para controle de permissões.
 * @param service Ponteiro para a interface do serviço de usuários.
 * @param parent Ponteiro para o widget pai.
 */
MainWindow::MainWindow(IUserService* service, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , userService(service) {
    ui->setupUi(this);

    // Recupera os dados do usuário para automação de reservas
    this->dadosUsuarioLogado = userService->getLoggedUserData();
    this->perfilAtual = dadosUsuarioLogado.role;

    ui->gridAgenda->setColumnCount(2);
    ui->gridAgenda->setHorizontalHeaderLabels({"Horário", "Status"});

    // Instanciação da biblioteca de reservas
    reservaService = new ReservaLib();

    // --- NOVA LÓGICA DE ADMIN ---
    if (this->perfilAtual == "Admin") {
        ui->btnAreaAdm->setVisible(true);
    } else {
        ui->btnAreaAdm->setVisible(false);
    }
}

/**
 * @brief Destrutor da classe MainWindow.
 * @details Realiza a limpeza da memória desalocando a interface UI e o serviço de reservas.
 */
MainWindow::~MainWindow() {
    delete ui;
    delete reservaService;
}

/**
 * @brief Slot acionado ao clicar no botão Buscar.
 * @details Abre um diálogo para selecionar a unidade acadêmica e a data, filtrando as salas via SQL.
 */
void MainWindow::on_btnBuscar_clicked() {
    QDialog dialog(this);
    dialog.setWindowTitle("Configurar Agendamento - SalaLivre");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    layout->addWidget(new QLabel("Selecione a Unidade (Prédio):"));
    QComboBox *comboLocal = new QComboBox(&dialog);
    comboLocal->addItems({"ICEB", "DEMIN", "Bloco de Salas de aula"});
    layout->addWidget(comboLocal);

    layout->addWidget(new QLabel("Selecione a Data:"));
    QCalendarWidget *calendario = new QCalendarWidget(&dialog);
    layout->addWidget(calendario);

    QPushButton *btnOk = new QPushButton("Confirmar", &dialog);
    layout->addWidget(btnOk);
    connect(btnOk, &QPushButton::clicked, &dialog, &QDialog::accept);

    if (dialog.exec() == QDialog::Accepted) {
        this->dataAtual = calendario->selectedDate();
        QString predio = comboLocal->currentText();

        ui->listSalas->clear();
        ui->gridAgenda->setRowCount(0);

        // BUSCA NO BANCO DE DADOS (Substituindo os loops manuais)
        QSqlQuery query;
        query.prepare("SELECT nome FROM salas WHERE unidade = :unidade");
        query.bindValue(":unidade", predio);

        if (query.exec()) {
            while (query.next()) {
                ui->listSalas->addItem(query.value(0).toString());
            }
        }

        ui->lblStatus->setText("Prédio: " + predio + " | Data: " + this->dataAtual.toString("dd/MM/yyyy"));
    }
}

void MainWindow::on_btnAgendar_clicked() {
    QList<int> linhas;
    for (int i = 0; i < ui->gridAgenda->rowCount(); ++i) {
        if (ui->gridAgenda->item(i, 1)->text() == "Selecionado") {
            linhas.append(i);
        }
    }

    if (linhas.isEmpty()) {
        QMessageBox::warning(this, "Aviso", "Selecione horários 'Disponíveis' primeiro!");
        return;
    }

    QString sala = ui->listSalas->currentItem()->text();
    QString statusTxt = ui->lblStatus->text();
    QString predio = statusTxt.split("|").first().replace("Prédio: ", "").trimmed();

    for (int row : linhas) {
        QString hora = ui->gridAgenda->item(row, 0)->text();

        // PERSISTÊNCIA NO BANCO (Sprint 3)
        QSqlQuery query;
        query.prepare("INSERT INTO reservas (sala_nome, usuario_nome, data, horario) "
                      "VALUES (:sala, :user, :data, :hora)");
        query.bindValue(":sala", sala);
        query.bindValue(":user", this->dadosUsuarioLogado.name);
        query.bindValue(":data", this->dataAtual.toString("yyyy-MM-dd"));
        query.bindValue(":hora", hora);
        query.exec();

        // Mantém compatibilidade com o serviço legado se necessário
        Reserva r;
        r.nome = this->dadosUsuarioLogado.name;
        r.telefone = this->dadosUsuarioLogado.email;
        r.perfil = this->dadosUsuarioLogado.role;
        r.ocupado = true;
        reservaService->salvarReserva(sala, this->dataAtual, hora, r);
    }

    QMessageBox::information(this, "Sucesso", "Reserva gravada no banco de dados para: " + this->dadosUsuarioLogado.name);
    atualizarGradeHoraria(this->dataAtual, this->perfilAtual, sala, predio);
}

void MainWindow::on_listSalas_itemClicked(QListWidgetItem *item) {
    QString statusTxt = ui->lblStatus->text();
    QString predio = statusTxt.split("|").first().replace("Prédio: ", "").replace("Unidade: ", "").trimmed();
    atualizarGradeHoraria(this->dataAtual, this->perfilAtual, item->text(), predio);
}

void MainWindow::on_gridAgenda_cellClicked(int row, int column) {
    if (column == 1) {
        QTableWidgetItem *it = ui->gridAgenda->item(row, 1);
        if (it->text() == "Disponível") {
            it->setText("Selecionado");
            it->setBackground(Qt::yellow);
        } else if (it->text() == "Selecionado") {
            it->setText("Disponível");
            it->setBackground(Qt::green);
        } else if (it->text().contains("OCUPADO")) {
            QMessageBox::information(this, "Detalhes da Reserva", it->toolTip());
        }
    }
}

void MainWindow::atualizarGradeHoraria(QDate data, QString perfil, QString sala, QString predio) {
    ui->gridAgenda->setRowCount(0);
    ui->lblStatus->setText("Unidade: " + predio + " | Sala: " + sala + " | Data: " + data.toString("dd/MM/yyyy"));

    // Verifica status da sala (Manutenção) via SQL
    bool emManutencao = false;
    QSqlQuery qSala;
    qSala.prepare("SELECT manutencao FROM salas WHERE nome = :nome");
    qSala.bindValue(":nome", sala);
    if(qSala.exec() && qSala.next()) {
        emManutencao = qSala.value(0).toInt() == 1;
    }

    for (int hora = 7; hora < 24; ++hora) {
        int linha = ui->gridAgenda->rowCount();
        ui->gridAgenda->insertRow(linha);
        QString hStr = QString("%1:00").arg(hora, 2, 10, QChar('0'));
        ui->gridAgenda->setItem(linha, 0, new QTableWidgetItem(hStr));

        QTableWidgetItem *st = new QTableWidgetItem();

        // CONSULTA DE OCUPAÇÃO NO BANCO
        QSqlQuery qReserva;
        qReserva.prepare("SELECT usuario_nome FROM reservas WHERE sala_nome = :sala AND data = :data AND horario = :hora");
        qReserva.bindValue(":sala", sala);
        qReserva.bindValue(":data", data.toString("yyyy-MM-dd"));
        qReserva.bindValue(":hora", hStr);

        if (qReserva.exec() && qReserva.next()) {
            st->setText("OCUPADO");
            st->setBackground(Qt::red);
            st->setToolTip("Reservado por: " + qReserva.value(0).toString());
        }
        else if (emManutencao) {
            st->setText("Manutenção");
            st->setBackground(Qt::gray);
        }
        else {
            st->setText("Disponível");
            st->setBackground(Qt::green);

            if (perfil == "Usuário Externo" && (hora < 10 || hora > 16)) {
                st->setText("Restrito");
                st->setBackground(Qt::gray);
            }
        }
        ui->gridAgenda->setItem(linha, 1, st);
    }
    ui->gridAgenda->horizontalHeader()->setStretchLastSection(true);
}


void MainWindow::on_btnAreaAdm_clicked() {
    Adminmodel telaGestao(userService, this);
    telaGestao.exec();
}

void MainWindow::on_btnEditarPerfil_clicked() {
    bool ok;
    QString novaSenha = QInputDialog::getText(this, "Perfil", "Alterar Senha:",
                                              QLineEdit::Password, "", &ok);
    if (ok && !novaSenha.isEmpty()) {
        QSqlQuery query;
        query.prepare("UPDATE usuarios SET senha = :senha WHERE username = :user");
        query.bindValue(":senha", novaSenha);
        query.bindValue(":user", this->dadosUsuarioLogado.name);
        if(query.exec()) {
            QMessageBox::information(this, "Sucesso", "Senha atualizada!");
        }
    }
}

void MainWindow::on_btnVerDetalhes_clicked() {
    if (!ui->listSalas->currentItem()) {
        QMessageBox::warning(this, "Aviso", "Por favor, selecione uma sala primeiro.");
        return;
    }
    QString salaSelecionada = ui->listSalas->currentItem()->text();
    QMessageBox::information(this, "Detalhes", "Informações da sala: " + salaSelecionada);
}

void MainWindow::on_btnCancelarReserva_clicked() {
    if (!ui->listSalas->currentItem()) {
        QMessageBox::warning(this, "Aviso", "Selecione a sala para cancelar.");
        return;
    }

    QString salaNome = ui->listSalas->currentItem()->text();
    QSqlQuery query;
    query.prepare("DELETE FROM reservas WHERE sala_nome = :sala AND data = :data AND usuario_nome = :user");
    query.bindValue(":sala", salaNome);
    query.bindValue(":data", this->dataAtual.toString("yyyy-MM-dd"));
    query.bindValue(":user", this->dadosUsuarioLogado.name);

    if (userService && userService->isAdmin()) {
        ui->btnAreaAdm->setVisible(true);
    } else {
        ui->btnAreaAdm->setVisible(false);
    }
}
