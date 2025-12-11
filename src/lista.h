#ifndef LISTA_H
#define LISTA_H

/*
* TAD Lista Genérica.
* Estrutura de dados dinâmica duplamente ou simplesmente encadeada (conforme implementação).
* Utilizada para armazenar coleções de formas, anteparos e eventos da varredura.
* Permite inserção no fim e remoção de qualquer posição.
*/

#include <stdbool.h>

/*
* Declaração opaca da Lista.
*/
typedef struct lista* Lista;

/*==========================*/
/* Construtor da Lista      */
/*==========================*/
/**
 * @brief Cria uma nova lista vazia.
 * @return Lista Um ponteiro para a lista criada, ou NULL se falhar.
 */
Lista lista_cria();

/*==========================*/
/* Operações de Inserção    */
/*==========================*/
/**
 * @brief Insere um elemento genérico no final da lista.
 * @param l A lista onde o elemento será inserido.
 * @param e O ponteiro para o elemento a ser armazenado.
 */
void lista_adiciona(Lista l, void* e);

/*==========================*/
/* Operações de Remoção     */
/*==========================*/
/**
 * @brief Busca e remove um elemento específico da lista.
 * @param l A lista de onde retirar.
 * @param e O ponteiro do elemento a ser removido (comparação por ponteiro).
 * @return void* O elemento removido, ou NULL se não encontrado/lista vazia.
 */
void* lista_retira(Lista l, void* e);

/*==========================*/
/* Consultas e Status       */
/*==========================*/
/**
 * @brief Retorna o número atual de elementos na lista.
 * @param l A lista consultada.
 * @return int O tamanho da lista.
 */
int lista_tamanho(Lista l);

/**
 * @brief Verifica se a lista não contém elementos.
 * @param l A lista consultada.
 * @return true Se estiver vazia.
 * @return false Se houver pelo menos um elemento.
 */
bool lista_vazia(Lista l);

/*==========================*/
/* Destrutor                */
/*==========================*/
/**
 * @brief Destrói a estrutura da lista.
 * Nota: Dependendo da implementação, pode ou não liberar o conteúdo (payload).
 * Geralmente libera apenas os nós da lista.
 * @param l A lista a ser destruída.
 */
void lista_destruir(Lista l);

/**
 * @brief Retorna um array com todos os elementos da lista.
 * ATENÇÃO: O array retornado deve ser liberado com free().
 * @param l Lista.
 * @param n Retorna o número de elementos.
 * @return void** Array de ponteiros, ou NULL em caso de erro.
 */
void** lista_para_array(Lista l, int* n);

#endif