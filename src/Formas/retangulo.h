#ifndef _RETANGULO_H
#define _RETANGULO_H

#include "../Implementacao/radialtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef void* Retangulo;

/* Modulo onde sao implementadas funcoes para conseguir acessar informacoes
 * de um retangulo (o qual eh uma struct).
 *
 * Aqui tem funcoes para inicializar uma struct retangulo, com informacoes.
 * Funcoes para conseguir imformacoes especificas de um retangulo, e funcoes
 * de modificar as informacoes.
 * 
 * Em resumo, eh um modulo que serve para eu conseguir fazer operacoes com retangulos.
 */

/* Incializa e retorna um retangulo de ID id, ancora em (x, y), largura w, altura h, cor da borda corb e cor de preenchimento corp
 */
Retangulo InicializaRetangulo (int id, double x, double y, double w, double h, char* corb, char* corp);

/* Retorna a largura (double) do retangulo ret
 */
double GetRectangleWidth (Retangulo ret);

/* Retorna a altura (double) do retangulo ret
 */
double GetRectangleHeight (Retangulo ret);

/* Retorna a cor da borda (char*) do retangulo ret
 */
char* GetRectangleCorb (Retangulo ret);

/* Retorna a cor de preenchimento (char*) do retangulo ret
 */
char* GetRectangleCorp (Retangulo ret);

/* Retorna a area (double) do retangulo ret
 */
double GetRectangleArea (Retangulo ret);

/* Retorna a quantidade (int) de elementos colhidos por uma colheitadera ret
 */
int GetColheitaderaContador (Retangulo ret);

/* Retorna uma lista com as informacoes de todos os elementos colhidos
 */
Lista GetColheitadeColhidos (Retangulo ret);

/* Modifica a cor da borda (char*) do retangulo ret, fazendo-a receber um char* corb
 */
void SetRectangleCorb (Retangulo ret, char* corb);

/* Modifica a cor de preenchimento (char*) do retangulo ret, fazendo-a receber um char* corp
 */
void SetRectangleCorp (Retangulo ret, char* corp);

/* Modifica o contador de elementos colhidos por uma colheitadera ret
 */
void SetContador (Retangulo ret, int contador);

/* Insere um elemento item, na lista que armazena a informacao dos elementos colhidos pela colheitadera ret
 */
void SetColhidos (Retangulo ret, Info item, Lista lista);

/* Define um retangulo como sendo uma colheitadeira, caso x = true, e como um retangulo, caso x = false
 */
void SetColheitadera (Retangulo ret, bool x);

/* Retorna verdadeiro para caso um retangulo ret seja uma colheitadera, e falso caso nao seja
 */
bool IsColheitadera (Retangulo ret);

#endif