#include <stdio.h>
#include <stdlib.h>

/*
Exercício 2
Com base nas instruções do programa C abaixo:
*/

int main(){
    int *px;

    int x[]= {10,7,2,6,3};
    px = x;
    printf("Valor de px: %d \n", *px);
    printf("%d \n", *(px+2));
    printf("%d \n", px[4]);
    printf("%d \n", px[1]);
    printf("%d \n", *(x+3));    

}
/*
Assinale Verdadeiro ou Falso:
a. *px é igual a 10             Verdadeiro
b. *(px + 2) é igual a 2        Verdadeiro
c. px[4] é igual a 3            Verdadeiro
d. px[1] é igual a 10           Falso
e. *(x + 3) é igual a 6         Verdadeiro
*/