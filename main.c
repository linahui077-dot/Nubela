#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// 1. ESTRUTURA DO INVESTIDOR


struct Investidor {
    char nome[200];
    char cpf[12];
    char senha[7];
};

void limparBuffer() {

    int caractere;

    while ((caractere = getchar()) != '\n' &&
           caractere != EOF) {
    }
}

// Remover quebra de linha
void removerEnter(char texto[]) {

    int i;

    for (i = 0; texto[i] != '\0'; i++) {

        if (texto[i] == '\n') {
            texto[i] = '\0';
            break;
        }
    }
}

// Ler texto permitindo espacos
void lerLinha(char texto[], int tamanho) {

    if (fgets(texto, tamanho, stdin) != NULL) {

        int i;
        int encontrouEnter = 0;

        for (i = 0; texto[i] != '\0'; i++) {

            if (texto[i] == '\n') {
                texto[i] = '\0';
                encontrouEnter = 1;
                break;
            }
        }

        if (encontrouEnter == 0) {
            limparBuffer();
        }
    }
}

// Ler numero inteiro
int lerInteiro() {

    int valor;

    if (scanf("%d", &valor) != 1) {

        limparBuffer();
        return -1;
    }

    limparBuffer();

    return valor;
}

// Ler numero decimal
float lerValor() {

    float valor;

    if (scanf("%f", &valor) != 1) {

        limparBuffer();
        return -1;
    }

    limparBuffer();

    return valor;
}

// Verificar se possui somente numeros
int somenteNumeros(char texto[]) {

    int i;

    if (strlen(texto) == 0) {
        return 0;
    }

    for (i = 0; texto[i] != '\0'; i++) {

        if (texto[i] < '0' || texto[i] > '9') {
            return 0;
        }
    }

    return 1;
}


// ==========================================
// 3. CADASTRO E LOGIN
// ==========================================

