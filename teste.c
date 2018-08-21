
// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Linhas auxiliares para impressao do menu
char linhaMenu[] = "\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\n";
char linhaOpcoes[] = "\t\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\n";

// Estrutura de dados de uma Proprietario
typedef struct cadastro{
    char nome[101];
    char CPF[12];
    char marca[101];
    char modelo[11];
}Proprietario;

// Estrutura de dados de uma lista dinamica duplamente encadeada
typedef struct node{
    struct node *ant;
    Proprietario * info;
    struct node *prox;
}NodeLista;


// Prototipos das funcões
NodeLista *inicializa();
NodeLista *insereNoInicio(NodeLista * , char *, char *, char *, char *);
NodeLista *buscaNome(NodeLista *, char *);
NodeLista *removeCadastro(NodeLista *, char *);
void visualizaPorNome(NodeLista *, char *);
void visualizaTudo(NodeLista *);
NodeLista *arquivoParaLista(NodeLista *);
void listaParaArquivo(NodeLista *);
void menu();
void menuEscolha(int);
NodeLista *inserirCadastro(NodeLista *);
void saida(NodeLista *);
char *insereNome();
NodeLista *insertionSort(NodeLista *);
void liberaLista(NodeLista *);


int main(){ //Funcao main()
    NodeLista *l;
    int escolha = 1;
    l = inicializa();
    l = arquivoParaLista(l);

// Menu do programa
    do {

        // imprime o texto do menu principal
        menu();

        scanf("%d", &escolha);

        // Limpa a telaapos a escolha da funcao
        system("cls");

        //Escolha do menu principal
        switch(escolha){

            case 1: // Inserir novo registro

                printf("%s", linhaOpcoes);
                printf("\t\xBA                          \xBA\n");
                printf("\t\xBA  Inserir novo cadastro   \xBA \n");
                printf("\t\xBA                          \xBA\n");
                printf("%s", linhaOpcoes);
                l = inserirCadastro(l);
                break;

            case 2: // Remover registros que possuem certo nome

                printf("%s", linhaOpcoes);
                printf("\t\xBA                          \xBA\n");
                printf("\t\xBA     Excluir cadastro     \xBA \n");
                printf("\t\xBA                          \xBA\n");
                printf("%s", linhaOpcoes);
                printf("\n\nNome do proprietario a ser excluido : ");
                l = removeCadastro(l,insereNome());
                break;

            case 3: // Visualizar registros em ordem alfabetica de acordo com o nome

                printf("%s", linhaOpcoes);
                printf("\t\xBA                          \xBA\n");
                printf("\t\xBA     Buscar cadastro      \xBA \n");
                printf("\t\xBA                          \xBA\n");
                printf("%s", linhaOpcoes);
                printf("\n\nNome do cadastro a ser buscado: ");
                visualizaPorNome(l,insereNome());
                break;

            case 4: // Visualizar todos os registros em ordem alfabetica de acordo com o nome

                printf("%s", linhaOpcoes);
                printf("\t\xBA                          \xBA\n");
                printf("\t\xBA    Lista de cadastros    \xBA \n");
                printf("\t\xBA                          \xBA\n");
                printf("%s\n", linhaOpcoes);
                visualizaTudo(l);
                break;

            case 0: // Finalizar o programa

                saida(l);
                break;

            default:
                printf("Digite uma opcao valida!\n");

        }
    } while(escolha);

    return 0;
}

NodeLista *inicializa(){ // Funcao que inicializa a lista vazia

    // Alocação dinamica da lista
    NodeLista *no = (NodeLista*)malloc(sizeof(NodeLista));

    // Setando todos os elementos nulo da Lista
    no->prox = NULL;
    no->ant = NULL;
    no->info = NULL;

    return no;
}

