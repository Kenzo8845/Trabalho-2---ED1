#include "formas.h"
#include "estilo.h"
#include "svg.h"
#include "anteparo.h"
#include "lista.h"
#include "geometria.h"
#include "poligono.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*======================*/
/*  Structs das formas  */ 
/*======================*/

typedef enum {
    TIPO_CIRCULO,
    TIPO_RETANGULO,
    TIPO_LINHA,
    TIPO_TEXTO
} TipoForma;

typedef struct {
    double x, y, r;
    char *corb, *corp;
} EstruturaCirculo;

typedef struct {
    double x, y, w, h;
    char *corb, *corp;
} EstruturaRetangulo;

typedef struct {
    double x1, y1, x2, y2;
    char *cor;
} EstruturaLinha;

typedef struct {
    double x, y;
    char *corb, *corp;
    char a;
    char *txto;
    Estilo estilo;
} EstruturaTexto;

typedef struct {
    TipoForma tipo;
    int id;
    union {
        EstruturaCirculo circulo;
        EstruturaRetangulo retangulo;
        EstruturaLinha linha;
        EstruturaTexto texto;
    } dados;
} EstruturaForma;

/*======================*/
/* Funções Auxiliares   */
/*======================*/

/**
 * @brief Duplica uma string (versão C99-compatível do strdup).
 * @param s String a ser duplicada.
 * @return char* Nova string alocada, ou NULL em caso de erro.
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

/*==========================*/
/*  Constructors das formas */
/*==========================*/


Forma circulo_cria(int i, double x, double y, double r, char *corb, char *corp) {
    EstruturaForma *NovoCirculo = (EstruturaForma*) malloc(sizeof(EstruturaForma));
    if (NovoCirculo == NULL) {
        printf("Erro ao alocar circulo em circulo_cria\n");
        return NULL;
    }

    NovoCirculo->tipo = TIPO_CIRCULO;
    NovoCirculo->id = i;
    NovoCirculo->dados.circulo.r = r;
    NovoCirculo->dados.circulo.x = x;
    NovoCirculo->dados.circulo.y = y;
    NovoCirculo->dados.circulo.corb = duplicar_string(corb);
    NovoCirculo->dados.circulo.corp = duplicar_string(corp);
    
    return (Forma)NovoCirculo;
}

 
Forma retangulo_cria(int i, double x, double y, double w, double h, char *corb, char *corp) {
    EstruturaForma *NovoRetangulo = (EstruturaForma*) malloc(sizeof(EstruturaForma));
    if (NovoRetangulo == NULL) {
        printf("Erro ao alocar retangulo em retangulo_cria\n");
        return NULL;
    }

    NovoRetangulo->tipo = TIPO_RETANGULO;
    NovoRetangulo->id = i;
    NovoRetangulo->dados.retangulo.x = x;
    NovoRetangulo->dados.retangulo.y = y;
    NovoRetangulo->dados.retangulo.w = w;
    NovoRetangulo->dados.retangulo.h = h;
    NovoRetangulo->dados.retangulo.corb = duplicar_string(corb);
    NovoRetangulo->dados.retangulo.corp = duplicar_string(corp);

    return (Forma)NovoRetangulo;
}


Forma linha_cria(int i, double x1, double y1, double x2, double y2, char *cor) {
    EstruturaForma *NovaLinha = (EstruturaForma*) malloc(sizeof(EstruturaForma));
    if (NovaLinha == NULL) {
        printf("Erro ao alocar linha em linha_cria\n");
        return NULL;
    }

    NovaLinha->tipo = TIPO_LINHA;
    NovaLinha->id = i;
    NovaLinha->dados.linha.x1 = x1;
    NovaLinha->dados.linha.x2 = x2;
    NovaLinha->dados.linha.y1 = y1;
    NovaLinha->dados.linha.y2 = y2;
    NovaLinha->dados.linha.cor = duplicar_string(cor);

    return (Forma)NovaLinha;
}


Forma texto_cria(int i, double x, double y, char* corb, char *corp, char a, char *txto, Estilo e) {
    EstruturaForma *NovoTexto = (EstruturaForma*) malloc(sizeof(EstruturaForma));
    if (NovoTexto == NULL) {
        printf("Erro ao alocar texto em texto_cria\n");
        return NULL;
    }

    NovoTexto->tipo = TIPO_TEXTO;
    NovoTexto->id = i;
    NovoTexto->dados.texto.x = x;
    NovoTexto->dados.texto.y = y;
    NovoTexto->dados.texto.corb = duplicar_string(corb);
    NovoTexto->dados.texto.corp = duplicar_string(corp);
    NovoTexto->dados.texto.a = a;
    NovoTexto->dados.texto.txto = duplicar_string(txto);
    NovoTexto->dados.texto.estilo = e;

    return (Forma)NovoTexto;
}

