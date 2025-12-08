// formas.h
#ifndef FORMAS_H
#define FORMAS_H

#include "estilo.h"
#include "anteparo.h"
#include "lista.h"
#include <stdio.h>

/*
 * TAD de Formas Geométricas.
 * 
 * Representa formas básicas (círculo, retângulo, linha, texto) usadas
 * no sistema. Cada forma possui um identificador único, coordenadas e cores.
 * 
 * Este arquivo contém funções para criar, manipular e desenhar formas,
 * além de convertê-las em anteparos (segmentos) para o algoritmo de visibilidade.
 */

typedef void* Forma;

/*==========================*/
/*  Constructors das formas */
/*==========================*/

/**
 * @brief Cria um novo círculo.
 * @param i Identificador único do círculo.
 * @param x Coordenada X do centro.
 * @param y Coordenada Y do centro.
 * @param r Raio do círculo.
 * @param corb Cor da borda (formato "#RRGGBB").
 * @param corp Cor do preenchimento (formato "#RRGGBB").
 * @return Forma Ponteiro para a forma criada, ou NULL em caso de erro.
 */
Forma circulo_cria(int i, double x, double y, double r, char *corb, char *corp);

/**
 * @brief Cria um novo retângulo.
 * @param i Identificador único do retângulo.
 * @param x Coordenada X da âncora (canto inferior esquerdo).
 * @param y Coordenada Y da âncora (canto inferior esquerdo).
 * @param w Largura do retângulo.
 * @param h Altura do retângulo.
 * @param corb Cor da borda.
 * @param corp Cor do preenchimento.
 * @return Forma Ponteiro para a forma criada, ou NULL em caso de erro.
 */
Forma retangulo_cria(int i, double x, double y, double w, double h, char *corb, char *corp);

/**
 * @brief Cria uma nova linha.
 * @param i Identificador único da linha.
 * @param x1 Coordenada X do ponto inicial.
 * @param y1 Coordenada Y do ponto inicial.
 * @param x2 Coordenada X do ponto final.
 * @param y2 Coordenada Y do ponto final.
 * @param cor Cor da linha.
 * @return Forma Ponteiro para a forma criada, ou NULL em caso de erro.
 */
Forma linha_cria(int i, double x1, double y1, double x2, double y2, char *cor);

/**
 * @brief Cria um novo texto.
 * @param i Identificador único do texto.
 * @param x Coordenada X da âncora.
 * @param y Coordenada Y da âncora.
 * @param corb Cor da borda.
 * @param corp Cor do preenchimento.
 * @param a Posição da âncora ('i': início, 'm': meio, 'f': fim).
 * @param txto String com o texto (pode incluir espaços).
 * @param e Estilo do texto (família, peso, tamanho da fonte).
 * @return Forma Ponteiro para a forma criada, ou NULL em caso de erro.
 */
Forma texto_cria(int i, double x, double y, char* corb, char *corp, char a, char *txto, Estilo e);

/*==========================*/
/*  Destructor das formas   */
/*==========================*/

/**
 * @brief Libera a memória alocada para uma forma.
 * @param f Forma a ser destruída.
 */
void forma_destruir(Forma f);

/*====================*/
/* Getters das formas */
/*====================*/

/**
 * @brief Retorna o identificador único da forma.
 * @param f Forma.
 * @return int ID da forma, ou -1 em caso de erro.
 */
int forma_getId(Forma f);

/**
 * @brief Retorna a cor de preenchimento da forma.
 * @param f Forma.
 * @return char* Cor de preenchimento, ou NULL em caso de erro.
 */
char* forma_getCorPreenchimento(Forma f);

/**
 * @brief Retorna a cor da borda da forma.
 * @param f Forma.
 * @return char* Cor da borda, ou NULL em caso de erro.
 */
char* forma_getCorBorda(Forma f);

/**
 * @brief Retorna a coordenada X da âncora da forma.
 * @param f Forma.
 * @return double Coordenada
 * X, ou -1 em caso de erro.
*/
double forma_getX(Forma f);
/**

@brief Retorna a coordenada Y da âncora da forma.
@param f Forma.
@return double Coordenada Y, ou -1 em caso de erro.
*/
double forma_getY(Forma f);

/*=================================*/
/*  Setters e operações das formas */
/*=================================*/

/** 
@brief Altera a cor da borda de uma forma.
@param f Forma a ser modificada.
@param novaCorBorda Nova cor da borda (formato "#RRGGBB").
*/
void forma_setCorBorda(Forma f, char *novaCorBorda);

/**
@brief Altera a cor de preenchimento de uma forma.
@param f Forma a ser modificada.
@param novaCorPreenchimento Nova cor de preenchimento.
*/
void forma_setCorPreenchimento(Forma f, char *novaCorPreenchimento);

/*=========================*/
/* Função de Desenho em SVG*/
/*=========================*/

/**
@brief Desenha uma forma em um arquivo SVG.
@param f Forma a ser desenhada.
@param svg_file Ponteiro para o arquivo SVG aberto.
*/
void forma_desenhaSvg(Forma f, FILE* svg_file);

//========================================/
/* Conversão de Forma para Anteparos     /
/========================================*
/
/**
@brief Converte uma forma em anteparos (segmentos).
Círculo: 1 segmento (horizontal ou vertical)
Retângulo: 4 segmentos (os 4 lados)
Linha: 1 segmento (ela mesma)
Texto: 1 segmento (baseado na âncora)
@param f Forma a ser convertida.
@param orientacao Orientação para círculos ('h': horizontal, 'v': vertical).
@return Lista Lista de anteparos criados, ou NULL em caso de erro.
*/
Lista forma_para_anteparos(Forma f, char orientacao);

#endif