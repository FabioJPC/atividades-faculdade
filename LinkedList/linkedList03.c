#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_DISCIPLINAS 10
#define maxAlunos 50
#define inv -1

//Definições de disciplina
typedef struct {
    int codigo;
    char nome[50];
}Disciplina;

typedef struct{
    Disciplina disciplina;
    int proximo;
}RegistroDisc;

//Lista de todas as disciplinas
typedef struct{
    int inicio, disponivel;
    RegistroDisc listaDisc[MAX_DISCIPLINAS];
}ListaDisciplinas;

//Definições de aluno
typedef struct{
    int matricula;
    char nome[100];
    ListaDisciplinas discAluno;
}Aluno;

typedef struct{
    Aluno aluno;
    int proximo;
}RegistroAluno;

typedef struct{
    RegistroAluno regAluno[maxAlunos];
    int inicio, disponivel;
}ListaAlunos;

//HELPERS
void paraMinusculo(char *str){
    for(int i=0; str[i]; i++){
        str[i] = tolower((unsigned char)str[i]);
    }
}

void inicializarDisciplinas(ListaDisciplinas *l){
    int i=0;
    for(i; i<MAX_DISCIPLINAS; i++){
        l->listaDisc[i].proximo = i + 1;
    }
    l->listaDisc[MAX_DISCIPLINAS - 1].proximo = inv;
    l->inicio = inv;
    l->disponivel = 0;
}

bool adicionarDisciplina(ListaDisciplinas *l, int codigo, const char *nome){
    //lista cheia
    if(l->disponivel == inv) return false;
    int anterior = inv;
    int i = l->inicio;

    while(i != inv && codigo > l->listaDisc[i].disciplina.codigo){
        anterior = i;
        i = l->listaDisc[i].proximo;
    }

    if(i != inv && l->listaDisc[i].disciplina.codigo == codigo) return false;

    int novo = l->disponivel;
    l->disponivel = l->listaDisc[novo].proximo;

    l->listaDisc[novo].disciplina.codigo = codigo;
    strcpy(l->listaDisc[novo].disciplina.nome, nome);

    if(anterior == inv){
        l->listaDisc[novo].proximo = l->inicio;
        l->inicio = novo;
    }else{
        l->listaDisc[novo].proximo = l->listaDisc[anterior].proximo;
        l->listaDisc[anterior].proximo = novo;
    }
    return true;
}

void preencherDisciplinas(ListaDisciplinas *l){
    int codigos[] = {1,2,3,4};
    char *nomes[] = {"Matemática", "Física", "Química", "Inglês"};
    for(int x=0; x<4; x++){
        adicionarDisciplina(l, codigos[x], nomes[x]);
    }
}

void mostrarDisciplinas(ListaDisciplinas *l){
    int x = l->inicio;
    while(x != inv){
        printf("%d.%s\n", l->listaDisc[x].disciplina.codigo, l->listaDisc[x].disciplina.nome);
        x = l->listaDisc[x].proximo;
    }
}

void inicializarAlunos(ListaAlunos *l){
    int i = 0;
    for(i; i<maxAlunos; i++){
        l->regAluno[i].proximo = i + 1;
    }
    l->regAluno[maxAlunos-1].proximo = inv;
    l->inicio = inv;
    l->disponivel = 0;
    printf("\nA lista de alunos foi inicializada!\n");
}

