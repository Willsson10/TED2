#ifndef _TEXTO_H
#define _TEXTO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef void* Texto;

/* Modulo onde sao implementadas funcoes para conseguir acessar informacoes
 * de um texto (o qual eh uma struct).
 *
 * Aqui tem funcoes para inicializar uma struct texto, com informacoes.
 * Funcoes para conseguir imformacoes especificas de um texto, e funcoes
 * de modificar as informacoes.
 * 
 * Em resumo, eh um modulo que serve para eu conseguir fazer operacoes com textos
 */

void SetPeso (void* item, double i);

/* Incializa e retorna um texto de ID id, ancora em (x, y), com cor da borda corb e cor de preenchimento corp, ancora centralizada em ancora, e conteudo conteudo
 */
Texto InicializaTexto (int id, double x, double y, char* corb, char* corp, char* ancora, char* conteudo);

/* Retorna a cor da borda (char*) do texto tex
 */
char* GetTextCorb (Texto tex);

/* Retorna a cor de preenchimento (char*) do texto tex
 */
char* GetTextCorp (Texto tex);

/* Retorna como a ancora (char*) do texto tex esta centralizada, (start, middle, end)
 */
char* GetTextAncora (Texto tex);

/* Retorna o conteudo (char*) escrito do texto tex
 */
char* GetTextContents (Texto tex);

/* Retorna a familia (char*) da fonte de um texto tex
 */
char* GetTextFamily (Texto tex);

/* Retorna o estilo (char*) de um texto tex
 */
char* GetTextWeight (Texto tex);

/* Retorna o tamanho (char*) da fonte de um texte tex
 */
char* GetTextSize (Texto tex);

/* Modifica a cor da borda (char*) do texto tex, fazendo-a receber um char* corb
 */
void SetTextCorb (Texto tex, char* corb);

/* Modifica a cor de preenchimento (char*) do texto tex, fazendo-a receber um char* corp
 */
void SetTextCorp (Texto tex, char* corp);

/* Modifica o conteudo (char*) escrito do texto tex, fazendo-o receber um char* conteudo
 */
void SetTextContents (Texto tex, char* conteudo);

/* Modifica o estilo do texto tex, tendo seu estilo de fonte como family, sua espessura como weight e o tamanho da sua fonte como size
 */
void SetTextStyle (Texto tex, char* family, char* weight, char* size);

#endif