#ifndef _CIRCULO_H
#define _CIRCULO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define pi 3.14159265358979323846

typedef void* Circulo;

/* Modulo onde sao implementadas funcoes para conseguir acessar informacoes
 * de um circulo (o qual eh uma struct).
 *
 * Aqui tem funcoes para inicializar uma struct circulo, com informacoes.
 * Funcoes para conseguir imformacoes especificas de um circulo, e funcoes
 * de modificar as informacoes.
 * 
 * Em resumo, eh um modulo que serve para fazer operacoes com circulos
 */

/* Inicializa e retorna um circulo de ID id, âncora (x, y), raio r, cor da borda corb e cor de preenchimento corp
 */
Circulo InicializaCirculo (int id, double x, double y, double r, char* corb, char* corp);

/* Retorna a raio (double) de um circulo cir
 */
double GetCircleRaio (Circulo cir);

/* Retorna a cor da borda (char*) de um circulo cir
 */
char* GetCircleCorb (Circulo cir);

/* Retorna a cor de preenchimento (char*) de um circulo cir
 */
char* GetCircleCorp (Circulo cir);

/* Retorna a area (double) de um circulo cir
 */
double GetCircleArea (Circulo cir);

/* Modifica a cor da borda (char*) do circulo cir, fazendo-a receber um char* corb
 */
void SetCircleCorb (Circulo cir, char* corb);

/* Modifica a cor de preenchimento (char*) do circulo cir, fazendo-a receber um char* corp
 */
void SetCircleCorp (Circulo cir, char* corp);

#endif