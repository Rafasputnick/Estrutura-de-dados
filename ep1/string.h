////////////////////////////////////////////////////////////////////////////////////////
/*          Biblioteca construida com base na biblioteca <string.h>                    */
/*                        Funcoes similares as seguintes                               */
/*                            strlen, strcmp, strcpy                                   */
/*                     tamanhoStr, comparaString  e copiaString                        */
/*                                                                                     */
/*                  Desenvolvido por Rafael Nascimento Lourenco                        */
////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

#pragma once

/* Funcao tamanhoStr (Tamanho da String) - Similar a strlen()
 * 
 * Retorna um valor inteiro representando o tamanho da string
 *
 * Recebe um ponteiro do tipo char(uma string)
 *
 * Tem como funcao calcular o tamanho de uma string
**/
int tamanhoStr(char a[]){
  int i;
  for(i=0; a[i] != '\0'; i++);
  /* Percorre a array de caracteres ate o seu fim
   * todo array de caracteres possui em seu final um valor '\0'
  **/
  return i;
}

/* Funcao menorTamanhoStrings (Menor Tamanho entre Strings) - Auxiliar para strAehMaiorQueStrB
 * 
 * Retorna um valor inteiro representando o menor tamanho 
 * entre as strings
 *
 * Recebe dois ponteiros do tipo char(duas strings)
 *
 * Tem como funcao retornar o tamnanho da menor string
**/
int menorTamanhoStrings(char a[], char b[]){
  int tamStrA = tamanhoStr(a);
  int tamStrB = tamanhoStr(b);
  if(tamStrA < tamStrB) return tamStrA;
  else return tamStrB;
}

/* Funcao strAehMaiorQueStrB (String a eh maior que a string b) - Auxiliar para comparaString
 * 
 * Retorna um valor inteiro
 * se retornar 1 significa que a ordem eh strA e dps strB
 * se retornar -1 significa que a ordem eh strB e dps srtA
 * para ser mais facil voce pode pensar assim
 * a orderm esta correta? retorna 1
 * a ordem esta invertida? retorna -1
 *
 * Recebe dois ponteiros do tipo char(duas strings) e o indice cujo 
 * valores anteriores a esse indice sao identicos nas duas strings
 * ou seja, eh o primeiro indice em comum com valores diferentes
 *
 * Tem como funcao retornar a ordem das strings
**/
int strAehMaiorQueStrB(char a[], char b[], int indiceIgual){
  if(a[indiceIgual] == '\0') return 1; //a ordem eh strA, strB 
  if (b[indiceIgual] == '\0') return -1; //a ordem eh strB, strA
  
  if(a[indiceIgual] > b[indiceIgual]) return -1; 
  else return 1;
}

/* Funcao comparaString (Compara Strings) - Similar a strcmp() 
 * 
 * Retorna um valor inteiro
 * se retornar 1 significa que a ordem eh strA e dps strB
 * se retornar -1 significa que a ordem eh strB e dps srtA
 * se retornar 0 significa que as strings sao iguais
 *
 * Recebe dois ponteiros do tipo char(duas strings) 
 * para compara-las
 * 
 * Tem como funcao retornar a ordem ou equalidade das strings
**/
int comparaString(char a[], char b[]){
  
  int i = 0;
  for(i=0; a[i] == b[i] && a[i] != '\0' && b[i] != '\0' ; i++);
  /* Quando essa estrutura de repeticao acaba significa que estamos
  * entre dois cenarios
  * se o valor do indice do a for diferente do valor do indice do b
  * ou se pelo menos uma das strings acabou '\0'
  */
  printf("%d", i);
  /* Caso chegue aqui com ambos das strings no final 
  * significa que as strings sao identicas em tamanho
  * e em seus valores
  */
  if( a[i] == '\0' && b[i] == '\0' ) return 0; //sao iguais
  else return strAehMaiorQueStrB(a,b, i); //sao diferentes
}

/* Funcao copiaString (Copia String) - Similar a strcpy()
 * 
 * Retorna void pois trabalha com ponteiros (enderecos de memoria)
 * 
 * Recebe dois ponteiros do tipo char
 *
 * O primeiro parametro entra no melhor caso quando eh passado
 * um ponteiro char com tamanho ainda nao definido, tambem nao aceita
 * uma string com valor ja definido anteriormente
 *
 * O segundo parametro pode ser tanto uma string com valor definido
 * quanto o valor em si entre aspas "valorStr"
 *
 * Tem como funcionalidade copiar o valor de uma string em um ponteiro de char 
**/
void copiaString(char a[], char b[]){
  int i;
  for(i=0; i < tamanhoStr(b); i++) a[i] = b[i];
  /* Em cada iteracao se copia o valor da string passada para 
   * copiar e aloca esse valor em um indice congruente
   * na string passada para ser a copia
  **/
}
