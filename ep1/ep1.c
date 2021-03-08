#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_INFO 64

typedef struct node{
  struct node * proximo;
  struct node * antescessor;
  char  info[TAM_INFO];
}Node;

typedef struct cabecaLista {
  struct node * iniLista;
  struct node * fimLista;
} CabecaLista;

void adicionarNode(CabecaLista* lista, char info[]){
  if(lista->iniLista == NULL || lista->fimLista == NULL){
    Node* node;
    node = malloc(sizeof(node));
    node->proximo = NULL;
    node->antescessor = NULL;
    strcpy(node->info, info);
    lista->iniLista = (Node*) node;
  }
}

void printaLista(CabecaLista lista, Node* nodeAtual){
  //while(nodeAtual->proximo != NULL){
    printf("%x", (Node*) lista->iniLista);
    printf("%c", (char) nodeAtual->info);
    //return printaLista(lista, nodeAtual->proximo);
  //}
    //printf("%s", nodeAtual->info);
    return;
}

int main (void){
  struct cabecaLista lista;
  char info[TAM_INFO] = {'R', 'A'};
  adicionarNode(&lista, info);

  printaLista(lista, lista.iniLista);

  return 0;
}