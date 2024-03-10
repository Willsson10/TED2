#ifndef _GEO_QRY_H
#define _GEO_QRY_H

#include "funcoes.h"
#include "relatorio.h"

/* Este modulo, eh onde sao implementadas as funcoes que realizam
 * as operacoes dadas por arquivos .geo e .qry. Onde aplico os 
 * comandos de .geo (c, r, l, ts, t), e os comandos do .qry
 * (cl, hvt, mv, ct, cr, ad, st, d?, c?).
 * 
 * Em resumo, sao as funcoes que realizam os principais procedimentos
 * do projeto.
 * */



/* Funcao que tem como objetivo, interpretar o arquivo .geo. Ela recebe um char** aux, o qual
 * armazena as strings de um linha do .geo, (ex: caso o comando fosse para inserir um circulo, 
 * o aux[0] seria "c"). Os vetores char family, weight e size, sao utilizados para alterar os
 * estilos dos textos, sendo atualizados quando aux[0] = "ts". Ao interpretar o comando da linha
 * do .geo, insere a informacao respectiva na arvore radial arvore.*/
void Interpreta_GEO (char** aux, char family[], char weight[], char size[], RadialTree arvore);

/* Funcao que realiza o comando "cr", dado em uma das linhas do .qry.
 * O paramatro char** aux, armazena as strings de um linha do .qry,
 * sendo utilizado para interpretar cada comando. 
 * 
 * Nesta funcao, eh "setado" como colheitadera, a informacao com id
 * igual a atoi(aux[1]) da arovre radial arvore.
 * */
void Funcao_cl (RadialTree arvore, char** aux);

/* Funcao que realiza o comando "mv", dado em uma das linhas do .qry.
 * O paramatro char** aux, armazena as strings de um linha do .qry,
 * sendo utilizado para interpretar cada comando. 
 * 
 * Nesta funcao, a informacao de id = atoi(aux[1]) da arvore radial arvore
 * eh movida strtod(aux[2], NULL) no eixo x e strtod(aux[3], NULL) no eixo y.
 * Os dados da informacao movida, sao relatadas no arquivo txt.
 * */
void Funcao_mv (RadialTree arvore, char** aux, FILE* txt);

/* Funcao que realiza o comando "hvt", dado em uma das linhas do .qry.
 * O paramatro char** aux, armazena as strings de um linha do .qry,
 * sendo utilizado para interpretar cada comando.  
 * 
 * Nesta funcao, a colheitadera de id = atoi(aux[1]) anda um cera quantidade de
 * passos (1 <= passos) para um certo sentido (norte, sul, leste ou oeste). Na 
 * area em que percorreu, "colhe" informacoes da arvore radial arvore. Informacoes 
 * colhidas sao marcadas como removidas e sao inseridas na lista ColheitaGeral (representa
 * a contabilidade total de todas as colheitas que ocorreram durante a leitura do arquivo .qry).
 * 
 * Eh reportado no FILE .txt, os dados da colheitadera e das informacoes colhidas por ela.
 * No .svg, eh desenhado uma area retangular vermelha, a qual representa a regiao colhida.
 * */
void Funcao_hvt (RadialTree arvore, char** aux, FILE* txt, FILE* svg, Lista ColheitaGeral);

/* Funcao que realiza os comandos "ct", "cr" e "ad", dado em uma das linhas do .qry.
 * O paramatro char** aux, armazena as strings de um linha do .qry,
 * sendo utilizado para interpretar cada comando.  
 * 
 * Nesta funcao, circunferencia de raio aux[5], sao distribuidas na regiao retangular
 * (aux[1], aux[2], aux[3], aux[4]). "Danificando" informacoes da arvore radial arvore
 * que forem "atingidas" por estas. Caso as informacoes sofram muitos "danos", sao 
 * marcadas como removidas da arvore radial.
 * 
 * Eh reportado no FILE txt, os dados das informacoes "atingidas". No FILE svg
 * eh desenhado um retangulo vermelho de bordas pontilhadas, representando a area retangular
 * e um circulo (vermelho, amarelo ou verde) em sua ancora.
 * */
void Funcoes_ct_cr_ad (RadialTree arvore, char** aux, FILE* txt, FILE* svg);

/* Funcao que realiza o comando "st", dado em uma das linhas do .qry.
 * O paramatro char** aux, armazena as strings de um linha do .qry,
 * sendo utilizado para interpretar cada comando. 
 * 
 * Nesta funcao, todas as informacoes da arvore radial arvore, que
 * estiverem totalmente internas a uma regia retangular (strtod(aux[1], NULL), 
 * strtod(aux[2], NULL), strtod(aux[3], NULL), strtod(aux[4], NULL)) terao suas
 * "sementes" espalhadas em outra regiao retangular de mesma dimensao, porem com
 * uma veriacao de posicao (strtod(aux[6], NULL)m strtod(aux[7], NULL)).
 * 
 * Nesta outra regiao retangular serao geradas copias das informacoes, com base
 * em um fator strtod(aux[5], NULL). Essas copias terao ids, a partir de 
 * atoi(aux[8]). As copias sao inseridas na arvore radial arvore. 
 * 
 * Eh reportado no FILE .txt, os atributos das informacoes semeadas e dos 
 * clones. No .svg, eh desenhado dois retangulos. Um representa a areas onde
 * foram "pegas" as sementes, e o outro a area semeada.
 * */
void Funcao_st (RadialTree arvore, char** aux, FILE* txt, FILE* svg);

/* Funcao que realiza o comando "d?", dado em uma das linhas do .qry.
 * O paramatro char** aux, armazena as strings de um linha do .qry,
 * sendo utilizado para interpretar cada comando. 
 * 
 * Nesta funcao, eh reportado em um FILE .txt, os dados de uma
 * informacao de id = atoi(aux[1]) da arvore radial arvore.
 * */
void Funcao_d (RadialTree arvore, char** aux, FILE* txt);

/* Funcao que realiza o comando "c?", dado em uma das linhas do .qry.
 * O paramatro char** aux, armazena as strings de um linha do .qry,
 * sendo utilizado para interpretar cada comando.  
 * 
 * Nesta funcao, eh reportado os atributos de todas as informacoes
 * consideras colheitaders da arvore radial arvore, em um FILE .txt.
 * */
void Funcao_c (RadialTree arvore, char** aux, FILE* txt);

#endif