// Verificar CPF existente
int cpfExiste(char cpf[]) {

    FILE *arquivo;

    char nome[200];
    char cpfArquivo[100];
    char senha[100];

    arquivo = fopen("usuarios.txt", "r");

    if (arquivo == NULL) {
        return 0;
    }

    while (fgets(nome, 200, arquivo) != NULL) {

        if (fgets(cpfArquivo, 100, arquivo) == NULL) {
            break;
        }

        if (fgets(senha, 100, arquivo) == NULL) {
            break;
        }

        removerEnter(cpfArquivo);

        if (strcmp(cpf, cpfArquivo) == 0) {

            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);

    return 0;
}

// Buscar usuario cadastrado
int buscarUsuario(char cpf[], char nomeEncontrado[],
                  char senhaEncontrada[]) {

    FILE *arquivo;

    char nome[200];
    char cpfArquivo[100];
    char senha[100];

    arquivo = fopen("usuarios.txt", "r");

    if (arquivo == NULL) {
        return 0;
    }

    while (fgets(nome, 200, arquivo) != NULL) {

        if (fgets(cpfArquivo, 100, arquivo) == NULL) {
            break;
        }

        if (fgets(senha, 100, arquivo) == NULL) {
            break;
        }

        removerEnter(nome);
        removerEnter(cpfArquivo);
        removerEnter(senha);

        if (strcmp(cpf, cpfArquivo) == 0) {

            strcpy(nomeEncontrado, nome);
            strcpy(senhaEncontrada, senha);

            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);

    return 0;
}

// ==========================================
// 4. CARTEIRA DO USUARIO
// ==========================================

// Criar nome do arquivo individual
void nomeCarteira(char cpf[], char nomeArquivo[]) {

    sprintf(nomeArquivo, "carteira_%s.txt", cpf);
}

// Salvar carteira
void salvarCarteira(char cpf[], float real,
                    float btc, float eth, float xrp) {

    FILE *arquivo;

    char nomeArquivo[50];

    nomeCarteira(cpf, nomeArquivo);

    arquivo = fopen(nomeArquivo, "w");

    if (arquivo != NULL) {

        fprintf(arquivo, "%.2f %.8f %.8f %.8f\n",
                real, btc, eth, xrp);

        fclose(arquivo);
    }

    else {

        printf("Erro ao salvar a carteira!\n");
    }
}

// Carregar carteira
void carregarCarteira(char cpf[], float *real,
                      float *btc, float *eth, float *xrp) {

    FILE *arquivo;

    char nomeArquivo[50];

    nomeCarteira(cpf, nomeArquivo);

    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {

        *real = 0;
        *btc = 0;
        *eth = 0;
        *xrp = 0;

        salvarCarteira(cpf, *real, *btc, *eth, *xrp);
    }

    else {

        if (fscanf(arquivo, "%f %f %f %f",
                   real, btc, eth, xrp) != 4) {

            *real = 0;
            *btc = 0;
            *eth = 0;
            *xrp = 0;
        }

        fclose(arquivo);
    }
}


// ==========================================
// 5. COTACOES DAS CRIPTOMOEDAS
// ==========================================

// Salvar cotacoes
void salvarCotacoes(float btc, float eth, float xrp) {

    FILE *arquivo;

    arquivo = fopen("cotacoes.txt", "w");

    if (arquivo != NULL) {

        fprintf(arquivo, "%.2f %.2f %.4f\n",
                btc, eth, xrp);

        fclose(arquivo);
    }

    else {

        printf("Erro ao salvar cotacoes!\n");
    }
}

// Carregar cotacoes
void carregarCotacoes(float *btc, float *eth, float *xrp) {

    FILE *arquivo;

    arquivo = fopen("cotacoes.txt", "r");

    if (arquivo == NULL) {

        *btc = 350000.00;
        *eth = 12000.00;
        *xrp = 2.50;

        salvarCotacoes(*btc, *eth, *xrp);
    }

    else {

        if (fscanf(arquivo, "%f %f %f",
                   btc, eth, xrp) != 3) {

            *btc = 350000.00;
            *eth = 12000.00;
            *xrp = 2.50;
        }

        fclose(arquivo);
    }
}

// Mostrar cotacoes
void mostrarCotacoes(float btc, float eth, float xrp) {

    printf("\n========== COTACOES ==========\n");

    printf("1. Bitcoin:  R$ %.2f\n", btc);
    printf("2. Ethereum: R$ %.2f\n", eth);
    printf("3. Ripple:   R$ %.4f\n", xrp);

    printf("==============================\n");
}

// Atualizar cotacoes
void atualizarCotacoes(float *btc, float *eth, float *xrp) {

    float variacao;

    // Bitcoin
    variacao = (rand() % 1001 - 500) / 10000.0;
    *btc = *btc * (1 + variacao);

    // Ethereum
    variacao = (rand() % 1001 - 500) / 10000.0;
    *eth = *eth * (1 + variacao);

    // Ripple
    variacao = (rand() % 1001 - 500) / 10000.0;
    *xrp = *xrp * (1 + variacao);

    salvarCotacoes(*btc, *eth, *xrp);
}

// ==========================================
// 6. EXTRATO
// ==========================================

// Criar nome do arquivo de extrato
void nomeExtrato(char cpf[], char nomeArquivo[]) {

    sprintf(nomeArquivo, "extrato_%s.txt", cpf);
}

// Registrar operacao
void registrarExtrato(char cpf[], char operacao[],
                      float valor, float cotacao, float taxa,
                      float real, float btc, float eth, float xrp) {

    FILE *arquivo;

    char nomeArquivo[50];

    nomeExtrato(cpf, nomeArquivo);

    arquivo = fopen(nomeArquivo, "a");

    if (arquivo != NULL) {

        fprintf(arquivo,
                "%s | Valor: %.4f | Cotacao: %.4f | Taxa: %.2f%% | BRL: %.2f | BTC: %.8f | ETH: %.8f | XRP: %.8f\n",
                operacao, valor, cotacao, taxa,
                real, btc, eth, xrp);

        fclose(arquivo);
    }

    else {

        printf("Erro ao registrar operacao!\n");
    }
}

// Consultar extrato
void consultarExtrato(char cpf[]) {

    FILE *arquivo;

    char nomeArquivo[50];
    char linha[400];

    nomeExtrato(cpf, nomeArquivo);

    arquivo = fopen(nomeArquivo, "r");

    printf("\n========== EXTRATO ==========\n");

    if (arquivo == NULL) {

        printf("Nenhuma operacao realizada.\n");
    }

    else {

        while (fgets(linha, 400, arquivo) != NULL) {

            printf("%s", linha);
        }

        fclose(arquivo);
    }

    printf("\n=============================\n");
}


// ==========================================
// 7. CONSULTAR SALDO
// ==========================================

void consultarSaldo(char cpf[], char nome[],
                    float real, float btc,
                    float eth, float xrp) {

    printf("\n========== CARTEIRA ==========\n");

    printf("Nome: %s\n", nome);
    printf("CPF: %s\n", cpf);

    printf("\nReais: R$ %.2f\n", real);
    printf("Bitcoin: %.8f BTC\n", btc);
    printf("Ethereum: %.8f ETH\n", eth);
    printf("Ripple: %.8f XRP\n", xrp);

    printf("==============================\n");
}

// ==========================================
// 8. CONFIRMAR SENHA
// ==========================================

int confirmarSenha(char senhaCorreta[]) {

    char senhaDigitada[100];

    printf("\nDigite sua senha de 6 digitos: ");

    lerLinha(senhaDigitada, 100);

    if (strcmp(senhaDigitada, senhaCorreta) == 0) {

        return 1;
    }

    printf("Senha incorreta!\n");

    return 0;
}

// ==========================================
// 9. PROGRAMA PRINCIPAL
// ==========================================

int main() {

    struct Investidor novoUsuario;

    FILE *arquivo;

    char cpfDigitado[100];
    char senhaDigitada[100];
    char senhaCorreta[100];
    char nomeUsuario[200];
    char operacao[30];

    float saldoReal;
    float saldoBitcoin;
    float saldoEthereum;
    float saldoRipple;

    float cotacaoBTC;
    float cotacaoETH;
    float cotacaoXRP;

    float valor;
    float quantidade;
    float taxa;
    float valorTaxa;
    float valorLiquido;
    float cotacaoEscolhida;
    float saldoMoeda;

    int opcao;
    int opcaoMenu;
    int acesso;
    int cpfValido;
    int senhaValida;
    int cpfEncontrado;
    int moeda;

    srand(time(NULL));

    carregarCotacoes(&cotacaoBTC, &cotacaoETH, &cotacaoXRP);

    do {

        printf("\n");
        printf("====================================\n");
        printf("          N E B U L A\n");
        printf("        CRYPTO EXCHANGE\n");
        printf("====================================\n");

        printf("1. Criar conta\n");
        printf("2. Fazer login\n");
        printf("3. Sair\n");

        printf("------------------------------------\n");
        printf("Escolha uma opcao: ");

        opcao = lerInteiro();

        switch (opcao) {

            // =================================
            // CADASTRO
            // =================================

            case 1:

                printf("\n========== CADASTRO ==========\n");

                printf("Digite seu nome completo: ");
                lerLinha(novoUsuario.nome, 200);

                if (strlen(novoUsuario.nome) == 0) {

                    printf("Nome invalido!\n");
                    break;
                }

                printf("Digite seu CPF (11 numeros): ");
                lerLinha(cpfDigitado, 100);

                cpfValido = 1;

                if (strlen(cpfDigitado) < 11) {

                    printf("CPF incompleto! Digite 11 numeros.\n");
                    cpfValido = 0;
                }

                else if (strlen(cpfDigitado) > 11) {

                    printf("CPF invalido! Excesso de numeros.\n");
                    cpfValido = 0;
                }

                if (somenteNumeros(cpfDigitado) == 0) {

                    printf("CPF invalido! Use somente numeros.\n");
                    cpfValido = 0;
                }

                if (cpfValido == 0) {
                    break;
                }

                strcpy(novoUsuario.cpf, cpfDigitado);

                cpfEncontrado = cpfExiste(novoUsuario.cpf);

                if (cpfEncontrado == 1) {

                    printf("Este CPF ja esta cadastrado!\n");
                    break;
                }

                printf("Crie uma senha de 6 digitos: ");
                lerLinha(senhaDigitada, 100);

                senhaValida = 1;

                if (strlen(senhaDigitada) != 6) {

                    printf("A senha deve ter exatamente 6 numeros!\n");
                    senhaValida = 0;
                }

                if (somenteNumeros(senhaDigitada) == 0) {

                    printf("A senha deve conter somente numeros!\n");
                    senhaValida = 0;
                }

                if (senhaValida == 0) {
                    break;
                }

                strcpy(novoUsuario.senha, senhaDigitada);

                arquivo = fopen("usuarios.txt", "a");

                if (arquivo != NULL) {

                    fprintf(arquivo, "%s\n", novoUsuario.nome);
                    fprintf(arquivo, "%s\n", novoUsuario.cpf);
                    fprintf(arquivo, "%s\n", novoUsuario.senha);

                    fclose(arquivo);

                    saldoReal = 0;
                    saldoBitcoin = 0;
                    saldoEthereum = 0;
                    saldoRipple = 0;

                    salvarCarteira(novoUsuario.cpf,
                                   saldoReal,
                                   saldoBitcoin,
                                   saldoEthereum,
                                   saldoRipple);

                    printf("\nCadastro realizado com sucesso!\n");
                    printf("Bem-vindo(a), %s!\n", novoUsuario.nome);
                }

                else {

                    printf("Erro ao salvar o cadastro!\n");
                }

                break;

            // =================================
            // LOGIN
            // =================================

            case 2:

                printf("\n========== LOGIN ==========\n");

                printf("Digite seu CPF: ");
                lerLinha(cpfDigitado, 100);

                printf("Digite sua senha: ");
                lerLinha(senhaDigitada, 100);

                cpfValido = 1;
                senhaValida = 1;

                if (strlen(cpfDigitado) != 11 ||
                    somenteNumeros(cpfDigitado) == 0) {

                    cpfValido = 0;
                }

                if (strlen(senhaDigitada) != 6 ||
                    somenteNumeros(senhaDigitada) == 0) {

                    senhaValida = 0;
                }

                if (cpfValido == 0 || senhaValida == 0) {

                    printf("CPF ou senha com formato invalido!\n");
                    break;
                }

                acesso = buscarUsuario(cpfDigitado,
                                       nomeUsuario,
                                       senhaCorreta);

                if (acesso == 0) {

                    printf("Usuario nao encontrado!\n");
                    break;
                }

                if (strcmp(senhaDigitada, senhaCorreta) != 0) {

                    printf("Senha incorreta!\n");
                    break;
                }

                printf("\nLogin realizado com sucesso!\n");
                printf("Bem-vindo(a), %s!\n", nomeUsuario);

                carregarCarteira(cpfDigitado,
                                 &saldoReal,
                                 &saldoBitcoin,
                                 &saldoEthereum,
                                 &saldoRipple);

                // MENU PRINCIPAL

                do {

                    printf("\n");
                    printf("====================================\n");
                    printf("          N E B U L A\n");
                    printf("        CRYPTO EXCHANGE\n");
                    printf("====================================\n");

                    printf("1. Consultar saldo\n");
                    printf("2. Consultar extrato\n");
                    printf("3. Depositar reais\n");
                    printf("4. Sacar reais\n");
                    printf("5. Comprar criptomoedas\n");
                    printf("6. Vender criptomoedas\n");
                    printf("7. Atualizar cotacao\n");
                    printf("8. Sair\n");

                    printf("------------------------------------\n");
                    printf("Escolha uma opcao: ");

                    opcaoMenu = lerInteiro();

                    switch (opcaoMenu) {
                    	
                    	
// CONSULTAR SALDO
case 1:

    if (confirmarSenha(senhaCorreta) == 1) {

        consultarSaldo(cpfDigitado,
                       nomeUsuario,
                       saldoReal,
                       saldoBitcoin,
                       saldoEthereum,
                       saldoRipple);
    }

    break;

// CONSULTAR EXTRATO
case 2:

    if (confirmarSenha(senhaCorreta) == 1) {

        consultarExtrato(cpfDigitado);
    }

    break;

// DEPOSITAR REAIS
case 3:

    printf("\n========== DEPOSITO ==========\n");

    printf("Digite o valor do deposito: R$ ");

    valor = lerValor();

    if (valor <= 0) {

        printf("Valor invalido!\n");
        break;
    }

    saldoReal = saldoReal + valor;

    salvarCarteira(cpfDigitado,
                   saldoReal,
                   saldoBitcoin,
                   saldoEthereum,
                   saldoRipple);

    registrarExtrato(cpfDigitado,
                     "DEPOSITO",
                     valor, 0, 0,
                     saldoReal,
                     saldoBitcoin,
                     saldoEthereum,
                     saldoRipple);

    printf("Deposito realizado!\n");

    consultarSaldo(cpfDigitado,
                   nomeUsuario,
                   saldoReal,
                   saldoBitcoin,
                   saldoEthereum,
                   saldoRipple);

    break;

// SACAR REAIS
case 4:

    printf("\n========== SAQUE ==========\n");

    printf("Digite o valor do saque: R$ ");

    valor = lerValor();

    if (valor <= 0) {

        printf("Valor invalido!\n");
        break;
    }

    if (valor > saldoReal) {

        printf("Saldo insuficiente!\n");
        break;
    }

    saldoReal = saldoReal - valor;

    salvarCarteira(cpfDigitado,
                   saldoReal,
                   saldoBitcoin,
                   saldoEthereum,
                   saldoRipple);

    registrarExtrato(cpfDigitado,
                     "SAQUE",
                     valor, 0, 0,
                     saldoReal,
                     saldoBitcoin,
                     saldoEthereum,
                     saldoRipple);

    printf("Saque realizado!\n");

    consultarSaldo(cpfDigitado,
                   nomeUsuario,
                   saldoReal,
                   saldoBitcoin,
                   saldoEthereum,
                   saldoRipple);

    break;

// COMPRAR CRIPTOMOEDAS
case 5:

    if (confirmarSenha(senhaCorreta) == 0) {
        break;
    }

    mostrarCotacoes(cotacaoBTC,
                    cotacaoETH,
                    cotacaoXRP);

    printf("Escolha a criptomoeda: ");

    moeda = lerInteiro();

    if (moeda == 1) {

        cotacaoEscolhida = cotacaoBTC;
        taxa = 2;
        saldoMoeda = saldoBitcoin;
        strcpy(operacao, "COMPRA BTC");
    }

    else if (moeda == 2) {

        cotacaoEscolhida = cotacaoETH;
        taxa = 1;
        saldoMoeda = saldoEthereum;
        strcpy(operacao, "COMPRA ETH");
    }

    else if (moeda == 3) {

        cotacaoEscolhida = cotacaoXRP;
        taxa = 1;
        saldoMoeda = saldoRipple;
        strcpy(operacao, "COMPRA XRP");
    }

    else {

        printf("Opcao invalida!\n");
        break;
    }

    printf("Quanto deseja investir em reais? R$ ");

    valor = lerValor();

    if (valor <= 0) {

        printf("Valor invalido!\n");
        break;
    }

    if (valor > saldoReal) {

        printf("Saldo insuficiente!\n");
        break;
    }

    valorTaxa = valor * taxa / 100;

    valorLiquido = valor - valorTaxa;

    quantidade = valorLiquido / cotacaoEscolhida;

    saldoReal = saldoReal - valor;

    saldoMoeda = saldoMoeda + quantidade;

    if (moeda == 1) {
        saldoBitcoin = saldoMoeda;
    }

    else if (moeda == 2) {
        saldoEthereum = saldoMoeda;
    }

    else {
        saldoRipple = saldoMoeda;
    }

    salvarCarteira(cpfDigitado,
                   saldoReal,
                   saldoBitcoin,
                   saldoEthereum,
                   saldoRipple);

    registrarExtrato(cpfDigitado,
                     operacao,
                     quantidade,
                     cotacaoEscolhida,
                     taxa,
                     saldoReal,
                     saldoBitcoin,
                     saldoEthereum,
                     saldoRipple);

    printf("\nCompra realizada com sucesso!\n");
    printf("Taxa: R$ %.2f\n", valorTaxa);
    printf("Quantidade recebida: %.8f\n", quantidade);

    consultarSaldo(cpfDigitado,
                   nomeUsuario,
                   saldoReal,
                   saldoBitcoin,
                   saldoEthereum,
                   saldoRipple);

    break;

// VENDER CRIPTOMOEDAS
case 6:

    if (confirmarSenha(senhaCorreta) == 0) {
        break;
    }

    mostrarCotacoes(cotacaoBTC,
                    cotacaoETH,
                    cotacaoXRP);

    printf("Escolha a criptomoeda: ");

    moeda = lerInteiro();

    if (moeda == 1) {

        cotacaoEscolhida = cotacaoBTC;
        taxa = 3;
        saldoMoeda = saldoBitcoin;
        strcpy(operacao, "VENDA BTC");
    }

    else if (moeda == 2) {

        cotacaoEscolhida = cotacaoETH;
        taxa = 2;
        saldoMoeda = saldoEthereum;
        strcpy(operacao, "VENDA ETH");
    }

    else if (moeda == 3) {

        cotacaoEscolhida = cotacaoXRP;
        taxa = 1;
        saldoMoeda = saldoRipple;
        strcpy(operacao, "VENDA XRP");
    }

    else {

        printf("Opcao invalida!\n");
        break;
    }

    printf("Digite a quantidade que deseja vender: ");

    quantidade = lerValor();

    if (quantidade <= 0) {

        printf("Quantidade invalida!\n");
        break;
    }

    if (quantidade > saldoMoeda) {

        printf("Quantidade insuficiente!\n");
        break;
    }

    valor = quantidade * cotacaoEscolhida;

    valorTaxa = valor * taxa / 100;

    valorLiquido = valor - valorTaxa;

    saldoReal = saldoReal + valorLiquido;

    saldoMoeda = saldoMoeda - quantidade;

    if (moeda == 1) {
        saldoBitcoin = saldoMoeda;
    }

    else if (moeda == 2) {
        saldoEthereum = saldoMoeda;
    }

    else {
        saldoRipple = saldoMoeda;
    }

    salvarCarteira(cpfDigitado,
                   saldoReal,
                   saldoBitcoin,
                   saldoEthereum,
                   saldoRipple);

    registrarExtrato(cpfDigitado,
                     operacao,
                     quantidade,
                     cotacaoEscolhida,
                     taxa,
                     saldoReal,
                     saldoBitcoin,
                     saldoEthereum,
                     saldoRipple);

    printf("\nVenda realizada com sucesso!\n");
    printf("Valor bruto: R$ %.2f\n", valor);
    printf("Taxa: R$ %.2f\n", valorTaxa);
    printf("Valor recebido: R$ %.2f\n", valorLiquido);

    consultarSaldo(cpfDigitado,
                   nomeUsuario,
                   saldoReal,
                   saldoBitcoin,
                   saldoEthereum,
                   saldoRipple);

    break;

// ATUALIZAR COTACOES
case 7:

    atualizarCotacoes(&cotacaoBTC,
                      &cotacaoETH,
                      &cotacaoXRP);

    printf("\nCotacoes atualizadas!\n");

    mostrarCotacoes(cotacaoBTC,
                    cotacaoETH,
                    cotacaoXRP);

    break;

// SAIR DA CARTEIRA
case 8:

    printf("\nSaindo da carteira...\n");
    break;

default:

    printf("Opcao invalida!\n");

}

} while (opcaoMenu != 8);

break;

// SAIR DO PROGRAMA
case 3:

    printf("\nObrigado por utilizar a NEBULA!\n");
    break;

default:

    printf("Opcao invalida!\n");

}

} while (opcao != 3);

return 0;

}



