#include "poligono.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EPSILON 1e-9

/*==========================*/
/* Estrutura Interna        */
/*==========================*/

typedef struct {
    double* xs;         // Array de coordenadas X dos vértices
    double* ys;         // Array de coordenadas Y dos vértices
    int num_vertices;   // Número atual de vértices
    int capacidade;     // Capacidade atual dos arrays
} EstruturaPoligono;

/*==========================*/
/* Funções Auxiliares       */
/*==========================*/

int expande_capacidade(EstruturaPoligono* pol) {
    if (pol == NULL) {
        return 0;
    }

    int nova_capacidade = pol->capacidade * 2;
    
    double* novos_xs = (double*)realloc(pol->xs, nova_capacidade * sizeof(double));
    double* novos_ys = (double*)realloc(pol->ys, nova_capacidade * sizeof(double));

    if (novos_xs == NULL || novos_ys == NULL) {
        printf("Erro ao expandir capacidade do poligono\n");
        return 0;
    }

    pol->xs = novos_xs;
    pol->ys = novos_ys;
    pol->capacidade = nova_capacidade;

    return 1;
}

/*==========================*/
/* Constructor/Destructor   */
/*==========================*/


Poligono poligono_cria() {
    EstruturaPoligono* NovoPoligono = (EstruturaPoligono*)malloc(sizeof(EstruturaPoligono));
    if (NovoPoligono == NULL) {
        printf("Erro ao alocar poligono em poligono_cria\n");
        return NULL;
    }

    NovoPoligono->capacidade = 100;
    NovoPoligono->xs = (double*)malloc(NovoPoligono->capacidade * sizeof(double));
    NovoPoligono->ys = (double*)malloc(NovoPoligono->capacidade * sizeof(double));

    if (NovoPoligono->xs == NULL || NovoPoligono->ys == NULL) {
        printf("Erro ao alocar arrays de vertices em poligono_cria\n");
        free(NovoPoligono->xs);
        free(NovoPoligono->ys);
        free(NovoPoligono);
        return NULL;
    }

    NovoPoligono->num_vertices = 0;

    return (Poligono)NovoPoligono;
}


void poligono_destroi(Poligono pol) {
    if (pol == NULL) {
        return;
    }

    EstruturaPoligono* poligono = (EstruturaPoligono*)pol;

    if (poligono->xs != NULL) {
        free(poligono->xs);
    }
    if (poligono->ys != NULL) {
        free(poligono->ys);
    }

    free(poligono);
}

/*==========================*/
/* Manipulação de Vértices  */
/*==========================*/


void poligono_adiciona_vertice(Poligono pol, double x, double y) {
    EstruturaPoligono* poligono = (EstruturaPoligono*)pol;
    if (poligono == NULL) {
        printf("Erro: poligono nulo em poligono_adiciona_vertice\n");
        return;
    }

    if (poligono->num_vertices >= poligono->capacidade) {
        if (!expande_capacidade(poligono)) {
            printf("Erro ao adicionar vertice: capacidade esgotada\n");
            return;
        }
    }

    poligono->xs[poligono->num_vertices] = x;
    poligono->ys[poligono->num_vertices] = y;
    poligono->num_vertices++;
}


int poligono_num_vertices(Poligono pol) {
    EstruturaPoligono* poligono = (EstruturaPoligono*)pol;
    if (poligono == NULL) {
        printf("Erro: poligono nulo em poligono_num_vertices\n");
        return -1;
    }
    
    return poligono->num_vertices;
}

/*==========================*/
/* Consultas Geométricas    */
/*==========================*/


#define EPSILON 1e-9

