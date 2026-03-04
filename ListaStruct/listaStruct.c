#include <stdio.h>
#include <string.h>
// 1 – Crie uma struct para controlar ações de uma bolsa de valores com as seuigntes informações:
typedef struct{
    char name[100];
    char sector[60];
    double valorAtual;
    double valorAnterior;
    double variacao;
} Company;

// 2- Faça um programa que:
//a) Preencha os campos da struct do exercício anterior
void preencherDados(Company *company){
    strcpy(company->name, "Embraer");
    strcpy(company->sector, "Aviação");
    company->valorAtual = 45.5;
    company->valorAnterior = 35.62;
    double temp = ((company->valorAtual - company->valorAnterior)/company->valorAnterior) *100;
    company->variacao = temp;
}

void preencherManual(Company *company){
    printf("\nDigite o nome da companhia: ");
    scanf(" %100[^\n]",company->name);

    printf("\nDigite o setor da companhia: ");
    scanf(" %60[^\n]",company->sector);

    printf("\nDigite o valor atual das ações: ");
    scanf(" %lf", &company->valorAtual);

    printf("\nDigite o valor anterior das ações: ");
    scanf(" %lf", &company->valorAnterior);
    double temp = ((company->valorAtual - company->valorAnterior)/company->valorAnterior) *100;
    company->variacao = temp;
}

void imprimirDados(Company *company){
    printf("\nNome da empresa: %s\n", &company->name);
    printf("Setor da empresa: %s\n", &company->sector);
    printf("Valor das açoes:\nHoje: %.1f     \nOntem:%.1f\n", company->valorAtual, company->valorAnterior);
    printf("Variação: %.2f\n", company->variacao);
}

void main(){
    
    Company company1;
    Company company2;
    preencherDados(&company1);

    //b) Imprima os campos da struct do exercicio anterior
    
    imprimirDados(&company1);
    
    //c) Com um laço, preencha 3 structs (vetor de structs)
    const int vectorSize= 3;
    Company companyVector[vectorSize];
    for(int i=0; i<vectorSize; i++){
        printf("--------Cadastrar novos dados----------\n");
        preencherManual(&companyVector[i]);
    }
    for(int i=0; i<vectorSize; i++){
        printf("Empresa %d \n", i);
        imprimirDados(&companyVector[i]);
    }

}