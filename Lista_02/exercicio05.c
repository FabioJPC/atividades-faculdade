#include <stdio.h>
typedef struct{
    char marca[50];
    char modelo[50];
    int ano;
    float preco;
} Veiculo;

void preencheVeiculo(Veiculo *v){
    printf("----Cadastrar um veículo----\n");
    printf("Digite o a marca do veículo:\n");
    scanf(" %49[^\n]%*c", &v->marca);
    printf("Digite o modelo do veículo:\n");
    scanf(" %49[^\n]%*c", &v->modelo);
    printf("Digite o ano do veículo:\n");
    scanf("%d", &v->ano);
    printf("Digite o preço do veículo:\n");
    scanf("%f", &v->preco);
}
void atualizaPreco(Veiculo *v, float preco){
    v->preco = preco;
}

void exibeVeiculo(Veiculo *v){
    printf("\n----Exibindo veiculo----\n");
    printf("Marca: %s\n", v->marca);
    printf("Modelo: %s\n", v->modelo);
    printf("Ano: %d\n", v->ano);
    printf("Preço: %.2f\n", v->preco);
}

int main(){
    Veiculo veiculo;
    float novoPreco;
    preencheVeiculo(&veiculo);
    exibeVeiculo(&veiculo);
    printf("Digite o novo preço para atualizar\n");
    scanf("%f", &novoPreco);
    atualizaPreco(&veiculo, novoPreco);
    exibeVeiculo(&veiculo);

}