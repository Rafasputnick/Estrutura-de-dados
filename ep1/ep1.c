#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
  strcpy(node->info,info);
  node->proximo = node->antescessor = NULL;
  return node;
}

Lista adicionarNome(Lista lista, char info[TAM_INFO]){
  ponteiroNode node = criaNode(info);

  if(lista->iniLista == NULL) lista->fimLista = NULL;
  else node->proximo = lista->iniLista;
  
  lista->iniLista = node;

  return lista;
}

void printaLista(ponteiroNode nodeAtual){  
  if(nodeAtual == NULL) return;
  printf("%s", nodeAtual->info);
  printaLista(nodeAtual->proximo);
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
      adicionarNome(lista,nome);
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
      printf("como inserir, deletar, printar ou quit");
      break;
  }

  return 1; //qualquer opcao sem ser o q(uit) para sair
}

void printarMenuOpcoes(){
  printf("Qual instrucao voce deseja realizar?\n\n");
  printf("i nome- insere um nome na lista\n");
  printf("d nome- deleta um nome da lista\n");
  printf("p - mostra como esta a lista\n");
  printf("q - sair\n\n");
}

/* Funcao main (principal)
**/
int main (void){
  char instrucaoENome[TAM_INSTRUCAO_E_NOME];
  int condicaoWhile;

  Lista lista = iniciaLista();

  printf("Lista de nomes\n\n");
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