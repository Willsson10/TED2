#ifndef _LINHA_H
#define _LINHA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef void* Linha;

/* Modulo onde sao implementadas funcoes para conseguir acessar informacoes
 * de uma linah (a qual eh uma struct).
 *
 * Aqui tem funcoes para inicializar uma struct linha, com informacoes.
 * Funcoes para conseguir informacoes especificas de uma linha, e funcoes
 * de modificar as informacoes.
 * 
 * Em resumo, eh um modulo que serve para eu conseguir fazer operacoes com linhas
 */

/* Inicializa e retorna uma linha de ID id, ancoras em (x1, y1) e (x2, y2), e cor cor
 */
Linha InicializaLinha (int id, double x1, double y1, double x2, double y2, char* cor);

/* Retorna o x2 (double) de uma das ancoras da linha lin
 */
double GetLineX2 (Linha lin);

/* Retorna o y2 (double) de uma das ancoras da linha lin
 */
double GetLineY2 (Linha lin); 

/* Retorna a cor (char*) de uma linha lin
 */
char* GetLineCor (Linha lin);

/* Retorna o comprimento (double) de uma linha lin
 */
double GetLineLength (Linha lin);

/* Modifica a posicao x2 (double) de uma das ancoras da linha lin, fazendo-a receber um double x2
 */
void SetLineX2 (Linha lin, double x2);

/* Modifica a posicao y2 (double) de uma das ancoras da linha lin, fazendo-a receber um double y2
 */
void SetLineY2 (Linha lin, double y2);

/* Modifica a cor (char*) de uma linha lin, fazendo-a receber um char* cor
 */
void SetLineCor (Linha lin, char* cor);

#endif