int poligono_contem_ponto(Poligono pol, double px, double py) {
    EstruturaPoligono* poligono = (EstruturaPoligono*)pol;
    if (poligono == NULL) {
        printf("Erro: poligono nulo em poligono_contem_ponto\n");
        return -1;
    }

    if (poligono->num_vertices < 3) {
        return 0;
    }
    
    int num_intersecoes = 0;
    
    for (int i = 0; i < poligono->num_vertices; i++) {
        int j = (i + 1) % poligono->num_vertices;
        
        double x1 = poligono->xs[i];
        double y1 = poligono->ys[i];
        double x2 = poligono->xs[j];
        double y2 = poligono->ys[j];
        
        // Checa se o ponto está exatamente na aresta
        // usando distância ponto-segmento
        double seg_dx = x2 - x1;
        double seg_dy = y2 - y1;
        double seg_len_sq = seg_dx*seg_dx + seg_dy*seg_dy;
        
        if (seg_len_sq > EPSILON) {
            double t = ((px - x1) * seg_dx + (py - y1) * seg_dy) / seg_len_sq;
            
            if (t >= 0 && t <= 1) {
                double closest_x = x1 + t * seg_dx;
                double closest_y = y1 + t * seg_dy;
                
                double dist_sq = (px - closest_x)*(px - closest_x) + 
                                (py - closest_y)*(py - closest_y);
                
                if (dist_sq < EPSILON) {
                    // Ponto está na aresta do polígono
                    return 1;
                }
            }
        }
        
        
        if ((y1 <= py && y2 > py) || (y2 <= py && y1 > py)) {
            // Calcula x da intersecção do raio com a aresta
            // O raio é uma linha horizontal: y = py, x > px
            
            double x_intersec = x1 + (py - y1) / (y2 - y1) * (x2 - x1);
            
            // Se a intersecção está à direita do ponto
            if (px < x_intersec) {
                num_intersecoes++;
            }
        }
    }
    
    // Se o número de intersecções é ímpar, o ponto está dentro
    return (num_intersecoes % 2 == 1);
}
void poligono_bounding_box(Poligono pol, double* xmin, double* ymin, 
                           double* xmax, double* ymax) {
    EstruturaPoligono* poligono = (EstruturaPoligono*)pol;
    if (poligono == NULL || poligono->num_vertices == 0) {
        printf("Erro em poligono_bounding_box\n");
        if (xmin) *xmin = 0;
        if (ymin) *ymin = 0;
        if (xmax) *xmax = 0;
        if (ymax) *ymax = 0;
        return;
    }

    double min_x = poligono->xs[0];
    double max_x = poligono->xs[0];
    double min_y = poligono->ys[0];
    double max_y = poligono->ys[0];

    for (int i = 1; i < poligono->num_vertices; i++) {
        double x = poligono->xs[i];
        double y = poligono->ys[i];

        if (x < min_x) min_x = x;
        if (x > max_x) max_x = x;
        if (y < min_y) min_y = y;
        if (y > max_y) max_y = y;
    }

    if (xmin) *xmin = min_x;
    if (ymin) *ymin = min_y;
    if (xmax) *xmax = max_x;
    if (ymax) *ymax = max_y;
}

/*==========================*/
/* Acesso aos Dados         */
/*==========================*/

void poligono_get_vertices(Poligono pol, double** xs, double** ys, int* n) {
    EstruturaPoligono* poligono = (EstruturaPoligono*)pol;
    if (poligono == NULL) {
        printf("Erro: poligono nulo em poligono_get_vertices\n");
        if (xs) *xs = NULL;
        if (ys) *ys = NULL;
        if (n) *n = 0;
        return;
    }

    if (xs) *xs = poligono->xs;
    if (ys) *ys = poligono->ys;
    if (n) *n = poligono->num_vertices;
}

/*==========================*/
/* Desenho SVG              */
/*==========================*/


void poligono_desenha_svg(Poligono pol, FILE* svg, char* cor) {
    EstruturaPoligono* poligono = (EstruturaPoligono*)pol;
    if (poligono == NULL || svg == NULL) {
        printf("Erro em poligono_desenha_svg: poligono ou arquivo nulo\n");
        return;
    }

    if (poligono->num_vertices < 3) {
        return;
    }

    fprintf(svg, "\t<polygon points=\"");
    
    for (int i = 0; i < poligono->num_vertices; i++) {
        fprintf(svg, "%.2f,%.2f ", poligono->xs[i], poligono->ys[i]);
    }
    
    fprintf(svg, "\" fill=\"%s\" fill-opacity=\"0.3\" stroke=\"%s\" stroke-width=\"2\" />\n", 
            cor, cor);
}