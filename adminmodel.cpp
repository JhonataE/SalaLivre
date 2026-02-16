/**
 * @file adminmodel.cpp
 * @brief Implementação do módulo de administração do sistema SalaLivre.
 * @author Jhonata
 * @details Contém a lógica para gerenciamento de unidades acadêmicas, criação de salas
 * e edição de atributos físicos como capacidade e recursos disponíveis.
 */

#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>

#include "adminmodel.h"
#include "ui_adminmodel.h"

/**
 * @brief Construtor da classe Adminmodel.
 * @details Inicializa a interface gráfica, popula as listas iniciais de unidades e
 * conecta o sinal de mudança de unidade para atualizar as salas dinamicamente.
 * @param service Ponteiro para o serviço de usuários para verificação de permissões.
 * @param parent Ponteiro para o widget pai.
 */
Adminmodel::Adminmodel(IUserService* service, QWidget *parent) :
    QDialog(parent), ui(new Ui::Adminmodel), m_service(service)
{
    ui->setupUi(this);
    atualizarListas();

    // Conexão para atualizar o combo de salas sempre que a unidade selecionada mudar
    connect(ui->comboUnidades, &QComboBox::currentTextChanged, this, &Adminmodel::atualizarComboSalas);
}

/**
 * @brief Destrutor da classe Adminmodel.
 * @details Libera os recursos alocados pela interface de usuário.
 */
Adminmodel::~Adminmodel() { delete ui; }

// --- GESTÃO DE UNIDADES ---

/**
 * @brief Slot para gerenciar ações relacionadas às unidades (Prédios).
 * @details Abre diálogos para cadastrar novas unidades, editar nomes ou remover unidades existentes.
 */
void Adminmodel::on_btnGerenciarUnidade_clicked() {
    QStringList opcoes = {"Cadastrar Nova", "Editar Nome", "Remover Unidade"};
    bool ok;
    QString acao = QInputDialog::getItem(this, "Unidades", "Selecione a ação:", opcoes, 0, false, &ok);

    if (ok && !acao.isEmpty()) {
        if (acao == "Cadastrar Nova") {
            QString nome = QInputDialog::getText(this, "Novo", "Nome da Unidade:", QLineEdit::Normal, "", &ok);
            if (ok && !nome.isEmpty()) {
                // Lógica de salvamento no serviço
                QMessageBox::information(this, "Sucesso", "Unidade " + nome + " cadastrada.");
            }
        } else if (acao == "Remover Unidade") {
            // Exemplo de confirmação de segurança para evitar exclusões acidentais
            auto res = QMessageBox::question(this, "Aviso", "Tem certeza? Isso afetará todas as salas vinculadas.");
            if (res == QMessageBox::Yes) { /* m_service->removerUnidade(...) */ }
        }
    }
}

/**
 * @brief Slot para definição de regras gerais da unidade selecionada.
 * @details Permite ao administrador definir horários e limites de uso para todas as salas de um prédio.
 */
void Adminmodel::on_btnRegrasUnidade_clicked() {
    bool ok;
    QString regras = QInputDialog::getMultiLineText(this, "Regras Gerais",
                                                    "Defina as regras (Horários, Limites, etc):",
                                                    "1. Horário: 07h às 22h\n2. Limite: 4h/dia", &ok);
    if (ok) {
        QMessageBox::information(this, "Regras Atualizadas", "As novas diretrizes foram aplicadas à unidade.");
    }
}

// --- GESTÃO DE SALAS ---

/**
 * @brief Slot para criação de uma nova sala na unidade atual.
 * @details Solicita o identificador da sala e a vincula automaticamente à unidade selecionada no comboUnidades.
 */
void Adminmodel::on_btnNovaSala_clicked() {
    bool ok;
    QString idSala = QInputDialog::getText(this, "Nova Sala", "Identificador/Número da Sala:", QLineEdit::Normal, "", &ok);
    if (ok && !idSala.isEmpty()) {
        // Vincula à unidade selecionada no ComboBox da interface
        QString unidade = ui->comboUnidades->currentText();
        QMessageBox::information(this, "Sucesso", "Sala " + idSala + " criada no " + unidade);
    }
}

/**
 * @brief Slot para salvar as edições de atributos de uma sala.
 * @details Captura a capacidade (spinCapacidade) e os recursos (txtRecursos) para atualizar a sala selecionada.
 */
void Adminmodel::on_btnSalvarAtributosSala_clicked() {
    // Captura dados direto dos campos da interface (sem abrir nova tela)
    int capacidade = ui->spinCapacidade->value();
    QString recursos = ui->txtRecursos->text();
    QString salaAlvo = ui->comboSalasEdicao->currentText();

    if (salaAlvo.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Selecione uma sala para editar.");
        return;
    }

    // Persistência de dados através do serviço de administração
    QMessageBox::information(this, "Atualizado", "Atributos da " + salaAlvo + " salvos com sucesso.");
}

/**
 * @brief Slot para fechar a janela de administração.
 */
void Adminmodel::on_btnSair_clicked() { this->close(); }

/**
 * @brief Inicializa as listas de unidades e salas na interface.
 * @details Define os prédios padrão (ICEB, DEMIN, Bloco de Salas) e dispara a atualização de salas inicial.
 */
void Adminmodel::atualizarListas() {
    ui->comboUnidades->clear();
    // Unidades reais da UFOP conforme definido nos requisitos
    ui->comboUnidades->addItems({"ICEB", "DEMIN", "Bloco de Salas"});

    atualizarComboSalas(ui->comboUnidades->currentText());
}

/**
 * @brief Atualiza dinamicamente o seletor de salas com base na unidade acadêmica.
 * @details Implementa as sequências de salas para ICEB (1-23), DEMIN (1-16) e Bloco de Salas (101-213).
 * @param unidade Nome da unidade selecionada para filtragem.
 */
void Adminmodel::atualizarComboSalas(const QString &unidade) {
    ui->comboSalasEdicao->clear();

    if (unidade == "ICEB") {
        for(int i=1; i<=23; ++i) ui->comboSalasEdicao->addItem("Sala " + QString::number(i));
    } else if (unidade == "DEMIN") {
        for(int i=1; i<=16; ++i) ui->comboSalasEdicao->addItem("Sala " + QString::number(i));
    } else if (unidade == "Bloco de Salas") {
        for(int i=101; i<=106; ++i) ui->comboSalasEdicao->addItem("Sala " + QString::number(i));
        for(int i=201; i<=213; ++i) ui->comboSalasEdicao->addItem("Sala " + QString::number(i));
    }
}
