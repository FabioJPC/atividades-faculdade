/* Exercicio 03
No bloco de código abaixo, conseguimos efetuar a leitura do
valor de saldo?]
*/

#include <stdio.h>
int main(){
    float saldo;
    float *Psaldo;
    
    Psaldo = &saldo;
    scanf("%f", Psaldo);
    printf("%f", saldo);
}

/*
Resposta: Sim pé possivel fazer a leitura de saldo pois o ponteiro PSaldo armazena
seu endereço e a função scanf quando faz a leitura recebe esse endereço e guarda o valor lá
*/