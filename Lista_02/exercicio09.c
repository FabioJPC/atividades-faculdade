#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
  char titulo[100];
  char autor[50];
  int anoPublicacao;
  int exemplaresDisponiveis;
}Livro;

Livro criaLivro(const char *titulo, const char *autor, int ano, int exemplares){
    Livro novo;
    novo.anoPublicacao = ano;
    novo.exemplaresDisponiveis = exemplares;
    strncpy(novo.autor, autor, sizeof(novo.autor)-1);
    strncpy(novo.titulo, titulo, sizeof(novo.titulo)-1);
    return novo;
}

bool emprestaLivro(Livro *livro){
    if(livro->exemplaresDisponiveis > 0){
        livro->exemplaresDisponiveis--;
        return true;
    }
    return false;
}

void devolveLivro(Livro *livro){
    livro->exemplaresDisponiveis++;
}

void exibeLivro(Livro livro){
    printf("\n----Exibindo Livro\n");
    printf("Título: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Ano: %d\n", livro.anoPublicacao);
    printf("Exemplares disponíveis: %d\n", livro.exemplaresDisponiveis);
}

int main(){
    char* nomes[] = {"1984", "Harry Potter"};
    char* autores[] = {"George Orwell", "J. K. Rowling"};
    int anos[]= {1949, 1997};
    int exemplares[] = {16, 28};

    Livro livro1 = criaLivro(nomes[0], autores[0], anos[0], exemplares[0]);
    Livro livro2 = criaLivro(nomes[1], autores[1], anos[1], exemplares[1]);
    printf("Livro antes do empréstimo: \n");
    exibeLivro(livro1);
    emprestaLivro(&livro1);
    printf("Livro depois do empréstimo: \n");
    exibeLivro(livro1);
    devolveLivro(&livro1);
    printf("Livro depois da devolução: \n");
    exibeLivro(livro1);
}

