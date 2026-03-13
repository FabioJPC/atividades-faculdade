#include <stdio.h>
typedef struct{
    int x, y, z;
}Vetor3D;

Vetor3D somaVetores(Vetor3D a, Vetor3D b){
    Vetor3D resultado;
    resultado.x = a.x + b.x;
    resultado.y = a.y + b.y;
    resultado.z = a.z + b.z;
    return resultado;
}

void acumulaNoPrimeiro(Vetor3D *a, Vetor3D b){
    a->x += b.x;
    a->y += b.y;
    a->z += b.z;
}

void inserirDados(Vetor3D *v){
    printf("----Construindo vetor----\n");
    printf("Digite o X: ");
    scanf("%d", &v->x);

    printf("Digite o Y: ");
    scanf("%d", &v->y);

    printf("Digite o Z: ");
    scanf("%d", &v->z);
}
void exibeVetor(Vetor3D *v){
    printf("Valor de X: %d ", v->x);
    printf("Valor de Y: %d ", v->y);
    printf("Valor de Z: %d ", v->z);
}

int main(){
    Vetor3D a, b, soma;
    inserirDados(&a);
    inserirDados(&b);
    soma = somaVetores(a, b);
    printf("\nPrimeiro vetor\n");
    exibeVetor(&a);
    printf("\nSegundo vetor\n");
    exibeVetor(&b);
    printf("\nSoma dos vetores\n");
    exibeVetor(&soma);

    acumulaNoPrimeiro(&a, b);
    printf("\nPrimeiro vetor após mudança:\n");
    exibeVetor(&a);

}