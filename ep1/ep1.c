#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "str.h"

/*
 * Variaveis globais para metodos de insercao 
**/

int possuiPredefinicao = 0;
char insercaoPreDefinida;

/* 
 ** Constantes
**/

/* Tamanho da array instrucoes e nomes 
 * eh preciso tratar ela e separar em duas strings
**/
#define TAM_INSTRUCAO_E_NOME 100 

/* Tamanho da string de nome exigida no enunciado
**/
#define TAM_INFO 64

/* Tamanho para a string de escolher metodo de insercao
 * ate 9 digitos para o metodo 1 para o espaco e ate outros 3 para escolher
 * se ja deixa definido e outro para marcar o final da string
 * '\0'
**/
#define TAM_METODO_INSERCAO 13

/*
 ** Tipos criados
**/

typedef struct node{
  struct node * proximo;
  struct node * antescessor;
  char  info[TAM_INFO];
}Node;

typedef Node* ponteiroNode;


typedef struct cabecaLista {
  struct node * iniLista;
  struct node * fimLista;
} CabecaLista;

typedef CabecaLista* Lista;


/*
 ** Funcoes de manipulacao da lista
**/

Lista iniciaLista(){
  Lista lista;
  lista = malloc(sizeof (CabecaLista));
  lista->iniLista = lista->fimLista = NULL;
  return lista;
}

ponteiroNode criaNode(char info[TAM_INFO]){
  ponteiroNode node;
  node = malloc(sizeof (Node));
  //copia string para a info do node
  copiaString(node->info,info);
  node->proximo = node->antescessor = NULL;
  return node;
}

void adicionarPrimeiroNode(Lista lista, char info[TAM_INFO]){
  ponteiroNode node = criaNode(info);

  lista->iniLista = node;  
  lista->fimLista = node;

  node->antescessor = NULL;
  node->proximo = NULL;
}

void adicionarNomeInicio(Lista lista, char info[TAM_INFO]){
  //criando um node novo
  ponteiroNode node = criaNode(info);

  //o atributo do node (proximo) recebe o valor do atual inicio da lista
  node->proximo = lista->iniLista; 
  
  //node atual tem o antescessor nulo
  node->antescessor = NULL;
  
  //o inicio da lista passa a ser o node criado
  lista->iniLista = node;

  //adicionando antescessor
  ponteiroNode aux = node; //guardando o endereco do node atual
  node = node->proximo; //o node passa a ser o proximo do node criado (antigo iniciaLista)
  node->antescessor = aux; //o node prox recebe o endereco do node criado
}


void adicionarNomeFinal(Lista lista, char info[TAM_INFO]){
  //criando um node novo
  ponteiroNode node = criaNode(info);

  //o atributo do node (antescessor) recebe o valor do atual fim da lista
  node->antescessor = lista->fimLista; 
  
  //node atual tem o proximo nulo
  node->proximo = NULL;
  
  //o fim da lista passa a ser o node criado
  lista->fimLista = node;

  //adicionando o proximo
  ponteiroNode aux = node; //guardando o endereco do node atual
  node = node->antescessor; //o node passa a ser o antescessor do node criado (antigo fimLista)
  node->proximo = aux; //o node antescessor recebe o endereco do node criado
}

int primeiroNode(Lista lista){
  if(lista->iniLista == NULL) return 1;
  else return 0;
}

/*
 ** Funcoes para liberar a lista
**/

void liberaNos (ponteiroNode nodeAtual) {
  if (nodeAtual == NULL) return;
  liberaNos(nodeAtual->proximo);
  free(nodeAtual); 
}

void liberaLista(Lista lista){
  if(lista->iniLista != NULL) liberaNos(lista->iniLista);
  free(lista);
}

/*
 ** Funcoes do menu
**/


void printaLista(ponteiroNode nodeAtual){  
  if(nodeAtual == NULL) return;
  printf("%s", nodeAtual->info);
  printaLista(nodeAtual->proximo);
}

void printarMenuInsercao(){
  printf("-----------------------------------------------------------------------------------\n");
  printf("Escolha uma opcao de insercao\n\n");
  
  printf("Para inserir no inicio:\n");
  printf(">inicio\n\n");
  
  printf("Para inserir no final:\n");
  printf(">final\n\n");
  
  printf("Para inserir de forma ordenada:\n");
  printf(">ordenada\n\n");

  printf("Voce tambem pode deixar pre-selecionado ate o final da execucao do programa:\n");
  printf(">inicio sim\n\n");

  printf("Voce pode usar as formas simplificadas tambem como nos exemplos abaixo:");
  printf("\n>i s");
  printf("\n>i\n");
  printf("-----------------------------------------------------------------------------------\n\n");
}