void adicionarAluno(ListaAlunos *l, ListaDisciplinas d){
    int mat, opcao;
    char nome[100];
    ListaDisciplinas disciplinasDoAluno;
    inicializarDisciplinas(&disciplinasDoAluno);

    if(l->disponivel == inv){
        printf("Lista de alunos cheia...");
        return;
    }
    printf("\n-----Adicionar aluno-----\n");
    printf("Digite o numero da matrícula: ");
    scanf("%d", &mat);
    printf("\nDigite o nome do aluno: ");
    scanf(" %99[^\n]", nome);
    printf("\nSelecione as disciplinas que irá cursar:\n");
    while(true){
        printf("\nDisciplinas disponíveis:\n");
        mostrarDisciplinas(&d);
        printf("\n9. Concluir\n");
        scanf("%d", &opcao);
        if(opcao == 9) break;
        int i = d.inicio;
        while(i != inv && d.listaDisc[i].disciplina.codigo != opcao){
            i = d.listaDisc[i].proximo;
        }
        if(i == inv){
            printf("\nDisciplina não encontrada!\n");
        }else{
            adicionarDisciplina(&disciplinasDoAluno, d.listaDisc[i].disciplina.codigo, d.listaDisc[i].disciplina.nome);
        }
    }
    //Inserindo e sinalizando o próximo
    int novo = l->disponivel;
    l->disponivel = l->regAluno[novo].proximo;
    int anterior = inv;
    int i = l->inicio;
    while(i != inv && mat > l->regAluno[i].aluno.matricula){
        anterior = i;
        i = l->regAluno[i].proximo;
    }

    l->regAluno[novo].aluno.matricula = mat;
    strcpy(l->regAluno[novo].aluno.nome, nome);
    l->regAluno[novo].aluno.discAluno = disciplinasDoAluno;

    if(anterior == inv){
        l->regAluno[novo].proximo = l->inicio;
        l->inicio = novo;
    }else{
        l->regAluno[novo].proximo = l->regAluno[anterior].proximo;
        l->regAluno[anterior].proximo = novo;
    }
    printf("\nAluno adicionado com sucesso!\n");
}

void imprimirAluno(Aluno aluno){
    printf("\nDados do aluno:\n");
    printf("Num. matrícula: %d\n", aluno.matricula);
    printf("Nome: %s\n", aluno.nome);
    printf("Disciplinas em andamento: \n");
    mostrarDisciplinas(&aluno.discAluno);
}

void buscarPorNome(ListaAlunos *l){
    char nome[100];
    printf("\n-----Busca por nome-----\n");
    printf("Digite o nome:");
    scanf(" %99[^\n]%c", nome);
    paraMinusculo(nome);
    int i=l->inicio;
    char nameFormat[100];
    while(i != inv){
        strcpy(nameFormat, l->regAluno[i].aluno.nome);
        paraMinusculo(nameFormat);
        if(strcmp(nome,nameFormat)== 0){
            break;
        }
        i = l->regAluno[i].proximo;
    }
    if (i != inv) {
        imprimirAluno(l->regAluno[i].aluno);
    } else {
        printf("Aluno nao encontrado.\n");
    }
}

void buscarPorMatricula(ListaAlunos *l){
    int matricula;
    printf("\n-----Busca por matrícula-----\n");
    printf("Digite o número da matrícula:");
    scanf("%d", &matricula);
    int i= l->inicio;
    while(i != inv && l->regAluno[i].aluno.matricula != matricula){
        i = l->regAluno[i].proximo;
    }
    if(i == inv || l->regAluno[i].aluno.matricula != matricula){
        printf("\nAluno não encontrado!\n");
    }else{
        imprimirAluno(l->regAluno[i].aluno);
    }
}

void deletarAluno(ListaAlunos *l){
    if (l->inicio == inv) {
        printf("\nLista vazia!\n");
        return;
    }
    printf("\n-----Deletar aluno-----\n");
    int matricula;
    printf("Digite a matrícula do aluno à deletar: ");
    scanf("%d", &matricula);
    
    int i = l->inicio;
    int anterior = inv;
    while(i != inv && l->regAluno[i].aluno.matricula < matricula){
        anterior = i;
        i = l->regAluno[i].proximo;
    }
    if(i != inv && l->regAluno[i].aluno.matricula == matricula){
        if(anterior == inv){
            l->inicio = l->regAluno[i].proximo;
        }else{
            l->regAluno[anterior].proximo = l->regAluno[i].proximo;
        }
        l->regAluno[i].proximo = l->disponivel;
        l->disponivel = i;
        printf("\nAluno deletado com sucesso!\n");
    }else {
        printf("\nAluno não encontrado!\n");
    }

}

