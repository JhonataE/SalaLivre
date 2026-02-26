#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(IUserService* service, QWidget *parent) :
    QDialog(parent), ui(new Ui::LoginDialog), m_service(service), m_isInstitucional(false)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0); // Começa na tela inicial (Acesso Externo)

    // Página 0 -> Página 1 (Login Externo)
    connect(ui->btnExterno, &QPushButton::clicked, this, &LoginDialog::irParaLoginExterno);

    // Página 1 -> Login ou Ir para Cadastro
    connect(ui->btnEntrar, &QPushButton::clicked, this, &LoginDialog::realizarLogin);

    // Ir para cadastro
    connect(ui->btnIrParaCadastro, &QPushButton::clicked, this, &LoginDialog::irParaCadastroExterno);

    // Página 2 -> Confirmar Cadastro e salvar no Service
    connect(ui->btnConfirmarCadastro, &QPushButton::clicked, this, &LoginDialog::realizarCadastro);
    connect(ui->btnInstitucional, &QPushButton::clicked, this, [this](){
        // Se a sua tela de Login Institucional for a 4ª página, o índice é 3
        ui->stackedWidget->setCurrentIndex(3);
    });
    connect(ui->pushButton, &QPushButton::clicked, this, &LoginDialog::realizarLoginInstitucional);

}
LoginDialog::~LoginDialog() {
    delete ui; // Garante a liberação da memória da interface
}
void LoginDialog::irParaLoginExterno() {
    m_isInstitucional = false;
    ui->stackedWidget->setCurrentIndex(1); // Muda para formulário de login por CPF
}

void LoginDialog::irParaCadastroExterno() {
    // Muda para a página onde estão os campos Nome, CPF, Email e Senha
    ui->stackedWidget->setCurrentIndex(2);
}

void LoginDialog::realizarCadastro() {
    // Usando os nomes exatos da sua imagem de componentes
    QString nome = ui->txtNomeCad->text();
    QString cpf = ui->txtCPFCad_2->text();
    QString email = ui->txtEmailCad->text();
    QString senha = ui->txtSenhaCad->text();

    if (cpf.isEmpty() || senha.isEmpty()) {
        QMessageBox::warning(this, "Erro", "CPF e Senha são obrigatórios para o cadastro.");
        return;
    }

    if (m_service->registerUser(cpf, senha, nome, email)) {
        QMessageBox::information(this, "Sucesso", "Cadastro realizado! Retornando ao início.");
        ui->stackedWidget->setCurrentIndex(0);
    } else {
        QMessageBox::warning(this, "Erro", "Não foi possível realizar o cadastro.");
    }
}
void LoginDialog::voltarParaInicio() {
    ui->stackedWidget->setCurrentIndex(0); // Retorna para a página inicial
}

void LoginDialog::realizarLogin() {
    // Ajustado para txtSenha_2 conforme sugerido pelo compilador
    QString usuario = ui->txtUser->text();
    QString senha = ui->txtSenha_2->text();

    if (m_service->login(usuario, senha)) {
        accept(); // Sucesso: fecha o diálogo
    } else {
        QMessageBox::warning(this, "Erro", "Credenciais inválidas.");
    }
}

/**
 * @brief Processa a autenticação para usuários internos da UFOP (Matrícula/SIAPE).
 * @details Valida as credenciais contra o UserService e fornece feedback específico
 * orientado ao suporte institucional (NTI) em caso de falha.
 */

void LoginDialog::realizarLoginInstitucional() {
    // Captura os dados da nova tela
    QString matricula = ui->txtMatriculaInst->text();
    QString senha = ui->txtSenhaInst->text();

    // O serviço valida se é Docente, Aluno ou Admin
    if (m_service->login(matricula, senha)) {
        // Recuperamos os dados para saber se é Admin
        UserData dados = m_service->getLoggedUserData();

        if (dados.role == "Admin") {
            this->done(2); // Retornamos um código personalizado (2) para identificar Admin
        } else {
            accept(); // Retorna o código padrão (1) para Alunos/Docentes
        }
    } else {
        QMessageBox::warning(this, "Erro", "Credenciais incorretas.");
    }
}