/*==========================*/
/*  Destructor das formas   */
/*==========================*/


void forma_destroi(Forma f) {
    EstruturaForma *forma = (EstruturaForma *)f;
    if (f == NULL) { 
        return;
    }

    switch (forma->tipo) {
        case TIPO_CIRCULO:
            free(forma->dados.circulo.corb);
            free(forma->dados.circulo.corp);
            break;

        case TIPO_RETANGULO:
            free(forma->dados.retangulo.corb);
            free(forma->dados.retangulo.corp);
            break;
            
        case TIPO_LINHA:
            free(forma->dados.linha.cor); 
            break;
            
        case TIPO_TEXTO:
            free(forma->dados.texto.corb);
            free(forma->dados.texto.corp);
            free(forma->dados.texto.txto); 
            estilo_destroi(forma->dados.texto.estilo);
            break;
    }

    free(forma); 
}

/*====================*/
/* Getters das formas */
/*====================*/


int forma_getId(Forma f) {
    EstruturaForma *forma = (EstruturaForma *)f;
    if (f == NULL) { 
        return -1;
    }
    return forma->id;
}


char* forma_getCorPreenchimento(Forma f) {
    EstruturaForma* forma = (EstruturaForma*) f;
    if (f == NULL) {
        printf("Erro em forma_getCorPreenchimento\n");
        return NULL;
    }

    switch (forma->tipo) {
        case TIPO_CIRCULO:
            return forma->dados.circulo.corp;
       
        case TIPO_RETANGULO:
            return forma->dados.retangulo.corp;

        case TIPO_LINHA:
            // Linha não tem preenchimento, retorna a cor da linha
            return forma->dados.linha.cor;

        case TIPO_TEXTO:
            return forma->dados.texto.corp;
    }

    return NULL;
}


char* forma_getCorBorda(Forma f) {
    EstruturaForma* forma = (EstruturaForma*) f;
    if (f == NULL) {
        printf("Erro em forma_getCorBorda\n");
        return NULL;
    }

    switch (forma->tipo) {
        case TIPO_CIRCULO:
            return forma->dados.circulo.corb;
       
        case TIPO_RETANGULO:
            return forma->dados.retangulo.corb;

        case TIPO_LINHA:
            return forma->dados.linha.cor;

        case TIPO_TEXTO:
            return forma->dados.texto.corb;
    }

    return NULL;
}


double forma_getX(Forma f) {
    EstruturaForma* forma = (EstruturaForma*) f;
    if (f == NULL) {
        printf("Erro em forma_getX\n");
        return -1;
    }

    switch (forma->tipo) {
        case TIPO_CIRCULO:
            return forma->dados.circulo.x;
       
        case TIPO_RETANGULO:
            return forma->dados.retangulo.x;

        case TIPO_LINHA:
            // Retorna o menor X
            return (forma->dados.linha.x1 < forma->dados.linha.x2) ? 
                    forma->dados.linha.x1 : forma->dados.linha.x2;

        case TIPO_TEXTO:
            return forma->dados.texto.x;
    }

    return -1;
}


double forma_getY(Forma f) {
    EstruturaForma* forma = (EstruturaForma*) f;
    if (f == NULL) {
        printf("Erro em forma_getY\n");
        return -1;
    }

    switch (forma->tipo) {
        case TIPO_CIRCULO:
            return forma->dados.circulo.y;
       
        case TIPO_RETANGULO:
            return forma->dados.retangulo.y;

        case TIPO_LINHA:
            // Retorna o menor Y
            return (forma->dados.linha.y1 < forma->dados.linha.y2) ? 
                    forma->dados.linha.y1 : forma->dados.linha.y2;

        case TIPO_TEXTO:
            return forma->dados.texto.y;
    }

    return -1;
}

/*==================================*/
/*  Setters e operações das formas  */
/*==================================*/


