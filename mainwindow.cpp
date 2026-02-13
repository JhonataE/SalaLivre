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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Configura colunas da Timeline
    ui->gridAgenda->setColumnCount(2);
    ui->gridAgenda->setHorizontalHeaderLabels({"Horário", "Status"});

    // Componentização: Instancia a classe concreta da DLL e atribui à Interface (baixo acoplamento)
    //Para usar SQL futuramente, basta criar nova classe que herda da interface e altera a inicialização
    reservaService = new ReservaLib();
}

MainWindow::~MainWindow() {
    delete ui;
    delete reservaService; //liberar memória do serviço
}

void MainWindow::on_btnBuscar_clicked() {
    QDialog dialog(this);
    dialog.setWindowTitle("Configurar Agendamento - SalaLivre");
    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    layout->addWidget(new QLabel("Perfil do Ator:"));
    QComboBox *comboUser = new QComboBox(&dialog);
    comboUser->addItems({"Docente", "Estudante", "Usuário Externo"});
    layout->addWidget(comboUser);

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
        this->perfilAtual = comboUser->currentText();
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

    // (Criação do Diálogo) ---
    QDialog d(this);
    d.setWindowTitle("Dados da Reserva");
    QFormLayout ly(&d);

    QLineEdit *editNome = new QLineEdit(&d);
    QLineEdit *editTel = new QLineEdit(&d);

    ly.addRow("Nome Completo:", editNome);
    ly.addRow("Telefone:", editTel);

    QPushButton *btnConfirmar = new QPushButton("Confirmar Reserva", &d);
    ly.addWidget(btnConfirmar);

    connect(btnConfirmar, &QPushButton::clicked, &d, &QDialog::accept);
    // ---------------------------------------------------------------------


    if (d.exec() == QDialog::Accepted && !editNome->text().isEmpty()) {
        QString sala = ui->listSalas->currentItem()->text();
        QString statusTxt = ui->lblStatus->text();
        QString predio = statusTxt.split("|").first().replace("Prédio: ", "").replace("Unidade: ", "").trimmed();

        for (int row : linhas) {
            QString hora = ui->gridAgenda->item(row, 0)->text();

            Reserva r;
            r.nome = editNome->text();
            r.telefone = editTel->text();
            r.perfil = this->perfilAtual;
            r.ocupado = true;

            // Uso da Interface e DLL
            reservaService->salvarReserva(sala, this->dataAtual, hora, r);
        }

        atualizarGradeHoraria(this->dataAtual, this->perfilAtual, sala, predio);
    }
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

        // Uso da Interface: Consultando o componente DLL
        if (reservaService->existeReserva(sala, data, hStr)) {
            Reserva r = reservaService->buscarReserva(sala, data, hStr);
            st->setText("OCUPADO (" + r.perfil + ")");
            st->setBackground(Qt::red);
            st->setToolTip("Nome: " + r.nome + "\nTel: " + r.telefone);
        } else {
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
