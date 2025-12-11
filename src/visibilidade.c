#include "poligono.h"
#include "geometria.h"
#include "anteparo.h"
#include "lista.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define EPSILON 1e-9
#define PI 3.14159265358979323846
#define DELTA_ANG 0.00001  // Offset angular pequeno

typedef struct {
    double angulo;
} RaioAngulo;

static int compara_angulos(const void* a, const void* b) {
    const RaioAngulo* ra = (const RaioAngulo*)a;
    const RaioAngulo* rb = (const RaioAngulo*)b;
    
    if (ra->angulo < rb->angulo) return -1;
    if (ra->angulo > rb->angulo) return 1;
    return 0;
}

static int encontra_interseccao_mais_proxima(double px, double py, double dir_x, double dir_y,
                                             Lista anteparos,
                                             double* ix, double* iy) {
    double t_min = 1e20;
    int encontrou = 0;
    
    int n;
    void** arr = lista_para_array(anteparos, &n);
    
    if (arr != NULL) {
        for (int i = 0; i < n; i++) {
            Anteparo ant = (Anteparo)arr[i];
            double isx, isy;
            
            if (geometria_raio_intersecta_anteparo(px, py, dir_x, dir_y, ant, &isx, &isy)) {
                double dist = (isx - px) * (isx - px) + (isy - py) * (isy - py);
                if (dist > EPSILON) {
                    double t = sqrt(dist);
                    if (t < t_min) {
                        t_min = t;
                        *ix = isx;
                        *iy = isy;
                        encontrou = 1;
                    }
                }
            }
        }
        free(arr);
    }
    
    // Testa intersecção com retângulo envolvente
    double xmin = -100, ymin = -100, xmax = 1100, ymax = 800;
    
    if (fabs(dir_x) > EPSILON) {
        double t = (xmax - px) / dir_x;
        if (t > EPSILON && t < t_min) {
            double y = py + t * dir_y;
            if (y >= ymin - EPSILON && y <= ymax + EPSILON) {
                t_min = t;
                *ix = xmax;
                *iy = y;
                encontrou = 1;
            }
        }
        
        t = (xmin - px) / dir_x;
        if (t > EPSILON && t < t_min) {
            double y = py + t * dir_y;
            if (y >= ymin - EPSILON && y <= ymax + EPSILON) {
                t_min = t;
                *ix = xmin;
                *iy = y;
                encontrou = 1;
            }
        }
    }
    
    if (fabs(dir_y) > EPSILON) {
        double t = (ymax - py) / dir_y;
        if (t > EPSILON && t < t_min) {
            double x = px + t * dir_x;
            if (x >= xmin - EPSILON && x <= xmax + EPSILON) {
                t_min = t;
                *ix = x;
                *iy = ymax;
                encontrou = 1;
            }
        }
        
        t = (ymin - py) / dir_y;
        if (t > EPSILON && t < t_min) {
            double x = px + t * dir_x;
            if (x >= xmin - EPSILON && x <= xmax + EPSILON) {
                t_min = t;
                *ix = x;
                *iy = ymin;
                encontrou = 1;
            }
        }
    }
    
    return encontrou;
}

Poligono calcula_regiao_visibilidade(double px, double py, Lista anteparos) {
    Poligono vis = poligono_cria();
    if (vis == NULL || anteparos == NULL) {
        return vis;
    }
    
    int n_ant;
    void** arr_ant = lista_para_array(anteparos, &n_ant);
    
    if (n_ant == 0) {
        if (arr_ant) free(arr_ant);
        poligono_adiciona_vertice(vis, -100, -100);
        poligono_adiciona_vertice(vis, 1100, -100);
        poligono_adiciona_vertice(vis, 1100, 800);
        poligono_adiciona_vertice(vis, -100, 800);
        return vis;
    }
    
    
    #define MAX_ANGULOS 3000
    RaioAngulo angulos[MAX_ANGULOS];
    int n_ang = 0;

    for (int i = 0; i < n_ant && n_ang + 6 < MAX_ANGULOS; i++) {
        Anteparo ant = (Anteparo)arr_ant[i];
        double x1, y1, x2, y2;
        anteparo_getCoordenadas(ant, &x1, &y1, &x2, &y2);
        
        // Ângulo do vértice inicial
        double ang1 = atan2(y1 - py, x1 - px);
        if (ang1 < 0) ang1 += 2*PI;
        
        // Ângulo do vértice final
        double ang2 = atan2(y2 - py, x2 - px);
        if (ang2 < 0) ang2 += 2*PI;
        
        // Offset - DELTA antes do inicial
        double ang1_before = ang1 - DELTA_ANG;
        if (ang1_before < 0) ang1_before += 2*PI;
        angulos[n_ang].angulo = ang1_before;
        n_ang++;
        
        // Exato inicial
        angulos[n_ang].angulo = ang1;
        n_ang++;
        
        // Offset + DELTA depois do inicial
        double ang1_after = ang1 + DELTA_ANG;
        if (ang1_after >= 2*PI) ang1_after -= 2*PI;
        angulos[n_ang].angulo = ang1_after;
        n_ang++;
        
        // Offset - DELTA antes do final
        double ang2_before = ang2 - DELTA_ANG;
        if (ang2_before < 0) ang2_before += 2*PI;
        angulos[n_ang].angulo = ang2_before;
        n_ang++;
        
        // Exato final
        angulos[n_ang].angulo = ang2;
        n_ang++;
        
        // Offset + DELTA depois do final
        double ang2_after = ang2 + DELTA_ANG;
        if (ang2_after >= 2*PI) ang2_after -= 2*PI;
        angulos[n_ang].angulo = ang2_after;
        n_ang++;
    }
    
    // Segundo: adiciona raios adicionais a cada 0.5 grau para cobertura total
    double paso = 0.5 * PI / 180.0;  // 0.5 graus em radianos
    for (double ang = 0; ang < 2*PI && n_ang < MAX_ANGULOS - 1; ang += paso) {
        angulos[n_ang].angulo = ang;
        n_ang++;
    }
    
    // Ordena por ângulo
    qsort(angulos, n_ang, sizeof(RaioAngulo), compara_angulos);
    
    // Remove duplicatas muito próximas
    RaioAngulo angulos_unicos[MAX_ANGULOS];
    int n_unicos = 0;
    
    for (int i = 0; i < n_ang; i++) {
        if (n_unicos == 0 || fabs(angulos[i].angulo - angulos_unicos[n_unicos-1].angulo) > EPSILON) {
            angulos_unicos[n_unicos].angulo = angulos[i].angulo;
            n_unicos++;
        }
    }
    
    // Para cada ângulo, traça raio e encontra interseção
    for (int i = 0; i < n_unicos; i++) {
        double ang = angulos_unicos[i].angulo;
        double dir_x = cos(ang);
        double dir_y = sin(ang);
        
        double ix, iy;
        if (encontra_interseccao_mais_proxima(px, py, dir_x, dir_y, anteparos, &ix, &iy)) {
            poligono_adiciona_vertice(vis, ix, iy);
        }
    }
    
    if (arr_ant) free(arr_ant);
    
    return vis;
}