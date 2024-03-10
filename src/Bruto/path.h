#ifndef _PATH_H
#define _PATH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

/* Neste modulo, sao implementadas as funcoes, as quais, auxiliam
 * na interpretacao dos parametros int argc, char** argv da main.
 * Funcoes para concatenar paths, e determinar o caminho de arquivos.
 * 
 * Em resumo, eh um modulo, feito para compilar e rodar todo o projeto,
 * com base em um script de comando. Sendo as funcoes que determinam se
 * os programas irao executar da forma correta
 */

/* Funcao a qual recebe como parametros char**, os quais irao receber os
 * argumentos do char** argv. O PathSaida, recebe o o argumento que representa
 * o diretorio de saida. O Path Entrada recebe o diretorio que representa o 
 * diretorio de entrada dos arquivos .geo e .qry. O NomeGeo recebe o nome
 * do arquivo .geo o qual sera utilizado. O NomeQry recebe o nome da pasta, onde
 * estarao os arquivos .qry que serao utilizados com o mesmo .geo. O Ns recebe 
 * a quantidade de setores que uma arvore radial (Banco de dados) ira ter. O Fd 
 * recebe o "fator degradacao" da arvore. Os parametros argc e argv sao utilizados
 * para fazer comparacoes e determinar o "recebimento" de cada variavel.
 * */
void PassaArgumentos (char** PathSaida, char** PathEntrada, char** NomeGeo, char** NomeQry, int* Ns, double* Fd, int argc, char** argv);

/* Funcao a qual recebe como parametro, os nomes dos arquivos
 * .geo e .qry, os quais sao representados pelas strings NomeGeo
 * e NomeQry respectivamente. Os nomes sao "juntados" e a funcao
 * retorna uma string nova, a qual sera utilizada para gerar os arquivos
 * de saida.
 * */
char* CriaNomeArq (char* NomeGeo, char* NomeQry);

/* Esta funcao, concatena duas strings em uma strings
 * auxiliar, e retorna esta.
 */
char* ConcatenaPath (char* Path, char* nome);

#endif