void forma_setCorBorda(Forma f, char* novaCorBorda) {
    if (novaCorBorda == NULL || novaCorBorda[0] != '#') {
        printf("Erro: cor invalida em forma_setCorBorda\n");
        return;
    }

    EstruturaForma* forma = (EstruturaForma*) f;
    if (f == NULL) {
        printf("Erro: forma nula em forma_setCorBorda\n");
        return;
    }

    char *novaCorAlocada = duplicar_string(novaCorBorda);
    if (novaCorAlocada == NULL) {
        printf("Erro ao alocar memoria em forma_setCorBorda\n");
        return;
    } 

    switch (forma->tipo) {
        case TIPO_CIRCULO:
            free(forma->dados.circulo.corb);
            forma->dados.circulo.corb = novaCorAlocada;
            return;

        case TIPO_RETANGULO:
            free(forma->dados.retangulo.corb);
            forma->dados.retangulo.corb = novaCorAlocada;
            return;

        case TIPO_LINHA:
            free(forma->dados.linha.cor);
            forma->dados.linha.cor = novaCorAlocada;
            return;
        
        case TIPO_TEXTO:
            free(forma->dados.texto.corb);
            forma->dados.texto.corb = novaCorAlocada;
            return;
    }
}


void forma_setCorPreenchimento(Forma f, char* novaCorPreenchimento) {
    if (novaCorPreenchimento == NULL || novaCorPreenchimento[0] != '#') {
        printf("Erro: cor invalida em forma_setCorPreenchimento\n");
        return;
    }

    EstruturaForma* forma = (EstruturaForma*) f;
    if (f == NULL) {
        printf("Erro: forma nula em forma_setCorPreenchimento\n");
        return;
    }

    char *novaCorAlocada = duplicar_string(novaCorPreenchimento);
    if (novaCorAlocada == NULL) {
        printf("Erro ao alocar memoria em forma_setCorPreenchimento\n");
        return;
    }

    switch (forma->tipo) {
        case TIPO_CIRCULO:
            free(forma->dados.circulo.corp);
            forma->dados.circulo.corp = novaCorAlocada;
            return;

        case TIPO_RETANGULO:
            free(forma->dados.retangulo.corp);
            forma->dados.retangulo.corp = novaCorAlocada;
            return;

        case TIPO_LINHA:
            // Linha não tem preenchimento
            free(novaCorAlocada);
            return;
        
        case TIPO_TEXTO:
            free(forma->dados.texto.corp);
            forma->dados.texto.corp = novaCorAlocada;
            return;
    }
}


void forma_desenhaSvg(Forma f, FILE* svg_file) {
    EstruturaForma *forma = (EstruturaForma*) f; 
    if (forma == NULL || svg_file == NULL) {
        return;
    }

    switch (forma->tipo) {
        case TIPO_CIRCULO:
            svg_desenha_circulo(svg_file,
                forma->dados.circulo.x, forma->dados.circulo.y,
                forma->dados.circulo.r,
                forma->dados.circulo.corb, forma->dados.circulo.corp);
            break;
            
        case TIPO_RETANGULO:
            svg_desenha_retangulo(svg_file,
                forma->dados.retangulo.x, forma->dados.retangulo.y,
                forma->dados.retangulo.w, forma->dados.retangulo.h,
                forma->dados.retangulo.corb, forma->dados.retangulo.corp);
            break;
            
        case TIPO_LINHA:
            svg_desenha_linha(svg_file,
                forma->dados.linha.x1, forma->dados.linha.y1,
                forma->dados.linha.x2, forma->dados.linha.y2,
                forma->dados.linha.cor);
            break;
            
        case TIPO_TEXTO:
            svg_desenha_texto(svg_file,
                forma->dados.texto.x, forma->dados.texto.y,
                forma->dados.texto.corb, forma->dados.texto.corp,
                forma->dados.texto.txto,
                estilo_getFamily(forma->dados.texto.estilo),
                estilo_getWeight(forma->dados.texto.estilo),
                estilo_getSize(forma->dados.texto.estilo),
                forma->dados.texto.a);
            break;
    }
}

// Estrutura auxiliar para coordenadas de segmento de texto
typedef struct {
    double x1, y1, x2, y2;
} SegmentoCoords;


