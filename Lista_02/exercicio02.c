#include <stdio.h>

typedef struct{
    char nome[150];
    char endereco[150];
    int idade;
}Pessoa;

void preenchePessoa(Pessoa *p){
    char buffer[50];
    printf("\n--------Nova Pessoa--------\n");
    printf("\nDigite o nome: ");
    scanf(" %149[^\n]%*c", p->nome);

    printf("\nDigite a idade: ");
    scanf("%d", &p->idade);

    printf("\nDigite o endereço: ");
    scanf(" %149[^\n]%*c", p->endereco);
}

void exibePessoa(Pessoa pessoa){
    printf("\n------Exibindo dados da pessoa-----\n");
    printf("\nNome: %s", pessoa.nome);
    printf("\nIdade: %d", pessoa.idade);
    printf("\nEndereço: %s", pessoa.endereco);
}

int main(){
    Pessoa pessoa1;
    preenchePessoa(&pessoa1);
    exibePessoa(pessoa1);

    Pessoa vetorPessoas[5];
    int size = 5;

    printf("\n-----Cadastrando pessoas-----\n");
    for(int i=0; i<size; i++){
        preenchePessoa(&vetorPessoas[i]);
    }

    printf("\n-----Exibindo pessoas-----\n");
    for(int i=0; i<size; i++){
        exibePessoa(vetorPessoas[i]);
    }
}