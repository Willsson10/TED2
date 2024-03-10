#ifndef _TIPOS_H
#define _TIPOS_H

#include "circulo.h"
#include "linha.h"
#include "retangulo.h"
#include "texto.h"

/* Modulo onde sao implementadas funcoes para conseguir acessar informacoes,
 * as quais, sao em comum entre circulos, linhas, retangulos e textos.
 *
 * Aqui tem funcoes para conseguir informacoes especificas de uma informacao,
 * de modo geral. Como o ID ou (x , y). Nao tendo que fazer funcoes especificas
 * para um informacao, como nos outros modulos de formas/figuras.
 * 
 * Em resumo, eh um modulo que coloco funcoes, para conseguir acessar ou modificar
 * uma informacao de um item qualquer, sem necessitar de um tipo de filtro, para saber
 * o tipo do item.
 */


/* Retorna o id (int) de uma informacao qualquer
 */
int GetID (void* item);

/* Retorna o identificador de tipo (int) de uma informacao qualquer
 */
int GetType (void* item);

/* Retorna a posicao x (double) da ancora de uma informacao qualquer
 */
double GetX (void* item);

/* Retona a posicao y (double) da ancora de uma informacao qualquer
 */
double GetY (void* item);

/* Retorna a vida atual (double) de uma informacao qualquer em porcentagem (0 <= vida <= 1)
 */
double GetLife (void* item);

/* Retorna a distancia (double) entre a ancora de uma informacao qualquer e o centro ficticio da arvore radial
 */
double GetDistanciaCentro (void* item);

/* Retorna o peso em gramas (double) de uma informacao qualquer
 */
double GetPeso (void* item);

/* Retorna o percentual (double) de dano causado a uma informacao qualquer
 */
double GetDano (void* item);

/* Retorna o percerntual (double) da area adubada de uma informacao qualquer
 */
double GetAdubagem (void* item);

/* Modifica a posicao x (double) de uma informacao qualquer, fazendo-a receber um double x
 */
void SetX (void* item, double x);

/* Modifica a posicao y (double) de uma informacao qualquer, fazendo-a receber um double y
 */
void SetY (void* item, double y);

/* Atualiza a vida/peso (double) atual de uma informacao item
 */
void SetLife (void* item);

/* Modifica a distancia (double) entre a ancora de uma informacao qualquer e o centro ficticio da arvore radial
 */
void SetDistanciaCentro (void* item, double DistanciaCentro);

/* Incrementa o dano (double) de uma informacao item, em dano
 */
void SetDano (void* item, double dano);

/* Incremente o valor adubado (double) de uma informacao item, em adubagem
 */
void SetAdubagem (void* item, double adubagem);

#endif