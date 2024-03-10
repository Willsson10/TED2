#ifndef _SVG_H
#define _SVG_H

#include "../Implementacao/ordenacao.h"

typedef void* ArqSvg;

/* Modulo onde implemento funcoes para escrever um codigo em svg,
 * o qual, representa alguma forma (circulo, linha, retangulo ou texto).
 * 
 * Em resumo, possue funcoes que servem para escrever o svg de informacoes 
 * em um arquivo svg.
 */

/* Abre um arquivo .svg de diretorio fn, para escrita. Retorna o arquivo
 */
ArqSvg AbreSvg (char* fn);

/* Escreve o final de um arquivo svg e o fecha
 */
void FechaSvg (FILE* svg);

/* Escreve o svg de uma informacao i, num arquivo svg, o qual tem como entrada um void* aux
 */
void EscreveArvoreSvg (Info i, double x, double y, void* aux);

/* Escreve o svg de um circulo, no file svg
 */
void CirculoSvg (Info i, FILE* svg);

/* Escreve o svg de uma linha, no file svg
 */
void LinhaSvg (Info i, FILE* svg);

/* Escreve o svg de um retangulo, no file svg
 */
void RetanguloSvg (Info i, FILE* svg);

/* Escreve o svg de um texto, no file svg
 */
void TextoSvg (Info i, FILE* svg);

#endif