
#include <stdio.h>
#include <string.h>

typedef struct{
    int hora, minuto, segundo;
    
} Horario;

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct{
    Data data;
    Horario horario;
    char descricao[300];
} Compromisso;

void imprimeCompromisso(Compromisso *comp){
    printf("\nSeu compromisso foi salvo para dia %d/%d/%d no horário %d:%d:%d \n",
    comp->data.dia, comp->data.mes, comp->data.ano,
    comp->horario.hora, comp->horario.minuto, comp->horario.segundo                             
    );
    printf("Descrição do compromisso:\n %s", comp->descricao);
}

void criaCompromisso(Compromisso *compromisso, int *d, int *h, char *desc){ 
    Data data; Horario horario;
    data.dia = d[0];
    data.mes = d[1];
    data.ano = d[2];
    horario.hora = h[0];
    horario.minuto = h[1];
    horario.segundo = h[2];

    if(horario.hora == 23 && horario.minuto == 59 && horario.segundo == 59){
        data.dia++;
        horario.hora = 0;
        horario.minuto = 0;
        horario.segundo = 0;
    }

    compromisso->horario = horario;
    compromisso->data = data;
    strcpy(compromisso->descricao, desc);
    
}

void main(){
    Compromisso compromisso;
    int data[3]; 
    int horario[3];
    char descricao[200];
    char buffer[20];
    
    //Data
    printf("Digite a data do compromisso no formato dd/mm/aaaa: \n");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d/%d/%d", &data[0], &data[1], &data[2]);

    //Horario
    printf("Digite o horario do compromisso no formato hh:mm:ss \n");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d:%d:%d", &horario[0], &horario[1], &horario[2]);

    printf("Digite uma descrição breve do compromisso.\n");
    fgets(descricao, sizeof(descricao), stdin);

    criaCompromisso(&compromisso, data, horario, descricao);
    imprimeCompromisso(&compromisso);

}
