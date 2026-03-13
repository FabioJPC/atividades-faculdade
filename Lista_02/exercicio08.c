#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef enum {TO_DO, IN_PROGRESS, DONE, BLOCKED}Status;
typedef enum {BAIXA, MEDIA, ALTA}Prioridade;
typedef struct {
    int id;
    char nome[100];
    Status status;
    Prioridade prioridade;
}Task;

Task criaTarefa(int id, const char *nome, Status s, Prioridade p){
    Task nova;
    nova.id = id;
    nova.status = s;
    nova.prioridade = p;
    strncpy(nova.nome, nome, sizeof(nova.nome)-1);
    return nova;
}

void atualizaStatus(Task *t, Status s){
    t->status = s;
}

bool tarefaUrgente(Task t){
    if(t.prioridade == ALTA){
        return true;
    }
    return false;
}

int main(){
    const char* status_nomes[] = {
    "TO_DO",
    "IN_PROGRESS",
    "DONE",
    "BLOCKED"
    };
    Task task = criaTarefa(1, "Estudar C", IN_PROGRESS, MEDIA);
    bool prioridade = tarefaUrgente(task);
    printf("A tarefa é %s ", prioridade ? "urgente" : "não urgente");
    printf("\nO status da tarefa é %s\n", status_nomes[task.status]);
    printf("Mudando status...\n");
    atualizaStatus(&task, ALTA);
    printf("O status da tarefa é %s\n", status_nomes[task.status]);
}

