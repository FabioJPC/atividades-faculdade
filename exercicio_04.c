/* Exercicio 04
Assuma que a variável x foi armazenada no endereço
2000. Sabendo que uma variável inteira ocupa 4 Bytes de
memória. Defina o que este bloco de código realiza e
determine os valores finais de x e px, depois de executar
estes comandos*/

#include <stdio.h>
int main(){
    int x, *px;
    x = 10;
    px = &x;
    *px *= 10;
    px += 2;
}
/*
Resposta: 
O valor final de x será 100 já quem em *px *= 10 a expressão acessa o valor para qual *px
aponta e o multiplica por 10, resultando em 100.

Já o valor de px em si é incrementado em duas posições de int (2 X 4 bytes), ou seja,
ele vai para, 2008

*/