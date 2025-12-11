#include "estilo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*================================*/
/* Estrutura Interna do TAD Estilo */
/*================================*/
typedef struct estilo {
    char *fFamily; 
    char *fWeight;
    double fSize;
} EstruturaEstilo;



/**
 * @brief Duplica uma string (versão C99-compatível do strdup).
 */
static char* duplicar_string(const char* s) {
    if (s == NULL) {
        return NULL;
    }

    size_t len = strlen(s) + 1; 

    char* nova_string = (char*) malloc(len);
    if (nova_string == NULL) {
        return NULL;
    }

    strcpy(nova_string, s);

    return nova_string;
}


/*=======================*/
/* Constructor do Estilo */
/*=======================*/
Estilo estilo_cria(char* fFamily, char* fWeight, double fSize) {
    EstruturaEstilo *NovoEstilo = (EstruturaEstilo*) malloc(sizeof(EstruturaEstilo));
    if (NovoEstilo == NULL) {
        printf("Erro(0) em estilo_cria: falha na alocacao.\n");
        return NULL;
    }

    if (fFamily == NULL || fWeight == NULL) {
        NovoEstilo->fFamily = duplicar_string("sans-serif");
        NovoEstilo->fWeight = duplicar_string("normal");
    } else {
        NovoEstilo->fFamily = duplicar_string(fFamily);
        NovoEstilo->fWeight = duplicar_string(fWeight);
    }
    
    if (NovoEstilo->fFamily == NULL || NovoEstilo->fWeight == NULL) {
        free(NovoEstilo->fFamily);
        free(NovoEstilo->fWeight);
        free(NovoEstilo);
        printf("Erro(1) em estilo_cria: falha na alocacao de string.\n");
        return NULL;
    }

    NovoEstilo->fSize = fSize;

    return (Estilo) NovoEstilo;
}


/*======================*/
/* Destructor do Estilo */
/*======================*/
void estilo_destroi(Estilo e) {
    if (e == NULL) return;

    EstruturaEstilo *estilo = (EstruturaEstilo*) e;

    if (estilo->fFamily != NULL) {
        free(estilo->fFamily);
    }
    if (estilo->fWeight != NULL) {
        free(estilo->fWeight);
    }

    free(estilo);
}


/*======================*/
/*  Getters do Estilo   */
/*======================*/
char* estilo_getFamily(Estilo e) {
    if (e == NULL) return NULL;
    EstruturaEstilo *estilo = (EstruturaEstilo*) e;
    return estilo->fFamily;
}

char* estilo_getWeight(Estilo e) {
    if (e == NULL) return NULL;
    EstruturaEstilo *estilo = (EstruturaEstilo*) e;
    return estilo->fWeight;
}

double estilo_getSize(Estilo e) {
    if (e == NULL) return -1;
    EstruturaEstilo *estilo = (EstruturaEstilo*) e;
    return estilo->fSize;
}


/*======================*/
/*  Setters do Estilo   */
/*======================*/
void estilo_setFamily(Estilo e, char* family) {
    if (e == NULL || family == NULL) return;
    EstruturaEstilo *estilo = (EstruturaEstilo*) e;

    if (estilo->fFamily != NULL) {
        free(estilo->fFamily);
    }

    estilo->fFamily = duplicar_string(family);

    if (estilo->fFamily == NULL) {
        printf("Erro em estilo_setFamily: falha na alocacao de string.\n");
    }
}

void estilo_setWeight(Estilo e, char* weight) {
    if (e == NULL || weight == NULL) return;
    EstruturaEstilo *estilo = (EstruturaEstilo*) e;

    if (estilo->fWeight != NULL) {
        free(estilo->fWeight);
    }

    estilo->fWeight = duplicar_string(weight);
    
    if (estilo->fWeight == NULL) {
        printf("Erro em estilo_setWeight: falha na alocacao de string.\n");
    }
}

void estilo_setSize(Estilo e, double size) {
    if (e == NULL) return;
    EstruturaEstilo *estilo = (EstruturaEstilo*) e;
    estilo->fSize = size;
}


/*======================*/
/* Operações do Estilo  */
/*======================*/
Estilo estilo_clona(Estilo e) {
    if (e == NULL) return NULL;

    EstruturaEstilo *original = (EstruturaEstilo*) e;
    
    Estilo clone = estilo_cria(
        original->fFamily, 
        original->fWeight, 
        original->fSize
    );

    return clone;
}