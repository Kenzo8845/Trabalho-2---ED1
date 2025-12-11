#ifndef PROCESSAGEO_H
#define PROCESSAGEO_H

#include "lista.h"
#include "svg.h"

#include <stdio.h>
#include <stdlib.h>


/* Modulo que processa o arquivo geo.
* Gera a lista com as formas posicionadas, e tambem o svg inicial.
*/

/**
 * @brief Processa o arquivo geo e gera a lista de formas.
 * @param dir_entrada
 * @param path_geo 
 * @return Lista 
 */
Lista processaGeo(const char *path_geo);

#endif