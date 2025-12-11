#ifndef PROCESSAGEO_H
#define PROCESSAGEO_H

#include "lista.h"
#include "svg.h"

#include <stdio.h>
#include <stdlib.h>


/* Modulo que processa o arquivo geo.
* Gera a lista com as formas posicionadas, e tambem o svg inicial.
*/


Lista processaGeo(const char *dir_entrada, const char *path_geo);

#endif