void imprimirTodosOsAlunos(ListaAlunos *l){
    if(l->inicio == inv){
        printf("Lista vazia\n");
        return;
    }
    int i = l->inicio;
    printf("\nImprimindo todos os alunos...\n");
    while(i != inv){
        printf("Matrícula: %d\tNome: %s\n", l->regAluno[i].aluno.matricula, l->regAluno[i].aluno.nome);
        i = l->regAluno[i].proximo;
    }
}

void imprimirPorDisciplina(ListaAlunos *l, ListaDisciplinas *d){
    char opcao[100];
    printf("\n----Imprimir alunos por disciplina-----\n");
    printf("Digite a disciplina desejada:\n");
    scanf(" %99[^\n]%c", &opcao);
    paraMinusculo(opcao);
    int i = d->inicio;
    char formatted[100];
    int codDisciplina;
    while(i != inv){
        strcpy(formatted,d->listaDisc[i].disciplina.nome);
        paraMinusculo(formatted);
        if(strcmp(formatted, opcao) == 0){
            codDisciplina = d->listaDisc[i].disciplina.codigo;
            break;
        }
        i = d->listaDisc[i].proximo;
    }
    if(i == inv){
        printf("\nDisciplina não encontrada!\n");
        return;
    }
    printf("Alunos matriculados em %s\n", d->listaDisc[i].disciplina.nome);
    int alunoAtual = l->inicio;
    bool encontrouDisciplina = false;

    while(alunoAtual != inv){
        int alunoDisciplinaAtual = l->regAluno[i].aluno.discAluno.inicio;
        while(alunoDisciplinaAtual != inv){
            if(l->regAluno[alunoAtual].aluno.discAluno.listaDisc[alunoDisciplinaAtual].disciplina.codigo == codDisciplina){
                printf("Matricula: %d\tNome: %s\n", l->regAluno[alunoAtual].aluno.matricula, l->regAluno[alunoAtual].aluno.nome);
                encontrouDisciplina = true;
            }
            alunoDisciplinaAtual = l->regAluno[alunoAtual].aluno.discAluno.listaDisc[alunoDisciplinaAtual].proximo;
        }
        alunoAtual = l->regAluno[alunoAtual].proximo;
    }
    if(!encontrouDisciplina){
        printf("Nenhum aluno matriculado nessa disciplina.\n");
    }

    
}

int main(){
    ListaDisciplinas disciplinasGeral;
    inicializarDisciplinas(&disciplinasGeral);
    preencherDisciplinas(&disciplinasGeral);
    ListaAlunos listaAlunos;
    inicializarAlunos(&listaAlunos);
    char sair = 'n';
    int opcao = inv;
    do{
        printf("\nSelecione uma das opções:\n");
        printf("1. Criar lista de alunos\n");
        printf("2. Inserir aluno na lista\n");
        printf("3. Ver um aluno\n");
        printf("4. Deletar um aluno\n");
        printf("5. Ver todos os alunos\n");
        printf("6. Ver todos os alunos por disciplina\n");
        printf("9. Sair do programa\n");
        scanf("%d", &opcao);
        switch (opcao){
        case 1:
            inicializarAlunos(&listaAlunos);
            break;
        case 2:
            adicionarAluno(&listaAlunos, disciplinasGeral);
            break;
        case 3:
            printf("Buscar aluno por matricula ou nome?\n");
            printf("1. Matrícula\n2. Nome\n");
            int selecao = inv;
            scanf("%d", &selecao);
            switch (selecao){
            case 1:
                buscarPorMatricula(&listaAlunos);
                break;
            case 2:
                buscarPorNome(&listaAlunos);
                break;
            default:
            printf("\nOpção inválida!");
                break;
            }
            break;

        case 4:
            deletarAluno(&listaAlunos);
            break;
        case 5:
            imprimirTodosOsAlunos(&listaAlunos);
            break;
        case 6:
            imprimirPorDisciplina(&listaAlunos, &disciplinasGeral);
            break;
        case 9:
            return 0;
        default:
            printf("\nOpção inválida!");
            break;
        }

        printf("\nDeseja sair do programa?(s/n)");
        scanf(" %c", &sair);

    }while(sair != 's' && sair != 'S');

}
