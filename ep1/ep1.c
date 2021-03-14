////////////////////////////////////////////////////////////////////////////////////////
/*                  Exercicio Programa 1 de Estrutura de dados                         */
/*              Objetivo: Construir uma lista ligada que guarda nomes                  */
/*                              Principais funcoes:                                    */
/*              Inserir de forma ordenada, deletar nome e printar lista                */
/*                                                                                     */
/*                  Desenvolvido por Rafael Nascimento Lourenco                        */
////////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include "ctype.h"
#include "string.h"


/* 
 ** Constantes
**/

/* Tamanho da array instrucoes e nomes 
 * eh preciso tratar ela e separar em duas strings
**/
#define TAM_INSTRUCAO_E_NOME 100 

/* Tamanho da string de nome exigida no enunciado
**/
#define TAM_NOME 64

/* Tamanho para a string de escolher metodo de insercao
 * ate 9 digitos para o metodo 1 para o espaco e ate outros 3 para escolher
 * se ja deixa definido e outro para marcar o final da string
 * '\0'
**/
#define TAM_METODO_INSERCAO 13

/*
 ** Tipos criados
**/

/* Tipo estruturado de no ou node em ingles
**/
typedef struct node{
  struct node * proximo;
  struct node * antescessor;
  char  nome[TAM_NOME];
}Node;

// Ponteiro do node
typedef Node* ponteiroNode;

/* Tipo estruturo da cabeca da lista
**/
typedef struct cabecaLista {
  struct node * iniLista;
  struct node * fimLista;
} CabecaLista;

// ponteiro da cabeca da lista
typedef CabecaLista* Lista;


/*
 ** Funcoes de manipulacao da lista
**/

/* Funcao iniciaLista (Inicia Lista)
 * 
 * Retorna um ponteiro de cabecaLista (Lista)
 *
 * Recebe um tipo Lista (ponteiro de cabecaLista)
 *
 * Tem como funcao setar os valores iniciais de uma lista (Ponteiros nulos)
**/
Lista iniciaLista(){
  Lista lista;
  lista = malloc(sizeof (CabecaLista));
  lista->iniLista = lista->fimLista = NULL;
  return lista;
}

/* Funcao criaNode (Criar Node)
 * 
 * Retorna um ponteiroNode
 *
 * Recebe um ponteiro do tipo char(uma string)
 *
 * Tem como funcao criar um no com a info e ponteiros nulos
**/
ponteiroNode criaNode(char info[TAM_NOME]){
  ponteiroNode node;
  node = malloc(sizeof (Node));
  //copia string para a info do node
  copiaString(node->nome,info);
  node->proximo = node->antescessor = NULL;
  return node;
}

/* Funcao adicionarPrimeiroNode (Adicionar Primeiro Node)
 * 
 * Retorna void pois trata diretamente nos enderecos de memoria
 *
 * Recebe um ponteiro do tipo char(uma string) e um ponteiro de cabecaLista (Lista)
 *
 * Tem como funcao alocar o primeiro node a uma lista vazia
**/
void adicionarPrimeiroNode(Lista lista, char info[TAM_NOME]){
  ponteiroNode node = criaNode(info);

  lista->iniLista = node;  
  lista->fimLista = node;

  node->antescessor = NULL;
  node->proximo = NULL;

  printf("O nome foi inserido com sucesso\n\n");
}

/* Funcao adicionarNomeInicio (Adiciona Nome No Inicio)
 * 
 * Retorna void pois trata diretamente nos enderecos de memoria
 *
 * Recebe um ponteiro do tipo char(uma string) e um ponteiro de cabecaLista (Lista)
 *
 * Tem como funcao inserir um nome no inicio da lista
**/
void adicionarNomeInicio(Lista lista, char info[TAM_NOME]){
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

  printf("O nome foi inserido com sucesso\n\n");
}


/* Funcao adicionarNomeFinal (Adiciona Nome No Final)
 * 
 * Retorna void pois trata diretamente nos enderecos de memoria
 *
 * Recebe um ponteiro do tipo char(uma string) e um ponteiro de cabecaLista (Lista)
 *
 * Tem como funcao inserir um nome no final da lista
**/
void adicionarNomeFinal(Lista lista, char info[TAM_NOME]){
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

  printf("O nome foi inserido com sucesso\n\n");
}