static SegmentoCoords get_texto_segmento(EstruturaTexto *texto) {
    SegmentoCoords seg;
    double xt = texto->x;
    double yt = texto->y;
    int t = strlen(texto->txto);
    
    double comprimento_total = 10.0 * (double)t;
    double comprimento_metade = comprimento_total / 2.0;

    switch (texto->a) {
        case 'i': // Início: segmento parte da âncora para direita
            seg.x1 = xt;
            seg.y1 = yt;
            seg.x2 = xt + comprimento_total;
            seg.y2 = yt; 
            break;
            
        case 'f': // Fim: segmento vai da esquerda até a âncora
            seg.x1 = xt - comprimento_total;
            seg.y1 = yt;
            seg.x2 = xt;
            seg.y2 = yt;
            break;
            
        case 'm': // Meio: segmento centralizado na âncora
            seg.x1 = xt - comprimento_metade;
            seg.y1 = yt;
            seg.x2 = xt + comprimento_metade;
            seg.y2 = yt;
            break;
            
        default:
            // Caso padrão: trata como início
            seg.x1 = xt; 
            seg.y1 = yt;
            seg.x2 = xt + comprimento_total; 
            seg.y2 = yt;
            break;
    }
    
    return seg;
}


static int proximo_id_clone = 50000;

Forma forma_clonar(Forma original, double dx, double dy) {
    EstruturaForma *forma = (EstruturaForma *)original;
    if (original == NULL) { 
        return NULL;
    }

    int novoId = proximo_id_clone++;

    switch (forma->tipo) {
        case TIPO_CIRCULO:
            return circulo_cria(novoId, 
                                forma->dados.circulo.x + dx, 
                                forma->dados.circulo.y + dy, 
                                forma->dados.circulo.r, 
                                forma->dados.circulo.corb, 
                                forma->dados.circulo.corp);

        case TIPO_RETANGULO:
            return retangulo_cria(novoId, 
                                  forma->dados.retangulo.x + dx, 
                                  forma->dados.retangulo.y + dy, 
                                  forma->dados.retangulo.w, 
                                  forma->dados.retangulo.h, 
                                  forma->dados.retangulo.corb, 
                                  forma->dados.retangulo.corp);

        case TIPO_LINHA:
            return linha_cria(novoId, 
                              forma->dados.linha.x1 + dx, 
                              forma->dados.linha.y1 + dy, 
                              forma->dados.linha.x2 + dx, 
                              forma->dados.linha.y2 + dy, 
                              forma->dados.linha.cor);

        case TIPO_TEXTO:
            return texto_cria(novoId, 
                              forma->dados.texto.x + dx, 
                              forma->dados.texto.y + dy, 
                              forma->dados.texto.corb, 
                              forma->dados.texto.corp, 
                              forma->dados.texto.a, 
                              forma->dados.texto.txto, 
                              estilo_clona(forma->dados.texto.estilo));
    }

    return NULL;
}

// Contador global para IDs únicos de anteparos
static int proximo_id_anteparo = 100000;


Lista forma_para_anteparos(Forma f, char orientacao) {
    EstruturaForma* forma = (EstruturaForma*)f;
    if (forma == NULL) {
        return NULL;
    }
    
    Lista anteparos = lista_cria();
    if (anteparos == NULL) {
        return NULL;
    }
    
    char* cor = forma_getCorBorda(f);
    
    switch (forma->tipo) {
        
        case TIPO_CIRCULO: {
            double cx = forma->dados.circulo.x;
            double cy = forma->dados.circulo.y;
            double r = forma->dados.circulo.r;
            
            Anteparo ant;
            if (orientacao == 'h') {
                // Segmento horizontal: passa pelo centro
                ant = anteparo_cria(proximo_id_anteparo++, cx - r, cy, cx + r, cy, cor);
            } else {  // 'v'
                // Segmento vertical: passa pelo centro
                ant = anteparo_cria(proximo_id_anteparo++, cx, cy - r, cx, cy + r, cor);
            }
            
            lista_adiciona(anteparos, ant);
            break;
        }
        
        case TIPO_RETANGULO: {
            double x = forma->dados.retangulo.x;
            double y = forma->dados.retangulo.y;
            double w = forma->dados.retangulo.w;
            double h = forma->dados.retangulo.h;
            
            // Lado superior
            Anteparo ant1 = anteparo_cria(proximo_id_anteparo++, x, y, x + w, y, cor);
            lista_adiciona(anteparos, ant1);
            
            // Lado direito
            Anteparo ant2 = anteparo_cria(proximo_id_anteparo++, x + w, y, x + w, y + h, cor);
            lista_adiciona(anteparos, ant2);
            
            // Lado inferior
            Anteparo ant3 = anteparo_cria(proximo_id_anteparo++, x + w, y + h, x, y + h, cor);
            lista_adiciona(anteparos, ant3);
            
            // Lado esquerdo
            Anteparo ant4 = anteparo_cria(proximo_id_anteparo++, x, y + h, x, y, cor);
            lista_adiciona(anteparos, ant4);
            break;
        }
        
        case TIPO_LINHA: {
            // Linha já é um segmento
            Anteparo ant = anteparo_cria(proximo_id_anteparo++, forma->dados.linha.x1, forma->dados.linha.y1, forma->dados.linha.x2, forma->dados.linha.y2, cor);
            lista_adiciona(anteparos, ant);
            break;
        }
        
        case TIPO_TEXTO: {
            // Converte texto em segmento
            SegmentoCoords seg = get_texto_segmento(&forma->dados.texto);
            
            Anteparo ant = anteparo_cria(proximo_id_anteparo++, seg.x1, seg.y1, seg.x2, seg.y2, cor);
            lista_adiciona(anteparos, ant);
            break;
        }
    }
    
    return anteparos;
}


