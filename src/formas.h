#ifndef FORMAS_H
#define FORMAS_H

#include "estilo.h"
#include "anteparo.h"
#include "lista.h"
#include "poligono.h"
#include <stdio.h>

/*
* TAD de Formas Geométricas.
* Representa os objetos da cidade (Círculos, Retângulos, Linhas, Textos).
* Cada forma possui ID, posição, dimensões e cores.
* Além de serem desenhadas no SVG, elas podem ser "explodidas" em Anteparos
* para bloquear a visão no algoritmo de visibilidade.
*/

typedef void* Forma;

/*==========================*/
/* Construtores            */
/*==========================*/

/**
 * @brief Cria um Círculo.
 * @param i ID da forma.
 * @param x, y Centro do círculo.
 * @param r Raio.
 * @param corb Cor da borda.
 * @param corp Cor do preenchimento.
 * @return Forma Ponteiro para o círculo criado.
 */
Forma circulo_cria(int i, double x, double y, double r, char *corb, char *corp);

/**
 * @brief Cria um Retângulo.
 * @param i ID da forma.
 * @param x, y Canto inferior esquerdo (âncora).
 * @param w Largura.
 * @param h Altura.
 * @param corb Cor da borda.
 * @param corp Cor do preenchimento.
 * @return Forma Ponteiro para o retângulo criado.
 */
Forma retangulo_cria(int i, double x, double y, double w, double h, char *corb, char *corp);

/**
 * @brief Cria uma Linha.
 * @param i ID da forma.
 * @param x1, y1 Ponto inicial.
 * @param x2, y2 Ponto final.
 * @param cor Cor da linha.
 * @return Forma Ponteiro para a linha criada.
 */
Forma linha_cria(int i, double x1, double y1, double x2, double y2, char *cor);

/**
 * @brief Cria um Texto.
 * @param i ID da forma.
 * @param x, y Ponto âncora.
 * @param corb Cor da borda (stroke).
 * @param corp Cor do preenchimento (fill).
 * @param a Tipo de âncora ('i'nício, 'm'eio, 'f'im).
 * @param txto Conteúdo do texto.
 * @param estilo Estilo de fonte (fonte, peso, tamanho).
 * @return Forma Ponteiro para o texto criado.
 */
Forma texto_cria(int i, double x, double y, char *corb, char *corp, char a, char *txto, Estilo estilo);

/*==========================*/
/* Destrutor               */
/*==========================*/
/**
 * @brief Destrói a forma e libera seus recursos (strings, estruturas).
 * @param f A forma a ser destruída.
 */
void forma_destroi(Forma f);

/*==========================*/
/* Getters e Setters       */
/*==========================*/

/**
 * @brief Retorna o ID da forma.
 * @param f A forma.
 * @return int O ID.
 */
int forma_getId(Forma f);

/**
 * @brief Retorna a coordenada X da âncora da forma.
 */
double forma_getX(Forma f);

/**
 * @brief Retorna a coordenada Y da âncora da forma.
 */
double forma_getY(Forma f);

/**
 * @brief Atualiza a cor de borda.
 * @param f A forma.
 * @param cor Nova cor.
 */
void forma_setCorBorda(Forma f, char* cor);

/**
 * @brief Atualiza a cor de preenchimento.
 * @param f A forma.
 * @param cor Nova cor.
 */
void forma_setCorPreenchimento(Forma f, char* cor);

/*==========================*/
/* Operações Avançadas     */
/*==========================*/

/**
 * @brief Desenha a forma no arquivo SVG fornecido.
 * @param f A forma.
 * @param svg O arquivo aberto.
 */
void forma_desenhaSvg(Forma f, FILE* svg);

/**
 * @brief Cria um clone de uma forma, transladando-a.
 * @param original Forma a ser clonada.
 * @param dx Deslocamento em X.
 * @param dy Deslocamento em Y.
 * @return Forma Clone da forma, ou NULL em caso de erro.
 */
Forma forma_clonar(Forma original, double dx, double dy);

/**
 * @brief Converte a forma geométrica em um ou mais Anteparos (segmentos).
 * - Retângulos geram 4 anteparos.
 * - Linhas geram 1 anteparo.
 * - Textos geram o "Bounding Box" como anteparos.
 * - Círculos: Geralmente aproximados ou tratados como 1 anteparo (dependendo da regra do projeto).
 * * @param f A forma a ser convertida.
 * @param l A lista onde os novos anteparos serão inseridos.
 */
Lista forma_para_anteparos(Forma f, char orientacao);

/**
 * @brief Verifica se uma forma sobrepõe parcialmente com uma região de visibilidade
 * @param f Forma a testar
 * @param vis Polígono da região de visibilidade
 * @return 1 se sobrepõe, 0 caso contrário
 */
int forma_sobrepoe_visibilidade(Forma f, Poligono vis);

#endif