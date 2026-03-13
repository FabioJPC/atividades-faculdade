#include <stdio.h>
#include <stdbool.h>

typedef struct {
  int matricula;
  char nome[50];
  float n1, n2, n3;
  float media;
}AlunoNota;

AlunoNota maiorPrimeiraProva(AlunoNota a[], int tam){
    float maiorNota = 0;
    int maiorIndex = 0;
    for(int i=0; i<tam; i++){
        if(a[i].n1 > maiorNota){
            maiorNota = a[i].n1;
            maiorIndex = i;
        }
    }
    return a[maiorIndex];
}

void mediaGeral(AlunoNota *a){
    float media;
    media = (a->n1 + a->n2 + a->n3) / 3;
    a->media = media;
}

bool aprovado(AlunoNota *a){
    float aprovacao = 70.0f;
    if(a->media < aprovacao){
        return false;
    }
    return true;
}

int main(){
    //Exemplos
    int arraySize = 2;
    AlunoNota alunos[arraySize];
    for(int i=0; i<arraySize; i++){
        printf("Cadastro novo aluno\n");

        printf("Digite o nome: ");
        scanf(" %49[^\n]%*c", &alunos[i].nome);

        printf("Digite a matrícula: ");
        scanf("%d", &alunos[i].matricula);

        printf("Digite a primeira nota: ");
        scanf("%f", &alunos[i].n1);

        printf("Digite a segunda nota: ");
        scanf("%f", &alunos[i].n2);

        printf("Digite a terceira nota: ");
        scanf("%f", &alunos[i].n3);

        mediaGeral(&alunos[i]);
    }
    AlunoNota melhorN1 = maiorPrimeiraProva(alunos, arraySize);
    printf("O aluno com a melhor primeira prova foi: %s \n", melhorN1.nome);
    if(aprovado(&melhorN1)){
        printf("Esse aluno está aprovado\n");
    }else{
        printf("Esse aluno está reprovado");
    }

}