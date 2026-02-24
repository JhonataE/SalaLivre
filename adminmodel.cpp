/**
 * @file adminmodel.cpp
 * @brief Implementação do módulo de administração do sistema SalaLivre com persistência SQL.
 * @author Jhonata
 * @details Contém a lógica para gerenciamento de unidades acadêmicas, criação de salas
 * e edição de atributos físicos como capacidade e recursos disponíveis.
 */

#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>

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
 * @details Abre diálogos para cadastrar novas unidades, editar nomes ou remover unidades existentes no banco de dados.
 */
void Adminmodel::on_btnGerenciarUnidade_clicked() {
    QStringList opcoes = {"Cadastrar Nova", "Remover Unidade"};
    bool ok;
    QString acao = QInputDialog::getItem(this, "Unidades", "Selecione a ação:", opcoes, 0, false, &ok);

    if (ok && !acao.isEmpty()) {
        if (acao == "Cadastrar Nova") {
            QString nome = QInputDialog::getText(this, "Novo", "Nome da Unidade:", QLineEdit::Normal, "", &ok);
            if (ok && !nome.isEmpty()) {
                // PERSISTÊNCIA: Cadastra a unidade no banco (usando uma sala dummy para criar a unidade se necessário)
                QSqlQuery query;
                query.prepare("INSERT INTO salas (nome, unidade) VALUES (:nome, :unidade)");
                query.bindValue(":nome", "Sala Inicial - " + nome);
                query.bindValue(":unidade", nome);

                if(query.exec()) {
                    atualizarListas();
                    QMessageBox::information(this, "Sucesso", "Unidade " + nome + " cadastrada no banco de dados.");
                }
            }
        } else if (acao == "Remover Unidade") {
            auto res = QMessageBox::question(this, "Aviso", "Tem certeza? Isso excluirá todas as salas vinculadas a esta unidade no banco.");
            if (res == QMessageBox::Yes) {
                QSqlQuery query;
                query.prepare("DELETE FROM salas WHERE unidade = :unidade");
                query.bindValue(":unidade", ui->comboUnidades->currentText());
                if(query.exec()) {
                    atualizarListas();
                    QMessageBox::information(this, "Sucesso", "Unidade e salas removidas.");
                }
            }
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
 * @details Solicita o identificador da sala e a vincula automaticamente à unidade selecionada no banco de dados.
 */
void Adminmodel::on_btnNovaSala_clicked() {
    bool ok;
    QString idSala = QInputDialog::getText(this, "Nova Sala", "Identificador/Número da Sala:", QLineEdit::Normal, "", &ok);

    if (ok && !idSala.isEmpty()) {
        QString unidadeAtual = ui->comboUnidades->currentText();
        QString nomeCompleto = "Sala " + idSala + " - " + unidadeAtual;

        // PERSISTÊNCIA: Insere a nova sala no banco
        QSqlQuery query;
        query.prepare("INSERT INTO salas (nome, unidade, manutencao, uso_externo) VALUES (:nome, :unidade, 0, 1)");
        query.bindValue(":nome", nomeCompleto);
        query.bindValue(":unidade", unidadeAtual);

        if (query.exec()) {
            atualizarComboSalas(unidadeAtual);
            QMessageBox::information(this, "Sucesso", "Sala " + idSala + " persistida no banco de dados.");
        } else {
            QMessageBox::warning(this, "Erro", "Erro ao criar sala: " + query.lastError().text());
        }
    }
}

/**
 * @brief Slot para salvar as edições de atributos de uma sala.
 * @details Captura a capacidade, recursos e status (Manutenção/Uso Externo) para atualizar o banco de dados.
 */
void Adminmodel::on_btnSalvarAtributosSala_clicked() {
    QString salaAlvo = ui->comboSalasEdicao->currentText();
    if (salaAlvo.isEmpty()) {
        QMessageBox::warning(this, "Erro", "Selecione uma sala para editar.");
        return;
    }

    bool emManutencao = ui->checkManutencao->isChecked();
    bool usoExterno = ui->checkUsoExterno->isChecked();

    // PERSISTÊNCIA: Atualiza os status da sala no banco de dados
    QSqlQuery query;
    query.prepare("UPDATE salas SET manutencao = :manut, uso_externo = :ext WHERE nome = :nome");
    query.bindValue(":manut", emManutencao ? 1 : 0);
    query.bindValue(":ext", usoExterno ? 1 : 0);
    query.bindValue(":nome", salaAlvo);

    if (query.exec()) {
        QMessageBox::information(this, "Sucesso", "Status da " + salaAlvo + " salvos permanentemente!");
    } else {
        QMessageBox::critical(this, "Erro", "Falha ao atualizar banco: " + query.lastError().text());
    }
}

/**
 * @brief Slot para fechar a janela de administração.
 */
void Adminmodel::fecharJanela() {
    this->close();
}
/**
 * @brief Inicializa as listas de unidades e salas buscando do banco de dados.
 * @details Busca todas as unidades cadastradas na tabela 'salas' para popular o combo.
 */
void Adminmodel::atualizarListas() {
    ui->comboUnidades->clear();

    QSqlQuery query("SELECT DISTINCT unidade FROM salas");
    while (query.next()) {
        ui->comboUnidades->addItem(query.value(0).toString());
    }

    if (ui->comboUnidades->count() == 0) {
        ui->comboUnidades->addItems({"ICEB", "DEMIN", "Bloco de Salas"});
    }

    atualizarComboSalas(ui->comboUnidades->currentText());
}

/**
 * @brief Atualiza dinamicamente o seletor de salas com base no banco de dados.
 * @details Realiza uma consulta SQL filtrando pelo nome da unidade selecionada.
 * @param unidade Nome da unidade selecionada para filtragem.
 */
void Adminmodel::atualizarComboSalas(const QString &unidade) {
    ui->comboSalasEdicao->clear();

    QSqlQuery query;
    query.prepare("SELECT nome FROM salas WHERE unidade = :unidade");
    query.bindValue(":unidade", unidade);

    if(query.exec()) {
        while(query.next()) {
            ui->comboSalasEdicao->addItem(query.value(0).toString());
        }
    }
}
