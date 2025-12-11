#include "ordenacao.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void ordena_qsort(void* array, int n, int tamanho_elemento, FuncaoComparacao compara) {
    qsort(array, n, tamanho_elemento, compara);
}


void ordena_insertionSort(void* array, int inicio, int fim, int tamanho_elemento, FuncaoComparacao compara) {
    
    // Alocar espaço temporário para um elemento
    void* temp = malloc(tamanho_elemento);
    if (temp == NULL) {
        printf("Erro ao alocar memória no insertion_sort\n");
        return;
    }
    
    char* arr = (char*)array;  // Tratar como array de bytes
    
    for (int i = inicio + 1; i <= fim; i++) {
        // Copiar elemento atual para temp
        memcpy(temp, arr + i * tamanho_elemento, tamanho_elemento);
        
        int j = i - 1;
        
        // Mover elementos maiores para direita
        while (j >= inicio && compara(arr + j * tamanho_elemento, temp) > 0) {
            memcpy(arr + (j + 1) * tamanho_elemento, arr + j * tamanho_elemento, tamanho_elemento);
            j--;
        }
        
        // Inserir temp na posição correta
        memcpy(arr + (j + 1) * tamanho_elemento, temp, tamanho_elemento);
    }
    
    free(temp);
}

static void merge(void* array, int inicio, int meio, int fim, int tamanho_elemento, FuncaoComparacao compara) {
    
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    
    void* esq = malloc(n1 * tamanho_elemento);
    void* dir = malloc(n2 * tamanho_elemento);
    
    if (esq == NULL || dir == NULL) {
        printf("Erro ao alocar memória no merge\n");
        free(esq);
        free(dir);
        return;
    }
    
    char* arr = (char*)array;
    
    memcpy(esq, arr + inicio * tamanho_elemento, n1 * tamanho_elemento);
    memcpy(dir, arr + (meio + 1) * tamanho_elemento, n2 * tamanho_elemento);

    int i = 0, j = 0, k = inicio;
    
    while (i < n1 && j < n2) {
        char* elem_esq = (char*)esq + i * tamanho_elemento;
        char* elem_dir = (char*)dir + j * tamanho_elemento;
        
        if (compara(elem_esq, elem_dir) <= 0) {
            memcpy(arr + k * tamanho_elemento, elem_esq, tamanho_elemento);
            i++;
        } else {
            memcpy(arr + k * tamanho_elemento, elem_dir, tamanho_elemento);
            j++;
        }
        k++;
    }
    

    while (i < n1) {
        memcpy(arr + k * tamanho_elemento, (char*)esq + i * tamanho_elemento, tamanho_elemento);
        i++;
        k++;
    }
    
    while (j < n2) {
        memcpy(arr + k * tamanho_elemento, (char*)dir + j * tamanho_elemento, tamanho_elemento);
        j++;
        k++;
    }
    
    free(esq);
    free(dir);
}


static void mergesort_recursivo(void* array, int inicio, int fim, int tamanho_elemento, int threshold, FuncaoComparacao compara) {
    
    int tamanho = fim - inicio + 1;
    
    if (tamanho <= threshold) {
        ordena_insertionSort(array, inicio, fim, tamanho_elemento, compara);
        return;
    }
    
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;
        

        mergesort_recursivo(array, inicio, meio, tamanho_elemento, threshold, compara);
        
        mergesort_recursivo(array, meio + 1, fim, tamanho_elemento, threshold, compara);
        
        merge(array, inicio, meio, fim, tamanho_elemento, compara);
    }
}

void ordena_mergesort(void* array, int n, int tamanho_elemento, int threshold, FuncaoComparacao compara) {
    
    if (array == NULL || n <= 0 || compara == NULL) {
        return;
    }
    
    mergesort_recursivo(array, 0, n - 1, tamanho_elemento, threshold, compara);
}