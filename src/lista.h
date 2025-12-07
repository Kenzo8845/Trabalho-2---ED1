#ifndef LISTA_H
#define LISTA_H

/*
*TAD de Lista generica, com a logica de primeiro a entrar sera o primeiro a sair.
*Este arquivo contem as funções básicas para manipulação das Lista.
*/

#include <stdbool.h>

/*
* Declaração opaca da Lista.
*/
typedef struct lista* Lista;

/*
* Cria uma Lista vazia.
* Retorna: um ponteiro para a Lista criada.
*/
Lista lista_cria();

/*
* Insere um elemento no final da Lista.
* Parametros:
* - l: uma Lista ja existente 
* - e: um elemento que sera alocado no fim.
*/
void lista_adiciona(Lista l, void* e);

/*
* Retira um elemento do inicio da Lista.
* Parametros: uma Lista 'l' na qual se quer retirar o elemento.
* Retorna: um ponteiro para o elemento retirado, ou NULL, caso a Lista esteja vazia.
*/
void* lista_retiraDoInicio(Lista l);

/*
* Mostra o numero de elementos da Lista.
* Parametros: a Lista 'l' qual sera retornado o tamanho.
* Retorna: o tamanho da Lista.
*/
int lista_tamanho(Lista l);

/*
* Verifica se a Lista esta vazia.
* Parametros: a Lista a ser verificada.
* Retorna:  
* True: caso ela esteja vazia.
* False: caso haja qualquer elemento nela.
*/
bool lista_vazia(Lista l);

/*
* Libera toda a memória usada pela Lista.
* Parametros: a Lista 'l' a ser destruida.
* IMPORTANTE: não libera a memória dos elementos apontados.
*/
void lista_destruir(Lista l);



#endif