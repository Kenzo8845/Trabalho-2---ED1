#ifndef POLIGONO_H
#define POLIGONO_H

#include <stdio.h>

typedef void* Poligono;

/*========================*/
/* Constructor/Destructor */
/*========================*/

/**
 * @brief Cria um polígono vazio.
 * @return Poligono Polígono criado, ou NULL em caso de erro.
 */
Poligono poligono_cria();

/**
 * @brief Destroi um polígono e libera memória.
 * @param pol Polígono a ser destruído.
 */
void poligono_destroi(Poligono pol);

/*========================*/
/* Manipulação            */
/*========================*/

/**
 * @brief Adiciona um vértice ao polígono.
 * @param pol Polígono.
 * @param x Coordenada X do vértice.
 * @param y Coordenada Y do vértice.
 */
void poligono_adiciona_vertice(Poligono pol, double x, double y);

/**
 * @brief Retorna o número de vértices do polígono.
 * @param pol Polígono.
 * @return int Número de vértices.
 */
int poligono_num_vertices(Poligono pol);

/*========================*/
/* Consultas Geométricas  */
/*========================*/

/**
 * @brief Verifica se um ponto está dentro do polígono (Ray Casting).
 * @param pol Polígono.
 * @param px Coordenada X do ponto.
 * @param py Coordenada Y do ponto.
 * @return int 1 se está dentro, 0 caso contrário.
 */
int poligono_contem_ponto(Poligono pol, double px, double py);

/**
 * @brief Pega os vertices de um poligono.
 */
void poligono_get_vertices(Poligono pol, double** xs, double** ys, int* n);

/*========================*/
/* Desenho                */
/*========================*/

/**
 * @brief Desenha o polígono em um arquivo SVG.
 * @param pol Polígono.
 * @param svg Arquivo SVG aberto.
 * @param cor Cor de preenchimento do polígono.
 */
void poligono_desenha_svg(Poligono pol, FILE* svg, char* cor);

#endif