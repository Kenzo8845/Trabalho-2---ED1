#ifndef ORDENACAO_H
#define ORDENACAO_H

/*
* Módulo de Ordenação.
* Oferece interfaces para algoritmos de ordenação genéricos (polimórficos).
* Permite ordenar arrays de qualquer tipo de dado, desde que fornecida
* uma função de comparação adequada.
* Fundamental para ordenar os eventos da varredura angular.
*/

/*
* Ponteiro para função de comparação.
* Deve retornar:
* < 0 se a < b
* 0 se a == b
* > 0 se a > b
*/
typedef int (*FuncaoComparacao)(const void* a, const void* b);

/*==========================*/
/* Algoritmos de Ordenação  */
/*==========================*/

/**
 * @brief Ordena um array usando o QuickSort (wrapper para qsort da stdlib).
 * @param array O array a ser ordenado.
 * @param n Número de elementos no array.
 * @param tamanho_elemento Tamanho em bytes de cada elemento (sizeof).
 * @param compara Função de comparação entre dois elementos.
 */
void ordena_qsort(void* array, int n, int tamanho_elemento, FuncaoComparacao compara);

/**
 * @brief Ordena um array usando o MergeSort (implementação robusta).
 * Algoritmo estável, ideal para listas encadeadas ou quando a estabilidade é necessária.
 * @param array O array a ser ordenado.
 * @param n Número de elementos.
 * @param tamanho_elemento Tamanho em bytes de cada elemento.
 * @param threshold Limite para trocar para Insertion Sort em subarrays pequenos (otimização).
 * @param compara Função de comparação.
 */
void ordena_mergesort(void* array, int n, int tamanho_elemento, int threshold, FuncaoComparacao compara);

/*==========================*/
/* Algoritmos Auxiliares    */
/*==========================*/

/**
 * @brief Ordena pequenos arrays usando Insertion Sort.
 * Eficiente para conjuntos de dados muito pequenos ou quase ordenados.
 * Utilizado internamente pelo MergeSort como otimização de base.
 * @param array O array a ser ordenado.
 * @param inicio Índice inicial.
 * @param fim Índice final.
 * @param tamanho_elemento Tamanho em bytes de cada elemento.
 * @param compara Função de comparação.
 */
void ordena_insertion_sort(void* array, int inicio, int fim, int tamanho_elemento, FuncaoComparacao compara);

#endif