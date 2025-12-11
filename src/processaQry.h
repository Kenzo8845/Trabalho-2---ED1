#ifndef PROCESSAQRY_H
#define PROCESSAQRY_H

#include "lista.h"

#include <stdio.h>
#include <stdlib.h>


/* Modulo que processa o arquivo geo.
* Gera a lista com as formas posicionadas, e tambem o svg inicial.
*/
void processaQry(const char *path_qry, Lista formas, 
                 const char *path_svg_saida, const char *path_txt_saida);

#endif