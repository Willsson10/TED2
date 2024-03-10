#ifndef _ORDENACAO_H
#define _ORDENACAO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "radialtree.h"
#include "../Formas/tipos.h"
#include "../Bruto/funcoes.h"

#define pi 3.14159265358979323846

/*Modulo onde sao implementadas funcoes para ordenacao da arvore radial.
 *Funcoes que determinam se informacoes estao completamente internas a
 *um retangulo. Funcoes que retornam os setores de um ponto ou retangulo.
 *Aqui tambem estao as funcoes que servem para reorganizar a arvore radial.
 *
 *Em resumo, é um modulo que serve para auxiliar as funcoes do modulo
 *radialtree.h. Sendo aqui onde declaro funcoes do tipo FdentroDeRegiao,
 *FpontoInternoAInfo e FvisitaNo.
 */

/* Retorna a distancia (double) entre os pontos (x1, y1) e (x2, y2)
 */
double DistEntrePontos (double x1, double y1, double x2, double y2);

/* Retorna o setor circular (0 a n-1) que um certo ponto (a,b) está em relação ao ponto central (x,y)
 * Utiliza o teorema da desigualdade triangular para realizar as comparacoes
 */
int PontoNoSetor(int n, double x, double y, double a, double b);

/* Preenche o vetor vetor, com os setores em que um retangulo de diagonais (x1, y1) (x2, y2) esta em
 * relacao a um ponto central (a, b). O tamanho do vetor, eh igual ao numero de setores s
 */
void PreencherSetores(int s, double x1, double y1, double x2, double y2, double a, double b, int vetor[]);

/* Confere se um certo retangulo (x1, y1) (x2, y2) esta em um certo setor s. O qual ponto de referencia eh o ponto central (a, b)
 * com n setores
 */
bool ConfereSetorDoRetangulo (int s, int n, double x1, double y1, double x2, double y2, double a, double b);

/* Confere se um ponto qualuer (a, b) está dentro de um retangulo, o qual é delimitado pelos pontos (x1, y1) e (x2, y2)
 * Retorna true para caso o ponto esteja dentro, e falso caso nao esteja
 */
bool GetPontoDentroRetangulo (double a, double b, double x1, double y1, double x2, double y2);

/* Confere se uma informacao i esta completamente dentro de um retangulo, delimitado pelos pontos (x1, y1) e (x2, y2),
 * caso esteja, a funcao retorna true, caso contrario, retorna false
 */
bool GetInfoDentroRetangulo (Info i, double x1, double y1, double x2, double y2);

/* Confere se um ponto qualquer (x, y) esta dentro de uma informacao i, caso esteja, a funcao retorna true,
 * caso contrario, retorna false
 */
bool GetPontoDentroInfo (Info i, double x, double y);

/* Define o centro ficticio de um retangulo, o qual "cobre" toda a regiao de uma arvore radial t
 * preenche o vetor centro[] com as coordenadas (x ,y) do centro ficticio
 */
void CentroFicticio (RadialTree t, double centro[]);

/* Delimita um retangulo, o qual "cobre" toda uma arvore radial. As coordenadas (x1, y1) e (x2, y2)
 * sao armazenadas em um vetor, o qual a entrada eh um void* aux
 */
void DelimitaRetangulo (Info i, double x, double y, void* aux);

/* Atualiza a distancia entre uma informacao i e o centro ficticio do retangulo que "cobre" a arvore radial, a coordenada deste ponto
 * esta armazenada em um vetor, o qual a entrada eh um void* aux
 */
void AtualizaDistancia (Info i, double x, double y, void* aux);

/* Adiciona a informacao i, para uma lista, a qual tem como entrada void* aux
 */
void NoParaLista (Info i, double x, double y, void* aux);

/* Adiciona a informacao i, para um vetor, o qual tem como entra void* aux
 */
void AdicionarNoAoVetor(RadialTree t, void* aux);

/* Funcao de ordenacao para qsort, a qual tem como parametro a distancia entre dois pontos
 */
int OrdenaDistancia (const void* Ponto1, const void* Ponto2);

/* Reorganiza a arvore radial t, retornando uma nova arvore. A qual foi ordenada com base em vetor de tamanho
 * TamanhoVetor
 */
RadialTree ReorganizaArvore (RadialTree t, int TamanhoVetor, int setores, double fd);

#endif