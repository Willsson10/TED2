#ifndef _DOT_H
#define _DOT_H

#include "leitura.h"

typedef void* Arqdot;

/* Modulo onde sao implementadas funcoes para realizar a escrita
 * em arquivos .dot.
 *
 * Em resumo, sao funcoes que iniciam e terminam a escrita de
 * um arquivo .dot
 * */

/* Escreve o inicio de um arquivo .dot, de fn
 */
void InicioDot (char* fn);

/* Escreve o fim de um arquivo .dot, de caminho fn
 */
void FimDot (char* fn);

#endif