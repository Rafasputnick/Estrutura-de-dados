#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_INFO 64

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

CabecaLista iniciaLista(){
  CabecaLista lista;
  lista.iniLista = lista.fimLista = NULL;
  return lista;
}

ponteiroNode criaNode(char info[TAM_INFO]){
  ponteiroNode node;
  node = malloc(sizeof (Node));
  //copia string para a info do node
  strcpy(node->info,info);
  node->proximo = node->antescessor = NULL;
  return node;
}

CabecaLista adicionarNode(CabecaLista lista, char info[TAM_INFO]){
  ponteiroNode node = criaNode(info);

  if(lista.iniLista == NULL) lista.fimLista = NULL;
  else node->proximo = lista.iniLista;
  
  lista.iniLista = node;

  return lista;
}

void printaLista(ponteiroNode nodeAtual){  
  if(nodeAtual == NULL) return;
  printf("%s ", nodeAtual->info);
  printf("\n");
  printaLista(nodeAtual->proximo);
}

void liberaLista(ponteiroNode nodeAtual) {
  if (nodeAtual == NULL) return;
  liberaLista(nodeAtual->proximo);  // libera o restante
  free(nodeAtual); 
}

int main (void){
  struct cabecaLista lista = iniciaLista();
  char instrucao;
  char info[TAM_INFO]; 
  printf("Lista de nomes\n\n");
  
  do{

    printf("Qual instrucao voce deseja realizar?\n\n");
    printf("i nome- insere um nome na lista\n");
    printf("d nome- deleta um nome da lista\n");
    printf("p - mostra como esta a lista\n");
    printf("q - sair\n\n");

    scanf("%c\n", &instrucao);

    switch(instrucao){
      case 'i':
        scanf("%s", info);
        adicionarNode(lista,info);
        break;
      case 'd':
        break;
      case 'p':
        printaLista(lista.iniLista);
        break;
      case 'q':
        break;
      default:
        break;
    }
    getchar();
  }while(instrucao != 'q');
  
  printaLista(lista.iniLista);

  printf("Tchau!");
  liberaLista(lista.iniLista);
  return 0;
}