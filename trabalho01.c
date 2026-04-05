#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//Definição de cores
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_ORANGE  "\x1b[38;5;208m"
#define ANSI_COLOR_RESET   "\x1b[0m"

//Helpers para exibiçao
const char* nomesSexo[] = {"Masculino", "Feminino"};
const char* nomesPrioridade[] = {"Vermelho", "Laranja", "Amarelo", "Verde"};
const char* coresPrioridade[] = {ANSI_COLOR_RED, ANSI_COLOR_ORANGE, ANSI_COLOR_YELLOW, ANSI_COLOR_GREEN};

//Definição de estruturas
typedef enum{MASCULINO, FEMININO}Sexo;
typedef enum {VERMELHO, LARANJA, AMARELO, VERDE }Prioridade;

typedef struct{
    int pressaoSistolica, nivelDor, idade;
    float altura, peso, temperatura;
    bool sangramentoVisivel, faltaAr, dorPeito;
}Triagem;

typedef struct{
    char nome[100];
    char cpf[15];
    char telefone[20];
    char email[50];
    char observacoes[300];
    Sexo sexo;
}Paciente;

typedef struct Elemento{
    Paciente *paciente;
    Prioridade prioridade;
    struct Elemento *proximo;
    int posicao;
}Elemento;

typedef struct{
    Elemento *inicio;
    Elemento *fim;
    Elemento *ultimos[4];
    int total;
}ListaPacientes;

