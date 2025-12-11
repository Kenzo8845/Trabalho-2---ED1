#ifndef ANTEPARO_H
#define ANTEPARO_H

#include <stdio.h>

/*
* TAD Anteparo.
* Representa um segmento de reta que bloqueia a propagação da luz ou explosão.
* É a unidade fundamental utilizada no algoritmo de varredura angular (Scanline).
* Possui coordenadas de início e fim, além de propriedades visuais.
*/

typedef void* Anteparo;

/*==========================*/
/* Construtor do Anteparo   */
/*==========================*/
/**
 * @brief Cria um novo anteparo (segmento de reta).
 * @param id Identificador único do anteparo.
 * @param x1 Coordenada X do ponto inicial.
 * @param y1 Coordenada Y do ponto inicial.
 * @param x2 Coordenada X do ponto final.
 * @param y2 Coordenada Y do ponto final.
 * @param cor Cor do anteparo (para visualização no SVG).
 * @return Anteparo Ponteiro para a estrutura criada, ou NULL em caso de erro.
 */
Anteparo anteparo_cria(int id, double x1, double y1, double x2, double y2, char* cor);

/*==========================*/
/* Destrutor do Anteparo    */
/*==========================*/
/**
 * @brief Libera a memória alocada para o anteparo.
 * @param a O anteparo a ser destruído.
 */
void anteparo_destroi(Anteparo a);

/*==========================*/
/* Getters e Acessores      */
/*==========================*/

/**
 * @brief Retorna o identificador único do anteparo.
 * @param a O anteparo.
 * @return int O ID do anteparo.
 */
int anteparo_getId(Anteparo a);

/**
 * @brief Recupera as coordenadas dos extremos do segmento.
 * @param a O anteparo.
 * @param x1 Ponteiro para armazenar o X inicial.
 * @param y1 Ponteiro para armazenar o Y inicial.
 * @param x2 Ponteiro para armazenar o X final.
 * @param y2 Ponteiro para armazenar o Y final.
 */
void anteparo_getCoordenadas(Anteparo a, double* x1, double* y1, double* x2, double* y2);

/**
 * @brief Retorna a string de cor do anteparo.
 * @param a O anteparo.
 * @return char* A cor do anteparo.
 */
char* anteparo_getCor(Anteparo a);

/*==========================*/
/* Funções de Desenho       */
/*==========================*/

/**
 * @brief Desenha a representação visual do anteparo em um arquivo SVG.
 * @param a O anteparo a ser desenhado.
 * @param svg O ponteiro para o arquivo SVG aberto.
 */
void anteparo_desenha_svg(Anteparo a, FILE* svg);

#endif