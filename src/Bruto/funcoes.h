#ifndef _FUNCOES_H
#define _FUNCOES_H

#include "../Implementacao/ordenacao.h"
#include <time.h>

/* Modulo onde sao implementadas funcoes que servem para auxiliar
 * nas funcoes do arquivo .qry. Sao as principais funcoes do codigo,
 * onde todos os processos de alteracoes de informacoes, realizacao de
 * processos, e geracao de saidas sao feitos.
 * 
 * Em resumo, eh um modulo, onde sao "guardadas" as principais funcoes
 * do programa.
 */

/* Busca um node de ID id em uma arvore radial t. Retornando o informacao deste
 */
Info BuscaPorID (RadialTree t, int id);

/* Confere se o id de uma informacao i, eh igual a o id da informacao da lista void* aux.
 * Eh uma funcao do tipo FvisitaNo
 */
void ConfereID (Info i, double x, double y, void* aux);

/* Cria uma copia de uma informacao item, porem com uma variacao dx e dy em suas coordenadas.
 * Retorna a copia.
 */
Info CriaCopia (Info item, double dx, double dy);

/* Confere se uma informacao i, eh uma colheitadera, caso seja, insere na lista aux, caso contrario,
 * a funcao retorna NULL
 */
void ProcuraColheitadera (Info i, double x, double y, void* aux);

/* Remove o no, o qual tenha a informacao item da radial tree t
 */
void EliminaColheita (Info item, RadialTree t, void* aux);

/* Retorna uma lista, a qual tera as goticulas de raio r (double), que estao dentro de um retangulo,
 * o qual tem ancora em (x, y), largura w e altura h
 */
Lista DelimitaGoticulas (double x, double y, double w, double h, double r);

/* Confere se um circulo de centro (x, y) e raio r, esta inteiramente dentro de uma informacao i.
 * Caso esteja, retorna true, caso contrario, retorna false
 */
bool ConfereCirculoNaInformacao (Info i, double x, double y, double r);

/* Causa dano/cura nas informacoes item de uma arvore radial t, as quais foram atingidas por goticulas.
 * Utilizando o aux como parametro para dar dano ou curar
 */
void CausaDanoInfos (Item item, RadialTree t, void* aux);

/* Utilizada para fazer comparacoes entre duas listas
 */
void ComparaListas (Item item, Lista lista, void* aux);

/* Compara informacoes de listas diferentes
 */
void ComparaInformacoes (Item item, Item circulo, void* aux);

/* Escreve um "x" no svg svg, caso a infoemacao item esteja morta
 */
void MarcaXSvg (Item item, void* svg, void* aux);

/* Atualiza um vetor vetor, o qual contabiliza quantidade de hortalicas
 */
void ContaHortalicas (Item item, void* vetor, void* aux);

/* Preenche a lista lista, com copias de informacoes de uma lisa Infos. Gera essas copias com base na quantidade
 * de cada informacao, a qual esta armazenada no vetor vetor, e com base no fator fd. Os identificadores das copias
 * comecam em j
 */
void GeraCopiasSementes (Lista lista, Lista Infos, int vetor[], int* j, double fd);

/* Recebe uma lista com copias "cruas", e espalha elas de forma aleatoria dentro de um retangulo (x1, y1) (x2, y2).
 * Inserindo as copias na arvore radial t ao final do processo
 */
void EspalhaCopiasNoRetangulo (Lista copias, double x1, double y1, double x2, double y2, RadialTree t);

/* Realiza a contagem de peso de uma informacao, e incrementa o vetor aux, com este peso.
 * O vetor serve para saber a contabilidade parcial da colheita 
 */
void Contagem (Item item, void* p, void* aux);

/* Faz exatamente o mesmo processo da funcao Contagem,
 * porem, informacao i, pertence a um node de uma  
 * arvore radial.
 */
void Contagem2 (Info i, double x, double y, void* aux);

/* Movimenta uma colheitadera item, atoi(aux[2]) passos para (norte, sul, leste ou oeste).
 * Desenha em um FILE .svg, a area que a colheitadera percorreu, e por fim, retorna uma copia
 * desta, com variacao de posicao, relativa ao numero de passos e posicao final da colheitadera
 * */
Info AndaHVT (char** aux, Info item, FILE* svg);

/* Realiza a colheita da colheitadera item. As informacoes colhidas, sao armazenadas nas
 * lista colhidos (representa a colheita atual) e ColheitaGeral (representa todas as colheitas que
 * que ocorreram durante a leitura do arquivo .qry). O parametro char** aux, eh usado para saber
 * a direcao em que a colheitadera andou (norte, sul, leste ou oeste). O parametro copia, eh uma
 * copia da colheitadera, porem com uma variacao de posicao. Ela se encontra na posicao final da
 * colheitadera apos o fim da movimentacao.
 * */
void ColheHVT (RadialTree arvore, char** aux, Info item, Info copia, Lista colhidos, Lista ColheitaGeral);

#endif