// Função que insere um novo cadastro da Proprietario no inicio da lista
NodeLista* insereNoInicio(NodeLista* lista, char* nome, char* CPF, char* marca, char* modelo){
    Proprietario* ag;
    NodeLista* novoNo;

    ag = (Proprietario*) malloc(sizeof(Proprietario));

    if (ag == NULL){ // Verifica se tem memória suficiente disponível
        printf("Memoria insuficiente!\n");
        exit(1);
    }
    // Preenchendo a Proprietario
    strcpy(ag->nome,nome);
    strcpy(ag->CPF,CPF);
    strcpy(ag->marca,marca);
    strcpy(ag->modelo,modelo);

    novoNo = (NodeLista *)malloc(sizeof(NodeLista));

    // Adicionando um novo elemneto de Proprietario na Lista
    novoNo->info = ag;
    novoNo->ant = NULL;
    novoNo->prox = lista;

    if(lista != NULL){
        lista->ant = novoNo;
    }

    return novoNo;
}



    // Função que busca o nome desejado na lista
    NodeLista *buscaNome(NodeLista *lista, char *nome){
    NodeLista *aux;

    // Percorre a lista a procura do nome desejado
    for(aux = lista; aux->info != NULL; aux = aux->prox){
        if(strcmp(aux->info->nome, nome) ==0){
            return aux;
        }
    }
    //printf("Cadastro Não encontrado!!\n");
    return NULL;
    }

    // Remove o contato desejado a partir do nome
    NodeLista *removeCadastro(NodeLista *lista, char *nome){
    // Chama a função busca nome para a pesquisa
    NodeLista *rCadastro = buscaNome(lista,nome);
    NodeLista *aux ;

    int i = 0;

    // Verifica se o nome digitado existe na Proprietario
    if(rCadastro == NULL){
        printf("\n\nCadastro não existe na base de dados!\n");
        getchar();
        printf("\n\nPressione 'Enter' para voltar ao menu principal\n");
        getchar();
        return lista;
    }

    // Método iterativo para contar quantos registros com o mesmo nome existe na Proprietario
    while(rCadastro != NULL){

        aux = rCadastro->prox;

        if(lista == rCadastro){
            lista = rCadastro->prox;
        } else{
            rCadastro->ant->prox = rCadastro->prox;
        }

        if(rCadastro != NULL){
            rCadastro->prox->ant = rCadastro->ant;
        }

        rCadastro = aux;

        rCadastro = buscaNome(lista,nome);

        i++;

    }

    // Pega a quantidade de iterações para informar quantos registros do banco de dados foram removidos
    printf("%d cadastro(s) removido(s) com sucesso!\n", i);

    // Funcão equivalente a system("pause") do windows;
    getchar();
    printf("\n\nPressione 'Enter' para voltar ao menu principal\n");
    getchar();

    free(rCadastro);

    return lista;
}

//Função que pega o nome e imprime o contato correspondente na tela;
void visualizaPorNome(NodeLista* lista, char* nome){
NodeLista *busca = buscaNome(lista,nome);

// Valida a existencia de um contato com o respectivo nome
if(busca == NULL){

    printf("Cadastro Não encontrado!!\n");
    getchar();
    printf("\n\nPressione 'Enter' para voltar ao menu principal\n");
    getchar();

}else{
    // Imprime na tela o cadastro correspondente ao nome desejado (se existir)
    printf("\n\nContato encontrado!\n");
    printf("Nome: %s\n",busca->info->nome);
    printf("CPF: %s\n",busca->info->CPF);
    printf("Marca: %s\n",busca->info->marca);
    printf("Modelo: %s\n",busca->info->modelo);

    // Funcão equivalente a system("pause") do windows;
    getchar();
    printf("\n\nPressione 'Enter' para voltar ao menu principal\n");
    getchar();

}
}

// Imprime na tela a Proprietario completa com todos os contatos cadastrados
void visualizaTudo(NodeLista *lista){
NodeLista* aux = lista;

// Verifica se existe lista
if(lista==NULL){
    printf("Sem espaço suficiente na memoria para gerar uma lista!\nPrograma finalizado!");
    exit(1);
}

// Verifica se existe alguma informacao na lista
if(lista -> info == NULL){
    printf("Nenhum cadastro encontrado!\n");
}

// Metodo iterativo para perccorrer a lista até o final e imprime na tela
while(aux->prox != NULL){
    printf("\nNome: %s\n",aux->info->nome);
    printf("CPF: %s\n",aux->info->CPF);
    printf("marca: %s\n",aux->info->marca);
    printf("Data de modelo: %s\n",aux->info->modelo);

    aux = aux->prox;
}

//Equivalente a system("PAUSE");
getchar();
printf("\n\nPressione 'Enter' para voltar ao menu principal\n");
getchar();

}