int forma_sobrepoe_visibilidade(Forma f, Poligono vis) {
    if (f == NULL || vis == NULL) return 0;
    
    EstruturaForma* forma = (EstruturaForma*)f;
    
    // Primeiro: testar bounding boxes
    double xmin_v, ymin_v, xmax_v, ymax_v;
    poligono_bounding_box(vis, &xmin_v, &ymin_v, &xmax_v, &ymax_v);
    
    double xmin_f, ymin_f, xmax_f, ymax_f;
    
    switch (forma->tipo) {
        case TIPO_CIRCULO:
            xmin_f = forma->dados.circulo.x - forma->dados.circulo.r;
            ymin_f = forma->dados.circulo.y - forma->dados.circulo.r;
            xmax_f = forma->dados.circulo.x + forma->dados.circulo.r;
            ymax_f = forma->dados.circulo.y + forma->dados.circulo.r;
            break;
            
        case TIPO_RETANGULO:
            xmin_f = forma->dados.retangulo.x;
            ymin_f = forma->dados.retangulo.y;
            xmax_f = forma->dados.retangulo.x + forma->dados.retangulo.w;
            ymax_f = forma->dados.retangulo.y + forma->dados.retangulo.h;
            break;
            
        case TIPO_LINHA:
            xmin_f = (forma->dados.linha.x1 < forma->dados.linha.x2) ? 
                     forma->dados.linha.x1 : forma->dados.linha.x2;
            ymin_f = (forma->dados.linha.y1 < forma->dados.linha.y2) ? 
                     forma->dados.linha.y1 : forma->dados.linha.y2;
            xmax_f = (forma->dados.linha.x1 > forma->dados.linha.x2) ? 
                     forma->dados.linha.x1 : forma->dados.linha.x2;
            ymax_f = (forma->dados.linha.y1 > forma->dados.linha.y2) ? 
                     forma->dados.linha.y1 : forma->dados.linha.y2;
            break;
            
        case TIPO_TEXTO:
            xmin_f = forma->dados.texto.x - 100;
            ymin_f = forma->dados.texto.y - 20;
            xmax_f = forma->dados.texto.x + 100;
            ymax_f = forma->dados.texto.y + 20;
            break;
            
        default:
            return 0;
    }
    
    if (xmax_f < xmin_v || xmin_f > xmax_v ||
        ymax_f < ymin_v || ymin_f > ymax_v) {
        return 0;
    }

    switch (forma->tipo) {
        case TIPO_CIRCULO: {
            double cx = forma->dados.circulo.x;
            double cy = forma->dados.circulo.y;
            double r = forma->dados.circulo.r;
            

            if (poligono_contem_ponto(vis, cx, cy)) return 1;
            
            for (int angulo = 0; angulo < 360; angulo += 10) {
                double rad = angulo * 3.14159265358979323846 / 180.0;
                double px = cx + r * cos(rad);
                double py = cy + r * sin(rad);
                if (poligono_contem_ponto(vis, px, py)) return 1;
            }
            
            // Algum vértice do polígono dentro do círculo?
            double* xs, * ys;
            int n;
            poligono_get_vertices(vis, &xs, &ys, &n);
            for (int i = 0; i < n; i++) {
                double dx = xs[i] - cx;
                double dy = ys[i] - cy;
                if (dx*dx + dy*dy <= r*r + 1e-6) return 1;
            }
            
            // Distância de alguma aresta do polígono até o centro <= r?
            for (int i = 0; i < n; i++) {
                int j = (i + 1) % n;
                double dist = geometria_distancia_ponto_segmento(cx, cy, xs[i], ys[i], xs[j], ys[j]);
                if (dist <= r + 1e-6) return 1;
            }
            
            return 0;
        }
        
        case TIPO_RETANGULO: {
            double x = forma->dados.retangulo.x;
            double y = forma->dados.retangulo.y;
            double w = forma->dados.retangulo.w;
            double h = forma->dados.retangulo.h;
            
            // Algum vértice do retângulo dentro do polígono?
            double vertices_rect[4][2] = {
                {x, y}, {x+w, y}, {x+w, y+h}, {x, y+h}
            };
            
            for (int i = 0; i < 4; i++) {
                if (poligono_contem_ponto(vis, vertices_rect[i][0], vertices_rect[i][1])) {
                    return 1;
                }
            }
            
            // Algum vértice do polígono dentro do retângulo?
            double* xs, * ys;
            int n;
            poligono_get_vertices(vis, &xs, &ys, &n);
            for (int i = 0; i < n; i++) {
                if (xs[i] >= x - 1e-6 && xs[i] <= x+w + 1e-6 &&
                    ys[i] >= y - 1e-6 && ys[i] <= y+h + 1e-6) {
                    return 1;
                }
            }
            
            // Intersecção de arestas
            for (int i = 0; i < n; i++) {
                int j = (i + 1) % n;
                
                if (geometria_segmentos_intersectam(xs[i], ys[i], xs[j], ys[j],
                                                     x, y, x+w, y)) return 1;
                if (geometria_segmentos_intersectam(xs[i], ys[i], xs[j], ys[j],
                                                     x+w, y, x+w, y+h)) return 1;
                if (geometria_segmentos_intersectam(xs[i], ys[i], xs[j], ys[j],
                                                     x+w, y+h, x, y+h)) return 1;
                if (geometria_segmentos_intersectam(xs[i], ys[i], xs[j], ys[j],
                                                     x, y+h, x, y)) return 1;
            }
            
            return 0;
        }
        
        case TIPO_LINHA: {
            double x1 = forma->dados.linha.x1;
            double y1 = forma->dados.linha.y1;
            double x2 = forma->dados.linha.x2;
            double y2 = forma->dados.linha.y2;
            
            // Algum extremo dentro?
            if (poligono_contem_ponto(vis, x1, y1)) return 1;
            if (poligono_contem_ponto(vis, x2, y2)) return 1;
            
            // Intersecção com o polígono?
            double* xs, * ys;
            int n;
            poligono_get_vertices(vis, &xs, &ys, &n);
            for (int i = 0; i < n; i++) {
                int j = (i + 1) % n;
                if (geometria_segmentos_intersectam(x1, y1, x2, y2, xs[i], ys[i], xs[j], ys[j])) {
                    return 1;
                }
            }
            
            return 0;
        }
        
        case TIPO_TEXTO: {
            double xt = forma->dados.texto.x;
            double yt = forma->dados.texto.y;
            
            // Ponto de âncora dentro?
            if (poligono_contem_ponto(vis, xt, yt)) return 1;
            
            // Aproximação - testa pontos em volta da âncora
            double offset = 60.0;
            if (poligono_contem_ponto(vis, xt - offset, yt - offset)) return 1;
            if (poligono_contem_ponto(vis, xt + offset, yt - offset)) return 1;
            if (poligono_contem_ponto(vis, xt + offset, yt + offset)) return 1;
            if (poligono_contem_ponto(vis, xt - offset, yt + offset)) return 1;
            
            // Segmento do texto intersecta polígono?
            SegmentoCoords seg = get_texto_segmento(&forma->dados.texto);
            
            double* xs, * ys;
            int n;
            poligono_get_vertices(vis, &xs, &ys, &n);
            for (int i = 0; i < n; i++) {
                int j = (i + 1) % n;
                if (geometria_segmentos_intersectam(seg.x1, seg.y1, seg.x2, seg.y2,
                                                     xs[i], ys[i], xs[j], ys[j])) {
                    return 1;
                }
            }
            
            return 0;
        }
    }
    
    return 0;
}