/* Funcao adicionarNomeEmOrdem (Adiciona Nome Em Ordem)
 * 
 * Retorna void pois trata diretamente nos enderecos de memoria
 *
 * Recebe um ponteiro do tipo char(uma string) e um ponteiro de cabecaLista (Lista)
 *
 * Tem como funcao inserir um nome de forma ordenada na lista
**/
void adicionarNomeEmOrdem(Lista lista, char info[TAM_NOME]){
  //Verificando casos especiais no qual o valor sera nas pontas, alterando o iniciaListae ou fimLista
  //obs: quando retorna 1 significa que a ordem esta certa e -1 esta invertida
  if( comparaString( info , lista->iniLista->nome ) >= 0 ) return adicionarNomeInicio(lista,info);
  if( comparaString( lista->fimLista->nome , info) >= 0 ) return adicionarNomeFinal(lista,info);

  ponteiroNode aux;
  for ( aux = lista->iniLista; (comparaString( info , aux->proximo->nome ) < 0) ; aux = aux->proximo );
  //quando parar significa que o valor da info eh maior que o anterior e menor que o proximo

  ponteiroNode node;
  node = criaNode(info);

  node->antescessor = aux;
  node->proximo = aux->proximo;

  node->antescessor->proximo = node;
  node->proximo->antescessor = node;

  printf("O nome foi inserido com sucesso\n\n");
}


/* Funcao verificarSeHaNomeLista (Verificar se ha o Nome Informado na Lista )
 * 
 * Retorna int para simular um boolean (0 - false e 1 - true)
 *
 * Recebe um ponteiro do tipo char(uma string) e um ponteiro de cabecaLista (Lista)
 *
 * Tem como funcao verificar a existencia do nome informado na lista
**/
int verificarSeHaNomeLista(Lista lista, char nome[TAM_NOME]){
  if(lista->iniLista != NULL){
    ponteiroNode aux;
    for( aux = lista->iniLista; aux != NULL; aux = aux->proximo){
      if ( comparaString( aux->nome , nome ) == 0 ) return 1;
    }
  }
  return 0;
}

/* Funcao deletaInicio (Deletar Inicio)
 * 
 * Retorna void pois trata diretamente nos enderecos de memoria
 *
 * Recebe um ponteiro do tipo char(uma string) e um ponteiro de cabecaLista (Lista)
 *
 * Tem como funcao deletar um nome no inicio da lista
**/
void deletarInicio(Lista lista, char nome[TAM_NOME]){
  ponteiroNode node;
  node = lista->iniLista;

  lista->iniLista = node->proximo; // o iniciaLista rebebe o iniciaLista->proximo
  node->proximo->antescessor = NULL; // o antescessor do proximo ao iniciaLista recebe nulo

  free(node);

  printf("O nome foi deletado com sucesso\n\n");
}


/* Funcao deletarFinal (Deletar Final)
 * 
 * Retorna void pois trata diretamente nos enderecos de memoria
 *
 * Recebe um ponteiro do tipo char(uma string) e um ponteiro de cabecaLista (Lista)
 *
 * Tem como funcao deletar um nome no fim da lista
**/
void deletarFinal(Lista lista, char nome[TAM_NOME]){
  ponteiroNode node;
  node = lista->fimLista;

  lista->fimLista = node->antescessor; // o fimLista rebebe o fimLista->antescessor
  node->antescessor->proximo = NULL; // o proximo do antescessor ao fimLista recebe nulo

  free(node);

  printf("O nome foi deletado com sucesso\n\n");
}

/* Funcao unicoElementoDaLista (Unico Elemento da Lista)
 * 
 * Retorna int simulando um boolean (0 - false e 1 - true)
 *
 * Recebe um ponteiro de cabecaLista (Lista)
 *
 * Tem como funcao verificar se a lista possui um unico elemento
**/
int unicoElementoDaLista(Lista lista){
  if ( lista->iniLista->proximo == NULL ) return 1;
  else return 0;
}

/* Funcao deletaUnicoElemento (Deleta Unico Elemento da Lista)
 * 
 * Retorna void pois trata diretamente nos enderecos de memoria
 *
 * Recebe um ponteiro de cabecaLista (Lista)
 *
 * Tem como funcao remover o unico nome da lista
**/
void deletaUnicoElemento(Lista lista){
  ponteiroNode nodeADeletar;
  nodeADeletar = lista->iniLista;

  free(nodeADeletar);

  lista->iniLista = NULL;
  lista->fimLista = NULL; 

  printf("O nome foi deletado com sucesso\n\n");
}


