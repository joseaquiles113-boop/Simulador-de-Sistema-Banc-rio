#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct conta{
    char nome[201];
    int senha;
    double saldo;
    struct conta *proximo;
}conta;

typedef struct{
    conta *inicio;
}Lista;

void cadastro(Lista *lista, const char *nome, int senha);
void deposito(Lista *lista, const char *nome, int senha, double saldo);
void saque(Lista *lista, const char *nome, int senha, double valor);
void transferencia(Lista *lista, const char *nome, int senha, double valor, const char *nomeR);
conta *login(Lista *lista, const char *nome, int senha);
void excluirConta(Lista *lista, const char *nome, int senha);
void limpar();
void liberarLista(Lista *lista);

int main(){
    Lista lista;

    lista.inicio = NULL;

    char nome[201];
    char nomeR[201];
    int senha, opcao;
    double valor;

    while(1){
        puts("\n--- BANCO CENTRAL ---\n");
        puts("1 - Cadastrar conta\n2 - Fazer login\n3 - Deposito\n4 - Saque\n5 - Realizar transferencia\n10 - Excluir conta\n0 - Sair do app");
        scanf("%d", &opcao);
        limpar();

        if(opcao == 1){

            system("cls");
            puts("Digite seu nome de usuario:");
            scanf("%200[^\n]", nome);
            puts("Crie uma senha:");
            scanf("%d", &senha);
            limpar();
            system("cls");
            cadastro(&lista, nome, senha);

        }else if(opcao == 2){

            system("cls");
            puts("Digite seu nome de usuario:");
            scanf("%200[^\n]", nome);
            limpar();
            puts("Digite sua senha:");
            scanf("%d", &senha);
            limpar();
            system("cls");
            login(&lista, nome, senha);

        }else if(opcao == 3){

            system("cls");
            puts("Digite seu nome de usuario:");
            scanf("%200[^\n]", nome);
            limpar();
            puts("Digite sua senha:");
            scanf("%d", &senha);
            limpar();
            puts("Digite o valor do deposito(R$):");
            scanf("%lf", &valor);
            limpar();
            deposito(&lista, nome, senha, valor);

        }else if(opcao == 4){

            system("cls");
            puts("Digite seu nome de usuario:");
            scanf("%200[^\n]", nome);
            limpar();
            puts("Digite sua senha:");
            scanf("%d", &senha);
            limpar();
            puts("Digite o valor do saque(R$):");
            scanf("%lf", &valor);
            limpar();
            saque(&lista, nome, senha, valor);

        }else if(opcao == 5){

            system("cls");
            puts("Digite seu nome de usuario:");
            scanf("%200[^\n]", nome);
            limpar();
            puts("Digite sua senha:");
            scanf("%d", &senha);
            limpar();
            puts("Digite o nome de quem ira receber a transferencia:");
            scanf("%200[^\n]", nomeR);
            limpar();
            puts("Digite o valor da transferencia(R$):");
            scanf("%lf", &valor);
            limpar();
            transferencia(&lista, nome, senha, valor, nomeR);

        }else if(opcao == 10){

            system("cls");
            puts("Digite seu nome de usuario:");
            scanf("%200[^\n]", nome);
            limpar();
            puts("Digite sua senha:");
            scanf("%d", &senha);
            limpar();
            excluirConta(&lista, nome, senha);

        }else if(opcao == 0){

            break;

        }else{

            system("cls");
            puts("Opcao invalida!");

        }
    }

    liberarLista(&lista);

    return 0;
}

void cadastro(Lista *lista, const char *nome, int senha){
    conta *nova = (conta*)malloc(sizeof(conta));
    conta *verificacao = lista->inicio;

    if(nova == NULL)return;

    while(verificacao != NULL && (strcmp(verificacao->nome, nome)) != 0){
        verificacao = verificacao->proximo;
    }if(verificacao != NULL){
        free(nova);
        puts("Esse nome ja esta em uso");
    }else{
        strncpy(nova->nome, nome, sizeof(nova->nome) - 1);
        nova->nome[sizeof(nova->nome) - 1] = '\0';

        nova->senha = senha;
        nova->saldo = 0;
        nova->proximo = lista->inicio;
        lista->inicio = nova;
    
        puts("Cadastro realizado com sucesso!");
    }
}