// Funcao que pega os dados do arquivo para a lista
NodeLista *arquivoParaLista(NodeLista* lista){

FILE *arquivo;

char nome[101] = "N";
char CPF[12];
char marca[101];
unsigned int cep;
char modelo[11];
char cifrao = 'C';
int i;
char n;

// Abertura do arquivo
arquivo = fopen("contatos.txt","a+");

 fscanf(arquivo," %[^\n]",nome);
    getc(arquivo);

    if(strcmp(nome,"N")!= 0){

        rewind(arquivo);

while(!feof(arquivo)){// Equanto não chega ao final do arquivo

    //Pega os dados de cada linha do arquivo
    fscanf(arquivo," %[^\n]",nome);
    getc(arquivo);

    fscanf(arquivo,"%s",CPF);
    getc(arquivo);

    fscanf(arquivo," %[^\n]",marca);
    getc(arquivo);

    fscanf(arquivo,"%d",&cep);
    getc(arquivo);

    fscanf(arquivo," %[^\n]",modelo);
    getc(arquivo);

    fscanf(arquivo,"%c",&cifrao);
    getc(arquivo);


    lista = insereNoInicio(lista,nome,CPF,marca,modelo);

}
}
// Fecahmento do arquivo
fclose(arquivo);
return lista;
}

// Função que passa os dados de contatos do programa para o arquivo no final da execução do programa
void listaParaArquivo(NodeLista *lista){

FILE *arquivo;
NodeLista *aux = lista;

// Abertura do arquivo
arquivo = fopen("contatos.txt","w+");

//Enquanto não chega ao ultimo cadastro
while(aux->prox != NULL){

    // Imprime os dados cadastrais no arquivo
    fprintf(arquivo, "%s\n",aux->info->nome);
    fprintf(arquivo, "%s\n",aux->info->CPF);
    fprintf(arquivo, "%s\n",aux->info->marca);
    fprintf(arquivo, "%s\n",aux->info->modelo);
    fprintf(arquivo, "%c\n",'$');

    // Incremento para o proximo elemento da lista
    aux = aux->prox;

}

//Fechamento do arquivo
fclose(arquivo);
}

// Função para impressão do menu principal
void menu(){
// Limpa a tela do terminal
system("cls");

printf("%s", linhaMenu);
printf("\xBA                                 \xBA\n");
printf("\xBA  1. Inserir novo cadastro       \xBA \n");
printf("\xBA                                 \xBA\n");
printf("\xBA  2. Remover cadastro            \xBA \n");
printf("\xBA                                 \xBA\n");
printf("\xBA  3. Buscar cadastro             \xBA \n");
printf("\xBA                                 \xBA\n");
printf("\xBA  4. Visualizar cadastro         \xBA\n");
printf("\xBA                                 \xBA\n");
printf("\xBA                                 \xBA\n");
printf("\xBA  0. Sair do programa            \xBA \n");
printf("\xBA                                 \xBA\n");
printf("%s", linhaMenu);
printf("\n\n");
}

//Função que pega os dados de um cadastro e manda para a funcão que insere no inicio da lista
NodeLista* inserirCadastro(NodeLista *lista){

NodeLista *novoCadastro;
novoCadastro = lista;
char nome[101];
char CPF[12];
char marca[101];
char modelo[101];

//Pega os dados de cadastro do teclado
printf("\t\n\nNome: ");
scanf(" %[^\n]", nome);

printf("\nCPF: ");
scanf("%s", CPF);

printf("\nMarca: ");
scanf(" %[^\n]", marca);

printf("\nModelo: ");
scanf("%s", modelo);

//Funcao que insere os dados cadastrais no inicio da lista
novoCadastro = insereNoInicio(lista, nome, CPF, marca, modelo);

return novoCadastro;

}

//funcao que finaliza o programa
void saida(NodeLista* lista){
lista = insertionSort(lista);
listaParaArquivo(lista);
liberaLista(lista);
printf("\n\tObrigado por utilizar o programa! :)\n\n");
exit(1);
};

//Funcao que capta um nome para pesquisa na Proprietario
char *insereNome(){
char *nome;

nome = (char*)calloc(101,sizeof(char));

scanf(" %[^\n]",nome);

return nome;
}


NodeLista *insertionSort(NodeLista *lista){
    NodeLista *p;
    NodeLista *j;
    Proprietario *aux;

    for(p = lista->prox; p->prox != NULL ; p = p -> prox){
        aux = p->info;
        j = p->ant;

        while((j->ant != NULL)&&((strcmp(j->info->nome,aux->nome) < 0))){
            j->prox->info = j->info;
            j = j -> ant;
        }

        j->prox->info = aux;

    }

return lista;
}


void liberaLista(NodeLista *lista){
if(lista != NULL){
    NodeLista* aux;
    while(lista != NULL){
        aux = lista;
        lista = lista -> prox;
        free(aux);
    }
    free(lista);
}
}
