/*
Escreva um programa que imprima um array de inteiros
na ordem inversa endereçando os elementos por meio de
um ponteiro.
*/

#include <stdio.h>
int main(){

    int vector[] = {10,20,30,40,50};
    int int_size = sizeof(vector[0]);

    int size = sizeof(vector) / int_size;
    
    int *pointer = vector + size -1;
    int *start = vector;

    while(pointer >= start){
        printf("Numero: %d e endereço: %p \n", *pointer, pointer);
        pointer--;
    }
}