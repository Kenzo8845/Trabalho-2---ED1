#include "geometria.h"
#include <math.h>
#include <stdio.h>

#define EPSILON 1e-9
#define PI 3.14159265358979323846


double geometria_distancia_pontos(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

double geometria_distancia_ponto_segmento(double px, double py,double x1, double y1, double x2, double y2) {
    // Vetor do segmento
    double ab_x = x2 - x1;
    double ab_y = y2 - y1;
    
    // Vetor do ponto inicial até o ponto
    double ap_x = px - x1;
    double ap_y = py - y1;
    
    // Comprimento ao quadrado do segmento
    double ab_len_sq = ab_x * ab_x + ab_y * ab_y;
    
    // Segmento de comprimento zero (é um ponto)
    if (ab_len_sq < EPSILON) {
        return sqrt(ap_x * ap_x + ap_y * ap_y);
    }
    
    // Projeção do ponto no segmento (parâmetro t)
    double t = (ap_x * ab_x + ap_y * ab_y) / ab_len_sq;
    
    // Clampar t entre [0, 1]
    if (t < 0.0) t = 0.0;
    if (t > 1.0) t = 1.0;
    
    // Ponto mais próximo no segmento
    double nearest_x = x1 + t * ab_x;
    double nearest_y = y1 + t * ab_y;
    
    // Distância do ponto ao ponto mais próximo
    double dx = px - nearest_x;
    double dy = py - nearest_y;
    
    return sqrt(dx * dx + dy * dy);
}

double geometria_distancia_ponto_anteparo(double px, double py, Anteparo a) {
    double x1, y1, x2, y2;
    anteparo_getCoordenadas(a, &x1, &y1, &x2, &y2);
    return geometria_distancia_ponto_segmento(px, py, x1, y1, x2, y2);
}

double geometria_orientacao(double x1, double y1, double x2, double y2, double x3, double y3) {
    // Produto vetorial: (p2 - p1) × (p3 - p1)
    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
}

int geometria_ponto_a_direita(double x1, double y1, double x2, double y2, double px, double py) {
    double orient = geometria_orientacao(x1, y1, x2, y2, px, py);
    return (orient < -EPSILON) ? 1 : 0;
}

int geometria_ponto_a_esquerda(double x1, double y1, double x2, double y2, double px, double py) {
    double orient = geometria_orientacao(x1, y1, x2, y2, px, py);
    return (orient > EPSILON) ? 1 : 0;
}


int geometria_segmentos_intersectam(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    
    double o1 = geometria_orientacao(x1, y1, x2, y2, x3, y3);
    double o2 = geometria_orientacao(x1, y1, x2, y2, x4, y4);
    double o3 = geometria_orientacao(x3, y3, x4, y4, x1, y1);
    double o4 = geometria_orientacao(x3, y3, x4, y4, x2, y2);
    
    // Caso geral: orientações opostas
    if (((o1 > EPSILON && o2 < -EPSILON) || (o1 < -EPSILON && o2 > EPSILON)) &&
        ((o3 > EPSILON && o4 < -EPSILON) || (o3 < -EPSILON && o4 > EPSILON))) {
        return 1;
    }
    
    // Casos especiais: colineares
    // (simplificado - pode adicionar verificação de sobreposição se necessário)
    
    return 0;
}

int geometria_raio_intersecta_segmento(double px, double py, double dx, double dy, double x1, double y1, double x2, double y2, double* ix, double* iy) {
    
    // Segmento: P1 + s*(P2-P1), onde 0 <= s <= 1
    // Raio: P + t*D, onde t >= 0
    
    double sx = x2 - x1;  // Vetor do segmento
    double sy = y2 - y1;

    
    double denom = dx * sy - dy * sx;
    
    // Raio paralelo ao segmento
    if (fabs(denom) < EPSILON) {
        return 0;
    }
    
    double t = ((x1 - px) * sy - (y1 - py) * sx) / denom;
    double s = ((x1 - px) * dy - (y1 - py) * dx) / denom;
    
    // Verificar se há interseção válida
    if (t >= -EPSILON && s >= -EPSILON && s <= 1.0 + EPSILON) {
        // Calcular ponto de interseção
        if (ix) *ix = px + t * dx;
        if (iy) *iy = py + t * dy;
        return 1;
    }
    
    return 0;
}

int geometria_raio_intersecta_anteparo(double px, double py, double dx, double dy, Anteparo a, double* ix, double* iy) {
    double x1, y1, x2, y2;
    anteparo_getCoordenadas(a, &x1, &y1, &x2, &y2);
    return geometria_raio_intersecta_segmento(px, py, dx, dy, x1, y1, x2, y2, ix, iy);
}

double geometria_calcula_angulo(double x_ref, double y_ref, double px, double py) {
    double dx = px - x_ref;
    double dy = py - y_ref;
    
    double angulo = atan2(dy, dx);
    
    // Normalizar para [0, 2*PI)
    if (angulo < 0) {
        angulo += 2.0 * PI;
    }
    
    return angulo;
}