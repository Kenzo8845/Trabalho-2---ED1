#ifndef PROCESSAQRY_H
#define PROCESSAQRY_H

#include "lista.h"

#include <stdio.h>
#include <stdlib.h>


/* Modulo que processa o arquivo geo.
* Gera a lista com as formas posicionadas, e tambem o svg inicial.
*/

/**
 * @brief Processa o arquivo qry e devolve e escreve no svg final e o txt.
 * @param path_qry O caminho do arquivo Qry.
 * @param formas A lista de formas vinda do geo.
 * @param path_svg_saida O caminho onde deve ser gerado o txt.
 * @param path_txt_saida O caminho onde deve ser gerado o svg_final.
 */
void processaQry(const char *path_qry, Lista formas, const char *path_svg_saida, const char *path_txt_saida);

#endif