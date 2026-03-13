#include <stdio.h>
#include <string.h>

typedef struct{
    int id;
    char nome[50];
    float preco;
    int quantidadeEstoque;
}Produto;

Produto criaProduto(int id, const char* nome, float preco, int estoque){
    Produto novo;
    novo.id = id;
    novo.preco = preco;
    novo.quantidadeEstoque = estoque;
    strncpy(novo.nome, nome, sizeof(novo.nome));
    return novo;
}

void atualizaEstoque(Produto *p, int delta){
    p->quantidadeEstoque += delta;
}

void exibeProduto(Produto prod){
    printf("\n----Detalhes do produto----\n");
    printf("Identificador: %d\n", prod.id);
    printf("Nome: %s\n", prod.nome);
    printf("Preço: %.2f\n", prod.preco);
    printf("Estoque: %d\n", prod.quantidadeEstoque);
}

int main(){
    Produto produto = criaProduto(1, "Teclado Logitech", 149.99, 100);
    printf("\n----Exibindo produto original:\n");
    exibeProduto(produto);

    atualizaEstoque(&produto, -10);
    printf("Após decréscimo: ");
    exibeProduto(produto);

    atualizaEstoque(&produto, 5);
    printf("Após acréscimo: ");
    exibeProduto(produto);

}
