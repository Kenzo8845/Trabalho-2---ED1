#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct No {
    void *elemento;
    struct No* prox;
} NoLista;

typedef struct lista {
    NoLista *inicio;
    NoLista* fim;
    int tamanho;
} EstruturaLista;

Lista lista_cria() {
    EstruturaLista * ListaNova = (EstruturaLista*) malloc(sizeof(EstruturaLista));
    if(ListaNova == NULL) {
        printf("erro de alocação ao criar lista nova");
        return NULL;
    }

    ListaNova->fim = NULL;
    ListaNova->inicio = NULL;
    ListaNova->tamanho = 0;

    return (Lista)ListaNova;
}

void lista_adicionaAoFim(Lista l, void* elemento) {
    EstruturaLista *lista = (EstruturaLista*) l;
    
    if (lista == NULL || elemento == NULL) {
        printf("erro ao adicionar ao fim, lista nao criada ou elemento invalido");
        return;
        // Erro de alocação
    }

    NoLista *NovoFim = (NoLista*) malloc(sizeof(NoLista));

    if (NovoFim == NULL) {
        printf("erro ao criar novo fim");
        return;
    }

    NovoFim->prox = NULL; 
    NovoFim->elemento = elemento;

    if(lista->tamanho == 0) {

        NovoFim->prox = NULL;
        NovoFim->elemento = elemento;

        lista->inicio = NovoFim;
        lista->fim = NovoFim;

        lista->tamanho++;
        return;
    }

    lista->fim->prox = NovoFim;
    lista->fim = NovoFim;

    lista->tamanho++;

    return;
}

void* lista_retiraDoInicio(Lista l) {
    EstruturaLista* lista = (EstruturaLista*) l;
    if (lista == NULL) {
        printf("nao foi possivel criar a lista em: lista_retiraDoInicio\n");
        return NULL;
    }

    if(lista->inicio == NULL) { 
        printf("nao foi possivel retirar da lista, ela esta vazia\n");
        return NULL;
    }

    NoLista* ItemRetirado = lista->inicio;
    void* ItemRetorno = lista->inicio->elemento;

    lista->inicio = lista->inicio->prox;
    
    if (lista->inicio == NULL) {
        lista->fim = NULL;
    }

    free(ItemRetirado);
    lista->tamanho--;

    return ItemRetorno;
}

int lista_tamanho(Lista l) {
    EstruturaLista* lista = (EstruturaLista*) l;
    if (lista == NULL) {
        printf("nao foi possivel criar a lista em: lista_tamanho");
        // Erro ao criar a lista.
        return -1;
    }

    return lista->tamanho;
}

bool lista_vazia(Lista l) {
    EstruturaLista* lista = (EstruturaLista*) l;
    if (lista == NULL) {
        printf("nao foi possivel criar a lista em: lista_vazia (lista e nula)\n");
        return true; 
    }
    return (lista->tamanho == 0); 
}

void lista_destruir(Lista l) {
    EstruturaLista* lista = (EstruturaLista*) l;
    if (lista == NULL) {
        printf("nao foi possivel criar a lista em: lista_destruir");
        // Erro ao criar a lista.
        return;
    }

    NoLista *atual = lista->inicio;
    while (atual != NULL) {
        NoLista *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    free(lista);
}