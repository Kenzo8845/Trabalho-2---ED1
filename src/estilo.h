#ifndef ESTILO_H
#define ESTILO_H

#include <stdio.h>

/*
* TAD de Estilo de texto.
* O estilo de texto, é um parâmentro necessário para criação e manipulação de textos.
* O estilo consiste em 3 campos, família, grossura e tamanho da fonte do texto.
* A dinâmica do estilo do texto consiste em:
* Existe um estilo padrão de texto, caso não haja um comando 'ts' antes da criação de um texto, o estilo que ele irá usar, será o estilo padrão.
* Caso haja um comando 'ts', todo texto criado a partir disso usará os parametros do comando 'ts'.
* Textos clonados usam o mesmo estilo de sua forma original.
*
* Este arquivo contem todas as funções responsáveis pela manipulação de estilos de texto.
*/

typedef void* Estilo;



/*=======================*/
/* Constructor do Estilo */
/*=======================*/
/**
 * @brief Cria um estilo de texto com os parametros especificados pelo ultimo comando 'ts',
 * caso não haja um comando 'ts', sempre criara o estilo padrão.
 * @param fFamily Familia do texto (sans, serif, cursive, etc);
 * @param fWeight 'Grossura' do texto (n: normal, b: bolder, b+: bolder, etc).
 * @param fSize Tamanho da fonte.
 * @return Estilo Retorna um estilo para o texto, ou NULL em caso de erro.
 */
Estilo estilo_cria(char* fFamily, char* fWeight, double fSize);



/*======================*/
/* Destructor do Estilo */
/*======================*/
/**
 * @brief Libera a memoria alocada para um estilo.
 * @param e O estilo a ser destruido.
 */
void estilo_destroi(Estilo e);



/*======================*/
/*  Getters do Estilo   */
/*======================*/
/**
 * @brief Pega a familia da fonte de um estilo.
 * @param e O estilo qual se quer saber a familia.
 * @return char* A familia do estilo, ou NULL em caso de erro.
 */
char* estilo_getFamily(Estilo e);

/**
 * @brief Pega o weight da fonte de um estilo.
 * @param e O estilo qual se quer saber o weight.
 * @return char*  O weight do estilo, ou NULL em caso de erro.
 */
char* estilo_getWeight(Estilo e);

/**
 * @brief Pega o tamanho(Size) de um estilo.
 * @param e O estillo qual se quer saber o tamanho.
 * @return double O tamanho do estilo, ou -1 em caso de erro.
 */
double estilo_getSize(Estilo e);



/*======================*/
/*  Setters do Estilo   */
/*======================*/
/**
 * @brief Altera a familia de um estilo.
 * @param e O estilo qual se quer alterar a familia.
 * @param family A familia nova do estilo.
 */
void estilo_setFamily(Estilo e, char* family);

/**
 * @brief Altera o weight de um estilo.
 * @param e O estilo qual se quer alterar o weight.
 * @param weight O weight novo do estilo.
 */
void estilo_setWeight(Estilo e, char* weight);

/**
 * @brief Altera o tamanho(Size) de um estilo.
 * @param e O estilo qual se quer alterar o tamanho.
 * @param size O tamanho novo do estilo.
 */
void estilo_setSize(Estilo e, double size);



/*======================*/
/* Operações do Estilo  */
/*======================*/
/**
 * @brief Cria um clone de um estilo especificado.
 * @param e O estilo qual se quer clonar.
 * @return Estilo  O clone do estilo, ou NULL em caso de erro.
 */
Estilo estilo_clona(Estilo e);

#endif