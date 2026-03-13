#include <stdio.h>
#include <math.h>

typedef struct {
    float x, y;    
}Ponto2D;

Ponto2D criaPonto(float x, float y){
    Ponto2D ponto;
    ponto.x = x;
    ponto.y = y;
    return ponto;
}

void movePonto(Ponto2D *p, float dx, float dy){
    p->x = dx;
    p->y = dy;
}

float distanciaEntrePontos(Ponto2D p1, Ponto2D p2){
    float xf = p2.x - p1.x;
    float yf = p2.y - p1.y;
    float resultado = sqrtf(((xf*xf)+(yf*yf)));
    return resultado;
}

int main(){
    float x, y;
    printf("Crie o primeiro ponto 2D\n");
    printf("Digite o valor de X: ");
    scanf("%f", &x);
    printf("Digite o valor de Y: ");
    scanf("%f", &y);
    Ponto2D ponto1 = criaPonto(x, y);

    printf("Crie o segundo ponto 2D\n");
    printf("Digite o valor de X: ");
    scanf("%f", &x);
    printf("Digite o valor de Y: ");
    scanf("%f", &y);
    Ponto2D ponto2 = criaPonto(x, y);

    float distancia = distanciaEntrePontos(ponto1, ponto2);
    printf("\nA distância euclidiana entre os pontos é %.2f\n", distancia);
    movePonto(&ponto2, 50, 50);
    distancia = distanciaEntrePontos(ponto1, ponto2);
    printf("\nA distância euclidiana após atualização é %.2f\n", distancia);
}

