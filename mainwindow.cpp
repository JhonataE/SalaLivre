/**
 * @file mainwindow.cpp
 * @brief Implementação da janela principal do sistema SalaLivre.
 * @author Jhonata
 */

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "reservalib.h"
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
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "adminmodel.h"

/**
 * @details Inicializa os serviços e recupera os dados do usuário logado via UserService.
 */

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

    // Define o perfil padrão baseado no login para as restrições de busca
    this->perfilAtual = dadosUsuarioLogado.role;

    ui->gridAgenda->setColumnCount(2);
    ui->gridAgenda->setHorizontalHeaderLabels({"Horário", "Status"});

    // Instanciação da biblioteca de reservas
    reservaService = new ReservaLib();

    // --- NOVA LÓGICA DE ADMIN ---
    // Verifica se o usuário logado é Administrador
    if (this->perfilAtual == "Admin") {
        ui->btnAreaAdm->setVisible(true); // O botão deve estar criado no mainwindow.ui
    } else {
        ui->btnAreaAdm->setVisible(false); // Garante que alunos/externos não vejam
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
 * @details Abre um diálogo para selecionar a unidade acadêmica e a data, filtrando as salas disponíveis para exibição.
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

        if (predio == "Bloco de Salas de aula") {
            for(int i = 101; i <= 106; ++i) ui->listSalas->addItem("Sala " + QString::number(i));
            for(int i = 201; i <= 213; ++i) ui->listSalas->addItem("Sala " + QString::number(i));
        } else if (predio == "ICEB") {
            for(int i = 1; i <= 23; ++i) ui->listSalas->addItem("Sala " + QString::number(i) + " - ICEB");
        } else if (predio == "DEMIN") {
            for(int i = 1; i <= 16; ++i) ui->listSalas->addItem("Sala " + QString::number(i) + " - DEMIN");
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

    // Engenharia de Software: Uso de dados automáticos do login (SB01)
    for (int row : linhas) {
        QString hora = ui->gridAgenda->item(row, 0)->text();

        Reserva r;
        r.nome = this->dadosUsuarioLogado.name;
        // Armazenamos o e-mail no campo telefone para facilitar a exibição
        r.telefone = this->dadosUsuarioLogado.email;
        r.perfil = this->dadosUsuarioLogado.role;
        r.ocupado = true;

        reservaService->salvarReserva(sala, this->dataAtual, hora, r);
    }

    QMessageBox::information(this, "Sucesso", "Reserva confirmada automaticamente para: " + this->dadosUsuarioLogado.name);
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

    for (int hora = 7; hora < 24; ++hora) {
        int linha = ui->gridAgenda->rowCount();
        ui->gridAgenda->insertRow(linha);
        QString hStr = QString("%1:00").arg(hora, 2, 10, QChar('0'));
        ui->gridAgenda->setItem(linha, 0, new QTableWidgetItem(hStr));

        QTableWidgetItem *st = new QTableWidgetItem();

        // Verifica se existe reserva usando a interface do serviço
        if (reservaService->existeReserva(sala, data, hStr)) {
            Reserva r = reservaService->buscarReserva(sala, data, hStr);
            st->setText("OCUPADO (" + r.perfil + ")");
            st->setBackground(Qt::red);

            // Exibe Email em vez de Telefone conforme solicitado
            st->setToolTip("Nome: " + r.nome + "\nEmail: " + r.telefone);
        }
        else {
            st->setText("Disponível");
            st->setBackground(Qt::green);

            // Restrição para usuários externos conforme regras de negócio
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
    // Instancia a janela de gestão passando o serviço
    Adminmodel telaGestao(userService, this);

    // Abre como Modal (o usuário precisa fechar a gestão para voltar à agenda)
    telaGestao.exec();

    // Dica: Se algo foi alterado na gestão, você pode atualizar a lista de salas aqui
    // this->carregarSalasNoComboBox();
}
