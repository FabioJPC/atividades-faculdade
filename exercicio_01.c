#include <stdio.h>
#include <stdlib.h>

int main(){
    char c = 'A';
    char *pc1, *pc2, *pc3, *pc4;

    pc1 = &c;
    pc2 = pc1++;
    pc3 = pc2 + 4;
    pc4 = pc3 - 5;

    printf("pc1: %p, pc2: %p, pc3: %p, pc4: %p \n", pc1, pc2, pc3, pc4 );
    // Os endereços dos ponteiros serão:
    // pc1 = 1001       obs: seria 1000, mas é incrementado depois
    // pc2 = 1000       obs: copia o endereço de pc1 e depois pc1 é incrementado
    // pc3 = 1004
    // pc4 = 999
}