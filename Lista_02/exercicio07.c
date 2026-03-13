#include <stdio.h>

typedef struct{
    char nome[100];
    int tempoPreparoMinutos;
    int porcoes;
}Receita;

void preencheReceita(Receita *receita){
    printf("----Criar nova receita----\n");
    printf("Nome da receita: ");
    scanf(" %99[^\n]%*c", &receita->nome);
    printf("Tempo de preparo: ");
    scanf("%d", &receita->tempoPreparoMinutos);
    printf("Qtde de porções: ");
    scanf("%d", &receita->porcoes);
}

void imprimeReceita(Receita receita){
    printf("\n----Exibindo receita----\n");
    printf("Nome: %s\n", receita.nome);
    printf("Tempo de preparo: %d\n", receita.tempoPreparoMinutos);
    printf("Serve %d porções\n", receita.porcoes);
}

void ajustaPorcoes(Receita *receita, int novoNumPorcoes){
    receita->porcoes = novoNumPorcoes;
}

int main(){
    Receita receita;
    int novoPorcoes;
    preencheReceita(&receita);
    imprimeReceita(receita);
    printf("\nDigite o novo número de porções: ");
    scanf("%d", &novoPorcoes);
    ajustaPorcoes(&receita, novoPorcoes);
    printf("\nReceita após ajuste:\n");
    imprimeReceita(receita);
}