void controleDeInsercoes(char tipoInsercao, Lista lista, char info[TAM_INFO]){
  if(primeiroNode(lista)) return adicionarPrimeiroNode(lista,info);

  switch(tipoInsercao){
    case'i':
      adicionarNomeInicio(lista,info);
      break;

    case'f':
      adicionarNomeFinal(lista,info);
      break;

    case'o':

      break;
  }
}

void selecionarMetodoInsercao(Lista lista, char info[TAM_INFO]){
  if(possuiPredefinicao){
    controleDeInsercoes(insercaoPreDefinida, lista, info);
  }else{
    printarMenuInsercao();
    
    char tipoInsercao[TAM_METODO_INSERCAO-1]; //desconsiderando o espaco para o fim da string '\0'
    fgets(tipoInsercao,TAM_METODO_INSERCAO,stdin);
    
    int i;
    for(i=0; !isspace(tipoInsercao[i]) ;i++);
    //quando sai dessa estrutura de repeticao significa que achamos o primeiro espaco
    
    //cria um ponteiro de char para receber a substring apos o primeiro espaco
    char* predefinicao;
    predefinicao = &tipoInsercao[i+1]; //recebe substring com o dado sobre a predefinicao 
    
    if(predefinicao[0] == 's'){
      possuiPredefinicao = 1;
      insercaoPreDefinida = tipoInsercao[0];
    }
    
    controleDeInsercoes(tipoInsercao[0], lista, info);
  }
  printf("\n");
}

int tratarInstrucaoENome(char str[], Lista lista){
  int i;  
  for(i=0; !isspace(str[i]) ;i++);
  //quando sai dessa estrutura de repeticao significa que achamos o primeiro espaco

  //cria um ponteiro de char para receber a substring apos o primeiro espaco
  char* nome;
  nome = &str[i+1]; //recebe substring com a info(nome) para alocar na lista 

  /*o indice zero da str recebida guarda o dado necessario para saber
  * qual funcao realizar por exemplo em inserir o i ja eh sufiente 
  * para saber que se deseja inserir na lista
  * i(nsert) d(elete) p(rint) e q(uit)
  */
  switch(str[0]){
    case 'i':
      selecionarMetodoInsercao(lista,nome);
      break;

    case 'd':
      break;

    case 'p':
      printf("A lista esta:\n");
      printaLista(lista->iniLista);
      printf("\n\n");
      break;

    case 'q':
      return 0;

    default:
      printf("Eh preciso digitar alguma instrucao que comece com i ,d ,p ou q\n");
      printf("como inserir, deletar, printar ou quit\n");
      break;
  }

  return 1; //qualquer opcao sem ser o q(uit) para sair
}

void printarMenuOpcoes(){
  printf("-----------------------------------------------------------------------------------\n");
  printf("Qual instrucao voce deseja realizar?\n\n");
  printf("Para inserir um nome na lista:\n");
  printf(">inserir nome\n\n");
  printf("Para deletar um nome da lista:\n");
  printf(">deletar nome\n\n");
  printf("Para mostrar como esta a lista:\n");
  printf(">print\n");
  printf("\nPara sair\n");
  printf(">quit");
  printf("\n\nVoce pode usar as formas simplificadas tambem como nos exemplos abaixo:");
  printf("\n>i nome");
  printf("\n>d nome");
  printf("\n>p\n");
  printf("-----------------------------------------------------------------------------------\n\n");
}


/* Funcao main (principal)
**/
int main (void){
  char instrucaoENome[TAM_INSTRUCAO_E_NOME];
  int condicaoWhile;

  Lista lista = iniciaLista();

  printf("Lista de nomes\n");
  do {
    printarMenuOpcoes();

    //eh preciso somar um pois esta incluido o final da leitura '\0'
    fgets(instrucaoENome,(TAM_INSTRUCAO_E_NOME + 1),stdin);  
    printf("\n");
    
    condicaoWhile = tratarInstrucaoENome(instrucaoENome,lista);
  }while(condicaoWhile);

  printf("Tchau!");
  liberaLista(lista);
  return 0;
}