//Helpers
bool comparaStringIgnore(char *str1, char *str2){
    //Compara strings ignorando Case, retorna true caso sejam iguais.
    while(*str1 && (tolower((unsigned char) *str1) == tolower((unsigned char) *str2))){
        str1++;
        str2++;
    }
    return *str1 == *str2;
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Validação e formatação
bool validarCpf(char *cpfOriginal){
    //Tamanho da string inválido(somente numeros = 11, com pontuação = 14)
    int tamanho = strlen(cpfOriginal);
    if( tamanho != 11 && tamanho != 14){ printf("tamanho"); return false;}

    //Pegar CPF digito a digito
    int digitos[11] = {0};
    int j = 0;

    for(int i= 0; i < tamanho; i++){
        int num = 0;
        if(isdigit(cpfOriginal[i])){
            if(j < 11){
                digitos[j] = cpfOriginal[i] - '0';
                j++;
            }
        }  
    }

    //Digitos faltando
    if(j != 11) {
        printf("digitos faltando");
        return false;
    }

    //Se todos os digitos forem iguais é inválido
    bool todosIguais = true;
    for(int i=1; i<11; i++){
        if(digitos[0] != digitos[i]){
            todosIguais = false;
            break;
        }
    }
    if(todosIguais) {printf("iguais"); return false;}

    // Cálculo do 1º Dígito Verificador
    int soma = 0;
    for(int i=0; i<9; i++){
        soma += (10-i) * digitos[i];
    }
    int primeiroVerificador = 11 - (soma % 11);
    if(primeiroVerificador >= 10){
        primeiroVerificador = 0;
    }
    if(digitos[9] != primeiroVerificador) {printf("1VER");return false;}

    // Cálculo do 2º Dígito Verificador
    soma = 0;
    for(int i=0; i<10; i++){
        soma += (11-i) * digitos[i];
    }
    int segundoVerificador = 11 - (soma % 11);
    if(segundoVerificador >= 10){
        segundoVerificador = 0;
    }
    return (digitos[10] == segundoVerificador);
}

bool validarTelefone(char *telefone){
    int tamanho = 0;
    int somenteDigitos[12];

    int j=0;
    //Retirar qualquer caractere que não seja número
    for(int i=0; telefone[i] != '\0'; i++){
        if(isdigit(telefone[i]) != 0){
            if(tamanho < 11){
                somenteDigitos[j] = telefone[i] - '0';
                j++;
            }
            tamanho++;
        }
    }

    //Verificar tamanho total(No Brasil é 10 ou 11)
    if(tamanho != 10 && tamanho!= 11){
        printf(ANSI_COLOR_RED "\nErro: Numero fora do padrão, ex: 42911112222 (somente números).\n" ANSI_COLOR_RESET);
        return false;
    }
    //Validar DDD
    int ddd = somenteDigitos[0] * 10 + somenteDigitos[1];
    if(ddd < 11 || ddd > 99){
        printf(ANSI_COLOR_RED "\nO DDD não é válido. Ex: 42, 11.\n" ANSI_COLOR_RESET);
        return false; 
    }
    //Caso celular, validar nono dígito.
    if(tamanho == 11){
        if(somenteDigitos[2] != 9){
            printf("\nNono dígito incorreto!\n");
            return false;
        }
    }
    return true;
}

bool validarEmail(char *email){
    int tamanho =  strlen(email);
    int arroba = -1, ponto = -1;
    for(int i=0; i!= tamanho; i++){
        if(email[i] == '@'){
            if(arroba != -1){
                //Já tem um arroba, então inválido.
                return false;
            }
            arroba = i;
        }else if(email[i] == '.' ){
            if(arroba != -1) ponto = i; //'.' após o '@'
        }
    }
    return (arroba > 0 && ponto > arroba + 1 && ponto < tamanho - 1);
}

void formatarCpf(char *cpf){
    char somenteNumeros[15];
    int j = 0;
    for(int i=0; cpf[i] != '\0'; i++){
        if(isdigit((unsigned char)cpf[i])){
            somenteNumeros[j] = cpf[i];
            j++;
        }
    }
    somenteNumeros[j] = '\0';

    char molde[15] = "000.000.000-00";
    int k = 0;
    for(int i=0; molde[i] != '\0' && somenteNumeros[k] != '\0'; i++){
        if(molde[i] == '0'){
            molde[i] = somenteNumeros[k];
            k++;
        }
    }
    strcpy(cpf, molde);
}

void formatarTelefone(char *telefone){
    char apenasNumeros[20];
    int j = 0;
    for(int i= 0; telefone[i] != '\0'; i++){
        if(isdigit((unsigned char)telefone[i])){
            apenasNumeros[j] = telefone[i];
            j++;
        }
    }
    apenasNumeros[j] = '\0';
    char molde[15]= "(00)00000-0000";
    int k = 0;
    for(int i=0; molde[i] != '\0' && apenasNumeros[k] != '\0'; i++){
        if(molde[i] == '0'){
            molde[i] = apenasNumeros[k];
            k++;
        }
    }
    strcpy(telefone, molde);
}


//Funções da fila

Prioridade calcularPrioridade(Triagem d){
    int score = 0;
    //Temperatura
    if (d.temperatura >= 40.0 || d.temperatura < 35.0) score += 4;
    else if (d.temperatura >= 38.5) score += 2;
    else if (d.temperatura >= 37.5) score += 1;

    //Pressão Sistólica
    if (d.pressaoSistolica >= 200 || d.pressaoSistolica < 90) score += 4;
    else if (d.pressaoSistolica >= 160) score += 2;

    //Nível de Dor
    if (d.nivelDor >= 9) score += 3;
    else if (d.nivelDor >= 6) score += 1;

    //Idade
    if (d.idade >= 65 || d.idade <= 5) score += 2;

    //IMC
    if(d.altura > 0){
        float imc = d.peso / (d.altura * d.altura);
        if(imc >= 35) score +=2;
        else if(imc >= 31) score +=1; 
    }

    //Atenção Especial
    if (d.faltaAr) score += 5;
    if (d.sangramentoVisivel) score += 4;
    if (d.dorPeito) score += 5;

    if(score > 10 || d.dorPeito && d.faltaAr) return VERMELHO;
    if(score > 7) return LARANJA;
    if(score > 4) return AMARELO;
    return VERDE;
}

Prioridade definirPrioridade(){

    Triagem dados;
    char temp;

    printf(ANSI_COLOR_YELLOW"\n-----Pré-Consulta----\n"ANSI_COLOR_RESET);
    printf("Digite os seguintes dados do paciente: \n");
    
    printf("Temperatura: ");
    scanf("%f", &dados.temperatura);
    limparBuffer();

    printf("\nPressão Sistólica: ");
    scanf("%d", &dados.pressaoSistolica);
    limparBuffer();

    printf("\nPeso: ");
    scanf("%f", &dados.peso);
    limparBuffer();

    printf("\nAltura: ");
    scanf("%f", &dados.altura);
    limparBuffer();

    printf("\nIdade: ");
    scanf("%d", &dados.idade);
    limparBuffer();

    printf("\nNivel de dor: ");
    scanf("%d", &dados.nivelDor);
    limparBuffer();

    printf("\nPossui sangramento vísivel?(s/n) ");
    scanf(" %c", &temp);
    dados.sangramentoVisivel = (tolower(temp) == 's') ? true:false;

    printf("\nPossui falta de ar(s/n) ");
    scanf(" %c", &temp);
    dados.faltaAr = (tolower(temp) == 's') ? true:false;

    printf("\nPossui dor no peito?(s/n) ");
    scanf(" %c", &temp);
    dados.dorPeito = (tolower(temp) == 's') ? true:false;

    return calcularPrioridade(dados);
}

Elemento *buscarPorCPf(ListaPacientes *lista, char *cpf){
    formatarCpf(cpf);
    if(lista->inicio == NULL) return false;
    Elemento *atual = lista->inicio;
    while(atual != NULL){
        if(strcmp(atual->paciente->cpf, cpf) == 0){
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

Elemento *buscarDisponivel(ListaPacientes *gerenciador, Elemento *novo, int offset){

    //Caso lista vazia
    if(gerenciador->inicio == NULL) return NULL;

    if(novo->prioridade == VERDE){
        return gerenciador->fim;
    }

    //Tenta achar o ultimo com mesma prioridade
    Elemento *temp = NULL;
    temp = gerenciador->ultimos[novo->prioridade];

    //Caso não tenha nenhum com mesma prioridade tenta achar o ultimo com prioridade menor
    if(temp == NULL){
        for(int i = novo->prioridade - 1; i >=0; i--){
            if(gerenciador->ultimos[i] != NULL){
                temp = gerenciador->ultimos[i];
                break;
            }
        }
    }

    //Caso não ache nenhum com prioridade maior, deve inserir no inicio
    if(temp == NULL) return NULL;

    //Caso ache outro com prioridade aplicar o offset
    for(int i = 0; i < offset && temp->proximo != NULL; i++){
        temp = temp->proximo;
    }
    return temp;
}

void inserirPorPrioridade(ListaPacientes *gerenciador, Elemento *novoNo){
    /*  
        A lógica de inserção funciona assim:
        Vermelho - Sempre no começo da fila após os outros vermelhos já presentes
        Verde - Sempre no fim da fila, após os outros verdes
        Laranja e Amarelo - Caso sejam o primeiro do seu tipo, passam na frente de todos os
        de prioridade menor, caso já tenha um com a mesma prioridade ele irá ser adicionado
        pulando 1(amarelo) ou 3(Laranja) após o ultimo de cada cor.
    */
    int offset = (novoNo->prioridade == LARANJA) ? 1 : (novoNo->prioridade == AMARELO) ? 3 : 0; 

    Elemento *referencia = buscarDisponivel(gerenciador, novoNo, offset);

    if(referencia == NULL){
        novoNo->proximo = gerenciador->inicio;
        gerenciador->inicio = novoNo;
    }else{
        novoNo->proximo = referencia->proximo;
        referencia->proximo = novoNo;
    }
    gerenciador->ultimos[novoNo->prioridade] = novoNo;
    if(novoNo->proximo == NULL) gerenciador->fim = novoNo;

    gerenciador->total++;
    
}

void imprimirFila(ListaPacientes *gerenciador){

    if(gerenciador->total == 0){
        printf(ANSI_COLOR_RED "\nFila vazia!\n" ANSI_COLOR_RESET);
        return;
    }

    printf("\n\t\t\tLista de espera:\n");
    printf("Total de pacientes: %s%d%s\n", ANSI_COLOR_YELLOW, gerenciador->total, ANSI_COLOR_RESET);
    Elemento *i = gerenciador->inicio;
    int counter = 1;
    while(i != NULL){
        printf("%d. %-25s  Sexo: %-12s  Prioridade: %s%-12s%s\n",
                counter,
                i->paciente->nome,
                nomesSexo[i->paciente->sexo],
                coresPrioridade[i->prioridade],
                nomesPrioridade[i->prioridade],
                ANSI_COLOR_RESET);
        i = i->proximo;
        counter++;
    }
}

void chamarPaciente(ListaPacientes *gerenciador){
    if(gerenciador->inicio == NULL){
        printf(ANSI_COLOR_RED"\nA fila está vazia, nenhum paciente para chamar!\n"ANSI_COLOR_RESET);
        return;
    }
    Elemento *removido = gerenciador->inicio;
    Paciente *p = removido->paciente;

    printf("\n========================================");
    printf("\n   PROXIMO PACIENTE: %s", p->nome);
    printf("\n   SALA DE ATENDIMENTO: %d", (removido->prioridade + 1) * 10);
    printf("\n   PRIORIDADE: %s%s%s", coresPrioridade[removido->prioridade], nomesPrioridade[removido->prioridade], ANSI_COLOR_RESET);
    printf("\n========================================\n");

    //Checar se o nó removido não é o ultimo de sua cor e atualizar lista se necessário
    if(gerenciador->ultimos[removido->prioridade] == removido){
        gerenciador->ultimos[removido->prioridade] = NULL;
    }

    //Avançar fila
    gerenciador->inicio = removido->proximo;

    //Limpar o fim caso a fila fique zerada
    if(gerenciador->inicio == NULL){
        gerenciador->fim = NULL;
    }
    free(removido);
    gerenciador->total--;
    getchar();
}

void imprimirPacienteFila(Elemento *elemento){
    Paciente *p = elemento->paciente;
    printf(ANSI_COLOR_GREEN"\nInformações sobre o paciente na fila de espera:\n"ANSI_COLOR_RESET);
    printf("Posição na fila: %d\t Nome: %s\tPrioridade: %s%s%s\n",
                    elemento->posicao,
                    p->nome, 
                    coresPrioridade[elemento->prioridade], 
                    nomesPrioridade[elemento->prioridade],
                    ANSI_COLOR_RESET);
}


//Funções do banco de dados de pacientes

Sexo selecionarSexo(){
    printf("Selecione o sexo do paciente: \n");
    printf("\n1. Masculino");
    printf("\n2. Feminino\n");
    int opcao;
    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            return MASCULINO;
        case 2:
            return FEMININO;
        default:
            printf("\n"ANSI_COLOR_RED"Código inválido! Tente novamente."ANSI_COLOR_RESET"\n");
            return selecionarSexo();
    }
}

Elemento *inicializarElemento(){
    Elemento *novoRegistro = (Elemento *) malloc(sizeof(Elemento));
    if(novoRegistro == NULL){
        printf("Erro: memória insuficiente.\n");
        exit(1);
    }
    novoRegistro->proximo = NULL;
    return novoRegistro;
}

Paciente *inicializarPaciente(){
    Paciente *novo = (Paciente *)malloc(sizeof(Paciente));
    if(novo == NULL){
        printf("Erro: memória insuficiente.\n");
        exit(1);
    }
    return novo;
}

void iniciarLista(ListaPacientes *lista){
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->total = 0;
    int size = sizeof(lista->ultimos) / sizeof(lista->ultimos[0]);
    for(int i=0; i< size; i++){
        lista->ultimos[i] = NULL;
    }
}

bool lerEntrada(char *buffer, int tamanho, const char *mensagem){
    printf("%s", mensagem);
    fgets(buffer, tamanho, stdin);
    
    //Se o usuário apertou apenas enter.
    if(buffer[0] == '\n') return false;
    if(isspace(buffer[0])) return false;

    //Remover o '\n' do final
    buffer[strcspn(buffer, "\n")] = '\0';
    return true;
}

bool lerCpf(char *cpf, const char *mensagem){
    //Inserir e validar o CPF
    bool cpfValido = false;
    do{
        if(!lerEntrada(cpf, 20, mensagem)) return false;
        cpfValido = validarCpf(cpf);
        if(!cpfValido){
            printf(ANSI_COLOR_RED"\nCPF inválido! Digite novamente!\n"ANSI_COLOR_RESET);
        }
    }while(!cpfValido);
    return true;
}

bool lerTelefone(char *telefone, const char *mensagem){
    //Inserir e validar o telefone
    bool telefoneValido = false;
    do{
        if(!lerEntrada(telefone, 30, mensagem)) return false;
        telefoneValido = validarTelefone(telefone);
    }while(!telefoneValido);
    return true;
}

bool lerEmail(char *email, const char *mensagem){
    //Inserir e validar email
    bool emailValido = false;
    do{
        if(!lerEntrada(email, 50, mensagem)) return false;
        emailValido = validarEmail(email);
    }while(!emailValido);
    return true;
}

bool criarPaciente(Paciente *novoPaciente){
    char buffer[301];
    printf("\nInsira os dados do novo paciente...\n");
    
    //Leitura e validação do CPF
    if(!lerCpf(buffer, "Digite o CPF do paciente ou pressione 'Enter' para sair: ")) return false;
    formatarCpf(buffer);
    strcpy(novoPaciente->cpf, buffer);

    //Inserção do nome
    bool nomeInserido = lerEntrada(buffer, 100, "Digite o nome do paciente, ou pressione 'Enter' para sair: ");
    if(!nomeInserido) return false;
    strcpy(novoPaciente->nome, buffer);

    //Validar e inserir telefone
    bool telefoneInserido = lerTelefone(buffer, "Digite o telefone do paciente, ou pressione 'Enter' para sair: ");
    if(!telefoneInserido) return false;
    formatarTelefone(buffer);
    strcpy(novoPaciente->telefone, buffer);

    //Selecionar sexo do paciente
    novoPaciente->sexo = selecionarSexo();
    limparBuffer();

    //Validar e inserir email
    bool emailInserido = lerEmail(buffer, "Digite o email do paciente, ou pressione 'Enter' para sair: ");
    if(!emailInserido) return false;
    strcpy(novoPaciente->email, buffer);

    //Observações
    bool obs = lerEntrada(buffer, 300, "Observações sobre o paciente(max: 300 caracteres) ou 'Enter' para deixar vazio: ");
    strcpy(novoPaciente->observacoes, (obs ? buffer : ""));
    return true;
}

bool editarPaciente(Paciente *paciente){
    char buffer[301];

    printf(ANSI_COLOR_YELLOW"\n-----Editar Paciente-----\n"ANSI_COLOR_RESET);
    
    //CPF é inalterável
    printf("CPF atual: %s (Não pode ser alterado)\n", paciente->cpf);
    
    //Nome
    printf("\nNome atual: %s \n", paciente->nome);
    if(lerEntrada(buffer, 301, "Novo nome ('Enter' para manter): ")){
        strcpy(paciente->nome, buffer);
    }

    //Sexo
    printf("\nSexo atual: %s, deseja mudar? (s/n): ", nomesSexo[paciente->sexo]);
    char c = getchar();
    if(c == 's' || c == 'S'){
        paciente->sexo = selecionarSexo();
    }
    limparBuffer();

    // Telefone
    printf("\nTelefone atual: %s\n", paciente->telefone);
    if(lerTelefone(buffer, "Novo telefone (Enter para manter): ")){
        formatarTelefone(buffer);
        strcpy(paciente->telefone, buffer);
    }
    // Email
    printf("\nEmail atual: %s\n", paciente->email);
    if(lerEmail(buffer, "Novo email (Enter para manter): ")){
        strcpy(paciente->email, buffer);
    }

    // Observações
    printf("\nObservações atuais: %s\n", paciente->observacoes);
    if(lerEntrada(buffer, sizeof(buffer), "Novas observações (Enter para manter): ")){
        strcpy(paciente->observacoes, buffer);
    }

    return true;
}

bool excluirPaciente(Elemento *noRemover, ListaPacientes *lista, bool removerDB){
    //Essa função serve tanto para remover da fila quanto da base de dados
    //Caso queira excluir da base removerDB deve ser true

    if(noRemover == NULL|| lista->inicio == NULL) return false; 
    Elemento *atual = lista->inicio;
    Elemento *anterior = NULL;

    char confirmar;
    if(removerDB){
        printf(ANSI_COLOR_RED"Tem certeza que deseja apagar o paciente %s?(s/n)"ANSI_COLOR_RESET,
             noRemover->paciente->nome);
    }else{
        printf(ANSI_COLOR_RED"Tem certeza que deseja remover o paciente %s da fila?(s/n)"ANSI_COLOR_RESET,
             noRemover->paciente->nome);
    }
    scanf(" %c", &confirmar);
    limparBuffer();

    if(confirmar == 'n' || confirmar == 'N'){
        return false;
    }

    //Edge case, o paciente a ser deletado é o primeiro
    if(atual == noRemover){
        lista->inicio = noRemover->proximo;
        //Edge case, caso só tenha um nó
        if(lista->inicio == NULL){
            lista->fim = NULL;
        }

    }else{
        while(atual != NULL && atual != noRemover){
            anterior = atual;
            atual = atual->proximo;
        }
        if(atual == NULL) return false;

        anterior->proximo = atual->proximo;
        if(atual == lista->fim){
            lista->fim = anterior;
        }
    }
    //Lógica específica para a fila
    if(!removerDB){
        Prioridade p = noRemover->prioridade;
        if(lista->ultimos[p] != noRemover){
            //Percorrer lista e achar o ultimo dessa cor
            Elemento *temp = lista->inicio;
            Elemento *novoUltimo = NULL;
            while(temp != NULL && temp != noRemover){
                if(temp->prioridade == p && temp != noRemover){
                    novoUltimo = temp;
                }
                temp = temp->proximo;
            }
            lista->ultimos[p] = novoUltimo;
        }
    }

    if(removerDB){
        free(noRemover->paciente);
    }
    
    lista->total--;
    free(noRemover);
    return true;
}

void imprimirPaciente(Paciente *paciente){
    printf(ANSI_COLOR_YELLOW"\nDados do paciente:\n"ANSI_COLOR_RESET);
    printf("Nome: %s\n", paciente->nome);
    printf("Cpf: %s\n", paciente->cpf);
    printf("Sexo: %s\n", nomesSexo[paciente->sexo]);    
    printf("Telefone: %s\n", paciente->telefone);
    printf("Email: %s\n", paciente->email);
    printf("Observações: %s\n", paciente->observacoes);    
}

void imprimirTodos(ListaPacientes *DB){
    Elemento *atual = DB->inicio;
    Paciente *p;
    printf(ANSI_COLOR_YELLOW"\n-----Lista de todos os pacientes cadastrados-----\n"ANSI_COLOR_RESET);
    printf("%-25s | %-12s | %-16s | %-16s | %s\n", "NOME", "SEXO", "CPF", "TELEFONE", "EMAIL");
    printf("------------------------------------------------------------------------------------------------------------\n");
    while(atual != NULL){
        p = atual->paciente;
        printf("%-25.25s | %-12s | %-16s | %-16s | %s\n", 
            atual->paciente->nome, 
            (atual->paciente->sexo == MASCULINO ? "Masculino" : "Feminino"), 
            atual->paciente->cpf, 
            atual->paciente->telefone,
            atual->paciente->email);
        atual = atual->proximo;
    }
}

Elemento *buscarPaciente(ListaPacientes *lista){
    char buffer[100];
    bool entradaValida = false;
    int posicao = 1;

    while(!entradaValida){
        bool res = lerEntrada(buffer, 100,"Digite o nome ou o CPF do paciente (ou 'enter' para sair): ");
        if(!res) return NULL;
        //Checar se é cpf e se é válido
        if(isdigit(buffer[0])){
            buffer[strcspn(buffer, "\n")] = '\0';
            if(!validarCpf(buffer)){
                printf("\nCPF inválido, tente novamente.\n");
                continue;
            }
            formatarCpf(buffer);
        }
        entradaValida = true;
    }
    
    bool isCpf = isdigit(buffer[0]);

    Elemento *atual = lista->inicio;
    while(atual != NULL){
        char *dadoAComparar = isCpf ? atual->paciente->cpf : atual->paciente->nome;

        if(comparaStringIgnore(buffer, dadoAComparar)){
            atual->posicao = posicao;
            return atual;
        }
        posicao++;
        atual = atual->proximo;
    }
    printf(ANSI_COLOR_RED"\nPaciente não encontrado.\n"ANSI_COLOR_RESET);
    return NULL;
}

void gerenciarBancoPacientes(ListaPacientes *DB, ListaPacientes *fila){

    printf(ANSI_COLOR_YELLOW"\n----- Gerenciar banco de pacientes -----\n"ANSI_COLOR_RESET);
    int opcao;
    while(opcao != 9){
        printf("\nO que deseja fazer?\n");
        printf("1.Cadastrar novo paciente\n");
        printf("2.Ver dados do paciente\n");
        printf("3.Editar um paciente\n");
        printf("4.Excluir um paciente\n");
        printf("5.Ver todos os pacientes\n");
        printf("9.Voltar ao menu principal\n");
        scanf("%d", &opcao);
        limparBuffer();
        switch (opcao){
            case 1:
                Paciente *pacienteNovo = inicializarPaciente();
                bool sucesso = criarPaciente(pacienteNovo);
                if(sucesso){ 
                    Elemento *elementoNovo = inicializarElemento();
                    elementoNovo->paciente = pacienteNovo;
                    elementoNovo->proximo = DB->inicio;
                    DB->inicio = elementoNovo;
                    if(DB->fim == NULL) DB->fim = elementoNovo;
                    printf(ANSI_COLOR_GREEN
                        "\nPaciente adicionado com sucesso! ele já pode ser inserido na fila de espera.\n"
                        ANSI_COLOR_RESET);
                        DB->total++;
                    }else{
                    printf(ANSI_COLOR_RED"\nOcorreu um erro/cancelamento.\n"ANSI_COLOR_RESET);
                }
                break;

            case 2: 
                Elemento *encontrado = buscarPaciente(DB);
                if(encontrado != NULL && encontrado->paciente != NULL){
                    Paciente *paciente = encontrado->paciente;
                    imprimirPaciente(paciente);
                }
                break;

            case 3:
                Elemento *elementoEditar = buscarPaciente(DB);
                Paciente *pacienteEditar = elementoEditar->paciente;
                editarPaciente(pacienteEditar);
                break;

            case 4:
                //Se tiver na fila, excluir antes de excluir no banco
                Elemento *elementoExcluir = buscarPaciente(DB);
                if(elementoExcluir != NULL){
                    Elemento *naFila = buscarPorCPf(fila, elementoExcluir->paciente->cpf);
                    excluirPaciente(naFila, fila, false);
                }
                excluirPaciente(elementoExcluir, DB, true);
                break;

            case 5:
                imprimirTodos(DB);
                break;
                
            case 9:
                printf("\nRetornando ao menu principal...");
                return;
            default:
                printf(ANSI_COLOR_RED"\nOpção inválida!"ANSI_COLOR_RESET);
                break;
        }
    }
}

void testes(ListaPacientes *DB, ListaPacientes *fila){
    // Dados de teste
    Paciente pacientesExemplo[] = {
        {"Ana Souza", "529.982.247-25", "(11)97766-5544", "ana.souza@web.com", "Retorno de cirurgia", FEMININO},
        {"Lucas Oliveira", "12345678909", "21988881122", "lucas.oli@provider.com", "Dor lombar cronica", MASCULINO},
        {"Beatriz Lima", "987.654.321-00", "(31)99988-7766", "beah@email.com", "Alergia a dipirona", FEMININO},
        {"Carlos Eduardo", "16899535009", "47944332211", "cadu@servico.com", "Exame de rotina", MASCULINO},
        {"Ricardo Santos", "529.982.247-25", "(11)91234-5678", "ricardo.santos@email.com", "Hipertenso conhecido", MASCULINO},
        {"Mariana Costa", "847.362.915-91", "(21)98765-4321", "mari.costa@provider.com", "Suspeita de virose", FEMININO},
        {"Fernando Alves", "111.444.777-35", "(31)95544-3322", "alves.f@servico.com", "Entorse no tornozelo", MASCULINO},
        {"Juliana Meireles", "935.411.347-80", "(41)93322-1100", "ju.meireles@web.com", "Gestante, 20 semanas", FEMININO},
        {"Roberto Rocha", "286.255.878-87", "(47)96677-8899", "rocha.beto@email.com", "Dor de cabeça intensa", MASCULINO},
        {"Fernanda Lima", "60278143067", "(51)92233-4455", "fer.lima@provider.com", "Sintomas gripais", FEMININO}
    };

    Triagem exemplosTriagem[] = {
        {110, 2, 25, 1.75, 70.0, 36.5, false, false, false}, // VERDE
        {140, 6, 30, 1.75, 75.0, 38.5, false, false, false}, // AMARELO
        {160, 5, 70, 1.70, 70.0, 39.0, false, false, false}, // LARANJA
        {150, 10, 45, 1.80, 85.0, 37.0, false, true, true},   // VERMELHO
        {155, 4, 72,  1.65,68.0, 39.2, false, false,  false}  //VERDE
        };

    int qtdExemplos = sizeof(pacientesExemplo) / sizeof(pacientesExemplo[0]);

    //Inserir no banco de dados geral
    for(int i=0; i < qtdExemplos; i++){
        Paciente *p = inicializarPaciente();
        *p = pacientesExemplo[i];
        bool erroValidação = false;
        if(!validarCpf(p->cpf) || !validarTelefone(p->telefone)){
            printf(ANSI_COLOR_RED"\nOcorreu um erro de validação\n"ANSI_COLOR_RESET);
            continue;
        }
        formatarCpf(p->cpf);
        formatarTelefone(p->telefone);

        Elemento *novo = inicializarElemento();
        novo->paciente = p;

        novo->proximo = DB->inicio;
        DB->inicio = novo;

        if (DB->fim == NULL) {
            DB->fim = novo;
        }

        ////Inserir os primeiros 5 na fila
        if(i<5){
            Elemento *novoFila = inicializarElemento();
            novoFila->paciente = p;
            novoFila->prioridade = calcularPrioridade(exemplosTriagem[i]);
            inserirPorPrioridade(fila, novoFila);
        }
    }
}

int main(){
    
    ListaPacientes bancoDados;
    ListaPacientes gerenciadorFila;
    iniciarLista(&gerenciadorFila);
    iniciarLista(&bancoDados);
    printf("\n-----Sistema de fila de atendimento médico-----");
    int opcao = 0;
    while(opcao != 9){
        printf("\n\nO que deseja fazer?\n");
        printf("1. Gerenciar banco de pacientes\n");
        printf("2. Inserir paciente na fila\n");
        printf("3. Buscar um paciente na fila\n");
        printf("4. Remover um paciente da fila\n");
        printf("5. Ver a fila completa\n");
        printf("6. Chamar próximo paciente\n");
        printf("9. Sair do programa\n");

        scanf("%d", &opcao);
        limparBuffer();
        
        switch (opcao){

            case 1:
                gerenciarBancoPacientes(&bancoDados, &gerenciadorFila);
                break;

            case 2:
                Elemento *noDB = buscarPaciente(&bancoDados);
                Paciente *pacienteInserir;
                if(noDB != NULL){
                    pacienteInserir = noDB->paciente;
                }else{
                    break;
                }
                
                if(pacienteInserir != NULL){
                    Elemento *novoNo = inicializarElemento();
                    novoNo->paciente = pacienteInserir;
                    novoNo->prioridade = definirPrioridade();
                    inserirPorPrioridade(&gerenciadorFila, novoNo);
                } 
                break;
                
            
            case 3:
                Elemento *encontrado = buscarPaciente(&gerenciadorFila);
                if(encontrado !=NULL){
                    imprimirPacienteFila(encontrado);
                }
                break;

            case 4:
                Elemento *excluir = buscarPaciente(&gerenciadorFila);
                if(excluir !=NULL){
                    excluirPaciente(excluir, &gerenciadorFila, false);
                    printf(ANSI_COLOR_GREEN "Paciente removido com sucesso!\n" ANSI_COLOR_RESET);
                }
                break;

            case 5:
                imprimirFila(&gerenciadorFila);
                break;

            case 6:
                chamarPaciente(&gerenciadorFila);
                break;

            case 9:
                printf("Finalizando programa...");
                exit(0);

            case 99:
                //Opção oculta, para testes
                testes(&bancoDados, &gerenciadorFila);
                printf("\nRodando inserções de teste\n");
                break;

            default:
                printf(ANSI_COLOR_RED "Opção inválida, tente novamente...\n" ANSI_COLOR_RESET);
                break;
        }
    }
    
}