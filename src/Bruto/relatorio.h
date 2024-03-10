#ifndef _RELATORIO_H
#define _RELATORIO_H

#include "funcoes.h"

/* Modulo implemento as funcoes que servem para escrever relatorios
 * sobre informacoes especificas (circulo, linha, retangulo e texto).
 * 
 * Em resumo, possue funcoes que servem para escrever as informacoes de
 * uma informacao, em um arquivo txt.
 * */

/* Escreve um relatorio sobre uma informacao qualquer, em um arquivo txt
 */
void RelatorioInfo (Item item, void* txt, void* aux);

/* Escreve um relatorio sobre as informacoes de um circulo, em um arquivo txt
 */
void RelatorioCirculo (Info item, FILE* txt);

/* Escreve um relatorio sobre as informacoes de uma linha, em um arquivo txt
 */
void RelatorioLinha (Info item, FILE* txt);

/* Escreve um relatorio sobre as informacoes de um retangulo, em um arquivo txt
 */
void RelatorioRetangulo (Info item, FILE* txt);

/* Escreve um relatorio sobre as informacoes de um texto, em um arquivo txt
 */
void RelatorioTexto (Info item, FILE* txt);

/* Escreve a contabilidade total de elementos colhidos, durante as sucessivas
 * chamadas do comando "HVT" do .qry. Os elementos colhidos sao armazenados
 * na lista ColheitaGeral. Tambem escreve o contabilidade total de elementos
 * que nao forma colhidos, os quais estao armazenados na arvore radial arvore.
 */
void ContabilidadeTotal (RadialTree arvore, Lista ColheitaGeral, FILE* txt);

#endif