/* Funcao deletarNome (Deletar Nome)
 * 
 * Retorna void pois trata diretamente nos enderecos de memoria
 *
 * Recebe um ponteiro do tipo char(uma string) e um ponteiro de cabecaLista (Lista)
 *
 * Tem como funcao deletar um nome na lista
**/
void deletarNome(Lista lista, char nome[TAM_NOME]){
  
  if (verificarSeHaNomeLista(lista,nome) == 0){
    printf("O nome informado nao existe na lista\n\n");
    return;
  }

  //caso ultra especial no qual o elemento a ser deletado eh o unico da lista
  if ( unicoElementoDaLista(lista) ) return deletaUnicoElemento(lista);

  //Verificando casos especiais no qual o valor sera nas pontas, alterando o iniciaListae ou fimLista
  //obs: quando retorna 0 significa que as strings sao iguais
  if( comparaString( lista->iniLista->nome , nome ) == 0 ) return deletarInicio(lista,nome);
  if( comparaString( lista->fimLista->nome , nome ) == 0 ) return deletarFinal(lista,nome);

  ponteiroNode aux;
  for ( aux = lista->iniLista; comparaString( aux->proximo->nome , nome ) != 0 ; aux = aux->proximo );
  //quando se termina essa estrutura significa que o proximo node tem que ser deletado

  ponteiroNode nodeADeletado; //node que sera deletado
  nodeADeletado = aux->proximo;

  aux->proximo = nodeADeletado->proximo;
  nodeADeletado->proximo->antescessor = aux;

  free(nodeADeletado);

  printf("O nome foi deletado com sucesso\n\n");
}


/* Funcao primeiroNode (Primeiro Node)
 * 
 * Retorna int simulando um boolean (0 - false e 1 - true)
 *
 * Recebe um ponteiro de cabecaLista (Lista)
 *
 * Tem como funcao verificar a existencia de 2 ou mais nodes na lista 
**/
int primeiroNode(Lista lista){
  if(lista->iniLista == NULL) return 1;
  else return 0;
}

/*
 ** Funcoes para liberar a lista
**/


/* Funcao liberaNos (Libera Nos)
 * 
 * Retorna void pois trata diretamente nos enderecos de memoria
 *
 * Recebe um ponteiroNode 
 *
 * Tem como funcao dar free em todos os nodes da lista de forma recursiva
**/
void liberaNos (ponteiroNode nodeAtual) {
  if (nodeAtual == NULL) return;
  liberaNos(nodeAtual->proximo);
  free(nodeAtual); 
}


/* Funcao liberaLista (Libera Lista)
 * 
 * Retorna void pois trata diretamente nos enderecos de memoria
 *
 * Recebe um ponteiro de cabecaLista (Lista)
 *
 * Tem como funcao dar free na lista
**/
void liberaLista(Lista lista){
  if(lista->iniLista != NULL) liberaNos(lista->iniLista);
  free(lista);
}

/*
 ** Funcoes do menu
**/


/* Funcao printaLista (Printa Lista)
 * 
 * Retorna void pois apenas serve para printar algo na tela
 *
 * Recebe ponteiroNode
 *
 * Tem como funcao printar a lista
**/
void printaLista(ponteiroNode nodeAtual){  
  if(nodeAtual == NULL) return;
  printf("%s", nodeAtual->nome);
  printaLista(nodeAtual->proximo);
}


/* Funcao tratarInstrucaoENome (Tratar Funcao E Nome)
 * 
 * Retorna int pois simula um boolean (0 - false e 1 - true)
 *
 * Recebe um ponteiro do tipo char(uma string) e um ponteiro de cabecaLista (Lista)
 *
 * Tem como funcao tratar a string fornecida pelo usuario e encaminha-las para determinadas funcoes
**/
int tratarInstrucaoENome(char str[], Lista lista){
  int i;  
  for(i=0; !temValorVazio(str[i]) ;i++);
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
      if(primeiroNode(lista)) adicionarPrimeiroNode(lista,nome);
      else adicionarNomeEmOrdem(lista,nome);
      break;

    case 'd':
      deletarNome(lista,nome);
      break;

    case 'p':
      if(lista->iniLista == NULL){ 
        printf("A lista de nomes esta vazia");
      }else{
        printf("A lista de nomes esta:\n");
        printaLista(lista->iniLista);
      }  
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


/* Funcao printarMenuOpcoes (Printa Menu De Opcoes)
 * 
 * Retorna void pois apenas serve para printar algo na tela
 *
 * Nao recebe argumento
 *
 * Tem como funcao printar o menu de opcoes
**/
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

/*
 ** Funcao main (principal)
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