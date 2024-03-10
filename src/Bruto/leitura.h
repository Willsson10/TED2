#ifndef _LEITURA_H
#define _LEITURA_H

#include "geo_qry.h"
#include "relatorio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Modulo onde implemento funcoes que servem para ler arquivos
 * .geo e .qry, e interpreta-los. Realizando as funcoes ditadas por
 * esses.
 * 
 * Em resumo, possui funcoes que interpretam um arquivo .geo e um arquivo
 * .qry.
 * */

/* Retorna um char**, o qual armazena as palavras de uma linha de um arquivo de texto arq.
 * A cada chamada da funcao, a saida sera um char** com as palvras da linha seguinte
 */
char** ler_linha(FILE* arq);

/* Recebe o FILE geo, o qual aponta para um arquivo .geo. Este, tera comandos,
 * os quais irao determinar as informacoes que serao inseridas no banco de dados.
 * Neste caso, o banco de dados eh a arvore radial arvore.
 */
void LerGeo (FILE* geo, RadialTree arvore);

/* Recebe o FILE .qry, o qual aponta para um arquivo .qry. Este, tera comandos,
 * os quais irao derterminar "acoes" a serem feitas no banco de dados (arvore).
 * Os parametros svg e txt, sao serao as saidas do programa.
 */
void LerQry (RadialTree arvore, FILE* qry, FILE* svg, FILE* txt);

#endif