void deposito(Lista *lista, const char *nome, int senha, double valor){
    conta *atual = lista->inicio;

    while(atual != NULL && ((strcmp(atual->nome, nome)) != 0 || atual->senha != senha)){
        atual = atual->proximo;
    }if(atual == NULL || (strcmp(atual->nome, nome)) != 0 || atual->senha != senha){
        puts("Seu nome ou senha esta(ao) incorreto(s)");
    }else{
        if(valor > 50000){
            puts("Valor maximo de deposito excedido!");
        }else if(valor <= 0){
            puts("Nao e possivel depositar um valor negativo ou igual a zero!");
        }else{
            atual->saldo += valor;
            puts("Saldo depositado na conta!");
        }
    }
}

void saque(Lista *lista, const char *nome, int senha, double valor){
    conta *atual = lista->inicio;

    while(atual != NULL && ((strcmp(atual->nome, nome)) != 0 || atual->senha != senha)){
        atual = atual->proximo;
    }if(atual == NULL || (strcmp(atual->nome, nome)) != 0 || atual->senha != senha){
        puts("Seu nome ou senha esta(ao) incorreto(s)");
    }else{
        if(valor > 30000){
            puts("Valor maximo de saque excedido!");
        }else if(valor <= 0){
            puts("Nao e possivel retirar um valor negativo ou igual a zero!");
        }else{
            if(atual->saldo < valor){
                puts("Nao e possivel retirar um valor alem do saldo disponivel!");
            }else{
                atual->saldo -= valor;
                puts("Saque realizado!");
            }
        }
    }
}

void transferencia(Lista *lista, const char *nome, int senha, double valor, const char *nomeR){
    conta *atual = lista->inicio;
    conta *atualR = lista->inicio;

    while(atual != NULL && ((strcmp(atual->nome, nome)) != 0 || atual->senha != senha)){
        atual = atual->proximo;
    }if(atual == NULL || (strcmp(atual->nome, nome)) != 0 || atual->senha != senha){
        puts("Seu nome ou senha esta(ao) incorreto(s)");
    }else{
        if(valor > 80000){
            puts("Valor maximo de transferencia excedido!");
        }else{
            while(atualR != NULL && (strcmp(atualR->nome, nomeR)) != 0){
                atualR = atualR->proximo;
            }if(atualR == NULL || (strcmp(atualR->nome, nomeR)) != 0){
                puts("Nome incorreto");
            }else{
                if((strcmp(atual->nome, atualR->nome)) == 0){
                    puts("Nao e possivel enviar um valor para si proprio");
                }else{
                    if(valor <= 0){
                        puts("Nao e possivel transferir um valor negativo ou igual a zero!");
                    }else if(atual->saldo < valor){
                        puts("Nao e possivel transferir um valor alem do saldo disponivel!");
                    }else{
                        atual->saldo -= valor;
                        atualR->saldo += valor;
                        puts("Transferencia realizada!");
                    }
                }
            }
        }
    }
}

conta *login(Lista *lista, const char *nome, int senha){
    conta *proximo = lista->inicio;

    while(proximo != NULL && ((strcmp(proximo->nome, nome)) != 0 || proximo->senha != senha)){
        proximo = proximo->proximo;
    }if(proximo == NULL || (strcmp(proximo->nome, nome)) != 0 || proximo->senha != senha){
        puts("Seu nome ou senha esta(ao) incorreto(s)");
    }else{
        printf("Bem vindo(a), %s!\nSaldo: R$%.2f", proximo->nome, proximo->saldo);
    }

    return proximo;
}

void excluirConta(Lista *lista, const char *nome, int senha){
    conta *contaExcluir = NULL;
    conta *inicio = lista->inicio;

    if(inicio != NULL && (strcmp(inicio->nome, nome)) == 0 && inicio->senha == senha){
        contaExcluir = lista->inicio;
        lista->inicio = contaExcluir->proximo;
    }else{
        while(inicio != NULL && inicio->proximo != NULL && ((strcmp(inicio->proximo->nome, nome)) != 0 || inicio->proximo->senha != senha)){
            inicio = inicio->proximo;
        }if(inicio != NULL && inicio->proximo != NULL && (strcmp(inicio->proximo->nome, nome)) == 0 && inicio->proximo->senha == senha){
            contaExcluir = inicio->proximo;
            inicio->proximo = contaExcluir->proximo;
        }else{
            puts("Seu nome ou senha esta(ao) incorreto(s)");
        }
    }

    if(contaExcluir != NULL){
        free(contaExcluir);
        puts("Conta excluida");
    }
}

void limpar(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void liberarLista(Lista *lista){
    conta *atual = lista->inicio;

    while(atual != NULL) {
        conta *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    lista->inicio = NULL;
}