#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include "anteparo.h"
#include <stdbool.h>

/*
* Módulo de Geometria.
* Contém funções estáticas (stateless) para cálculos geométricos fundamentais.
* Responsável por calcular distâncias, orientações e, principalmente,
* as interseções entre o raio de varredura e os anteparos.
*/

/*=============================*/
/* Cálculos de Distância       */
/*=============================*/

/**
 * @brief Calcula a distância euclidiana entre dois pontos.
 * @param x1 X do ponto 1.
 * @param y1 Y do ponto 1.
 * @param x2 X do ponto 2.
 * @param y2 Y do ponto 2.
 * @return double A distância calculada.
 */
double geometria_distancia_pontos(double x1, double y1, double x2, double y2);

/**
 * @brief Calcula a menor distância de um ponto a um segmento de reta.
 * @param px X do ponto.
 * @param py Y do ponto.
 * @param x1 X do início do segmento.
 * @param y1 Y do início do segmento.
 * @param x2 X do fim do segmento.
 * @param y2 Y do fim do segmento.
 * @return double A distância mínima.
 */
double geometria_distancia_ponto_segmento(double px, double py, double x1, double y1, double x2, double y2);

/**
 * @brief Calcula a distância de um ponto a um anteparo existente.
 * Wrapper para a função de distância ponto-segmento usando o TAD Anteparo.
 * @param px X do ponto.
 * @param py Y do ponto.
 * @param a O anteparo alvo.
 * @return double A distância calculada.
 */
double geometria_distancia_ponto_anteparo(double px, double py, Anteparo a);

/*=============================*/
/* Orientação e Posição        */
/*=============================*/

/**
 * @brief Calcula a orientação de três pontos (produto vetorial 2D).
 * Útil para determinar se um ponto está à esquerda, direita ou é colinear.
 * @param x1, y1 Ponto A.
 * @param x2, y2 Ponto B.
 * @param x3, y3 Ponto C.
 * @return double Valor positivo (anti-horário/esquerda), negativo (horário/direita) ou 0 (colinear).
 */
double geometria_orientacao(double x1, double y1, double x2, double y2, double x3, double y3);

/**
 * @brief Verifica se um ponto (px, py) está estritamente à direita do segmento orientado (x1,y1 -> x2,y2).
 * @return int 1 se estiver à direita, 0 caso contrário.
 */
int geometria_ponto_a_direita(double x1, double y1, double x2, double y2, double px, double py);

/**
 * @brief Verifica se um ponto (px, py) está estritamente à esquerda do segmento orientado (x1,y1 -> x2,y2).
 * @return int 1 se estiver à esquerda, 0 caso contrário.
 */
int geometria_ponto_a_esquerda(double x1, double y1, double x2, double y2, double px, double py);

/*=============================*/
/* Interseções (Ray Casting)   */
/*=============================*/

/**
 * @brief Verifica se dois segmentos de reta se intersectam.
 * @param x1,y1 Inicio do seg 1.
 * @param x2,y2 Fim do seg 1.
 * @param x3,y3 Inicio do seg 2.
 * @param x4,y4 Fim do seg 2.
 * @return int 1 se houver interseção, 0 caso contrário.
 */
int geometria_segmentos_intersectam(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);

/**
 * @brief Calcula a interseção entre um raio e um segmento.
 * O raio é definido por uma origem (px, py) e um vetor direção (dx, dy).
 * @param px, py Origem do raio.
 * @param dx, dy Vetor direção do raio.
 * @param x1, y1 Inicio do segmento alvo.
 * @param x2, y2 Fim do segmento alvo.
 * @param ix [out] Armazena o X da interseção (se houver).
 * @param iy [out] Armazena o Y da interseção (se houver).
 * @return int 1 se o raio atinge o segmento, 0 caso contrário.
 */
int geometria_raio_intersecta_segmento(double px, double py, double dx, double dy, 
                                       double x1, double y1, double x2, double y2, 
                                       double* ix, double* iy);

/**
 * @brief Wrapper para calcular interseção de raio com um Anteparo.
 * Fundamental para o algoritmo de visibilidade (descobrir qual anteparo o raio atinge primeiro).
 * @param px, py Origem da bomba/luz.
 * @param dx, dy Vetor direção do raio.
 * @param a O anteparo a ser testado.
 * @param ix [out] Ponteiro para X da interseção.
 * @param iy [out] Ponteiro para Y da interseção.
 * @return int 1 se intersecta, 0 caso contrário.
 */
int geometria_raio_intersecta_anteparo(double px, double py, double dx, double dy, Anteparo a, double* ix, double* iy);

/**
 * @brief Calcula o angulo entre 2 pontos.
 * @param x_ref a coord x do primeiro ponto.
 * @param y_ref a coord y do primeiro ponto.
 * @param px a coord x do segundo ponto.
 * @param py a coord y do segundo ponto.
 * @return double, o angulo. 
 */
double geometria_calcula_angulo(double x_ref, double y_ref, double px, double py);

#endif