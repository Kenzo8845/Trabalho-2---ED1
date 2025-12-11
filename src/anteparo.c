#include "anteparo.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
    int id;           // ID único do anteparo
    double x1, y1;    // Ponto inicial
    double x2, y2;    // Ponto final
    char* cor;        // Cor do anteparo
} EstruturaAnteparo;

static char* duplicar_string(const char* s) {
    if (s == NULL) return NULL;
    
    size_t len = strlen(s) + 1;
    char* nova = (char*)malloc(len);
    if (nova == NULL) return NULL;
    
    strcpy(nova, s);
    return nova;
}


Anteparo anteparo_cria(int id, double x1, double y1, double x2, double y2, char* cor) {
    
    EstruturaAnteparo* novo = (EstruturaAnteparo*)malloc(sizeof(EstruturaAnteparo));
    if (novo == NULL) {
        printf("Erro ao alocar anteparo\n");
        return NULL;
    }
    
    novo->id = id;
    novo->x1 = x1;
    novo->y1 = y1;
    novo->x2 = x2;
    novo->y2 = y2;
    novo->cor = duplicar_string(cor);
    
    return (Anteparo)novo;
}


void anteparo_destroi(Anteparo a) {
    EstruturaAnteparo* ant = (EstruturaAnteparo*)a;
    if (ant == NULL) return;
    
    if (ant->cor != NULL) {
        free(ant->cor);
    }
    
    free(ant);
}


int anteparo_getId(Anteparo a) {
    EstruturaAnteparo* ant = (EstruturaAnteparo*)a;
    if (ant == NULL) return -1;
    return ant->id;
}

void anteparo_getCoordenadas(Anteparo a, double* x1, double* y1, 
                             double* x2, double* y2) {
    EstruturaAnteparo* ant = (EstruturaAnteparo*)a;
    if (ant == NULL) return;
    
    if (x1) *x1 = ant->x1;
    if (y1) *y1 = ant->y1;
    if (x2) *x2 = ant->x2;
    if (y2) *y2 = ant->y2;
}

char* anteparo_getCor(Anteparo a) {
    EstruturaAnteparo* ant = (EstruturaAnteparo*)a;
    if (ant == NULL) return NULL;
    return ant->cor;
}


void anteparo_desenha_svg(Anteparo a, FILE* svg) {
    EstruturaAnteparo* ant = (EstruturaAnteparo*)a;
    if (ant == NULL || svg == NULL) return;
    
    // Desenhar como linha grossa (para destacar que é anteparo)
    fprintf(svg, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" "
                 "stroke=\"%s\" stroke-width=\"3\" opacity=\"0.8\" />\n",
            ant->x1, ant->y1, ant->x2, ant->y2, ant->cor);
}