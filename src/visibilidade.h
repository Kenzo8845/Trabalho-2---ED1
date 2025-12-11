#ifndef VISIBILIDADE_H
#define VISIBILIDADE_H

#include "poligono.h"
#include "lista.h"

/**
 * @brief Calcula a região de visibilidade a partir de um ponto.
 * 
 * Implementa o algoritmo de varredura angular descrito no PDF
 * point-vis-region.pdf. Dado um ponto (bomba) e uma lista de
 * anteparos (segmentos bloqueantes), retorna um polígono que
 * representa a região iluminada/visível.
 * 
 * @param x Coordenada X da bomba.
 * @param y Coordenada Y da bomba.
 * @param anteparos Lista de anteparos (TAD Anteparo).
 * @return Poligono Região de visibilidade, ou NULL em caso de erro.
 */
Poligono calcula_regiao_visibilidade(double x, double y, Lista anteparos);

#endif