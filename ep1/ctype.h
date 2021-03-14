////////////////////////////////////////////////////////////////////////////////////////
/*          Biblioteca construida com base na biblioteca <ctype.h>                     */
/*                        Funcoes similares as seguintes                               */
/*                                    isspace                                          */
/*                                 temValorVazio                                       */
/*                                                                                     */
/*                  Desenvolvido por Rafael Nascimento Lourenco                        */
////////////////////////////////////////////////////////////////////////////////////////


#pragma once


/* Funcao temValorVazio (Tem valor vazio) - Similar a isspace()
 * 
 * Retorna um valor inteiro representando simulando um boolean
 *
 * Recebe uma variavel simples do tipo char
 *
 * Tem como funcao verificar se o valor contido no char eh vazio ou nao
**/
int temValorVazio( char a ){
  if( a == ' ' || a == '\n' || a == '\t' || a == '\v' || a == '\f' || a == '\r' ) return 1;
  else return 0;
}