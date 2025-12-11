#ifndef SVG_H
#define SVG_H

#include <stdio.h>

/*
* Módulo de Geração de SVG.
*
* Este módulo fornece funções primitivas para criar um arquivo SVG
* e desenhar formas básicas (círculo, retângulo, linha, texto).
*/


/**
 * @brief Abre um arquivo SVG para escrita e escreve o cabeçalho.
 * @param path_svg O caminho completo do arquivo a ser criado (ex: "saida/geo.svg").
 * @return FILE* O ponteiro para o arquivo aberto, ou NULL em caso de erro.
 */
FILE* svg_inicia(const char* path_svg);

/**
 * @brief Escreve a tag de fechamento </svg> e fecha o arquivo.
 * @param svg_file O ponteiro do arquivo retornado por svg_inicia.
 */
void svg_finaliza(FILE* svg_file);


/*=========================*/
/* Funções Primitivas de Desenho */
/*=========================*/

/**
 * @brief Desenha um círculo no arquivo SVG.
 */
void svg_desenha_circulo(FILE* f, double x, double y, double r, char* corb, char* corp);

/**
 * @brief Desenha um retângulo no arquivo SVG.
 */
void svg_desenha_retangulo(FILE* f, double x, double y, double w, double h, char* corb, char* corp);

/**
 * @brief Desenha uma linha no arquivo SVG.
 */
void svg_desenha_linha(FILE* f, double x1, double y1, double x2, double y2, char* cor);

/**
 * @brief Desenha um texto no arquivo SVG.
 * @param anr A âncora do texto ('i', 'm', ou 'f').
 */
void svg_desenha_texto(FILE* f, double x, double y, char* corb, char* corp, char* txto, char* fFamily, char* fWeight, double fSize, char anr);

/**
 * @brief Desenha um asterisco (anotação) no arquivo SVG.
 */
void svg_desenha_asterisco(FILE* f, double x, double y);

/**
 * @brief Desenha uma linha pontilhada (trajetória de disparo) no SVG.
 * @param f O arquivo SVG.
 * @param x1 Coordenada X inicial (posição do disparador).
 * @param y1 Coordenada Y inicial (posição do disparador).
 * @param x2 Coordenada X final (posição da forma após disparo).
 * @param y2 Coordenada Y final (posição da forma após disparo).
 */
void svg_desenha_trajetoria(FILE* f, double x1, double y1, double x2, double y2);


#endif