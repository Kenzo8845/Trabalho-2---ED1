#include "formas.h"
#include "estilo.h"
#include "svg.h"
#include "anteparo.h"
#include "lista.h"

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

/**
 * @brief Cria um novo círculo.
 * @param i Identificador único do círculo.
 * @param x Coordenada X do centro.
 * @param y Coordenada Y do centro.
 * @param r Raio do círculo.
 * @param corb Cor da borda.
 * @param corp Cor do preenchimento.
 * @return Forma Ponteiro para a forma criada, ou NULL em caso de erro.
 */
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

/**
 * @brief Cria um novo retângulo.
 * @param i Identificador único do retângulo.
 * @param x Coordenada X da âncora (canto inferior esquerdo).
 * @param y Coordenada Y da âncora (canto inferior esquerdo).
 * @param w Largura do retângulo.
 * @param h Altura do retângulo.
 * @param corb Cor da borda.
 * @param corp Cor do preenchimento.
 * @return Forma Ponteiro para a forma criada, ou NULL em caso de erro.
 */
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

/**
 * @brief Cria uma nova linha.
 * @param i Identificador único da linha.
 * @param x1 Coordenada X do ponto inicial.
 * @param y1 Coordenada Y do ponto inicial.
 * @param x2 Coordenada X do ponto final.
 * @param y2 Coordenada Y do ponto final.
 * @param cor Cor da linha.
 * @return Forma Ponteiro para a forma criada, ou NULL em caso de erro.
 */
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

/**
 * @brief Cria um novo texto.
 * @param i Identificador único do texto.
 * @param x Coordenada X da âncora.
 * @param y Coordenada Y da âncora.
 * @param corb Cor da borda.
 * @param corp Cor do preenchimento.
 * @param a Posição da âncora ('i': início, 'm': meio, 'f': fim).
 * @param txto String com o texto.
 * @param e Estilo do texto (família, peso, tamanho da fonte).
 * @return Forma Ponteiro para a forma criada, ou NULL em caso de erro.
 */
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

/**
 * @brief Libera a memória alocada para uma forma.
 * @param f Forma a ser destruída.
 */
void forma_destruir(Forma f) {
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

/**
 * @brief Retorna o identificador único da forma.
 * @param f Forma.
 * @return int ID da forma, ou -1 em caso de erro.
 */
int forma_getId(Forma f) {
    EstruturaForma *forma = (EstruturaForma *)f;
    if (f == NULL) { 
        return -1;
    }
    return forma->id;
}

/**
 * @brief Retorna a cor de preenchimento da forma.
 * @param f Forma.
 * @return char* Cor de preenchimento, ou NULL em caso de erro.
 */
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

/**
 * @brief Retorna a cor da borda da forma.
 * @param f Forma.
 * @return char* Cor da borda, ou NULL em caso de erro.
 */
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

/**
 * @brief Retorna a coordenada X da âncora da forma.
 * @param f Forma.
 * @return double Coordenada X, ou -1 em caso de erro.
 */
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

/**
 * @brief Retorna a coordenada Y da âncora da forma.
 * @param f Forma.
 * @return double Coordenada Y, ou -1 em caso de erro.
 */
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

/**
 * @brief Altera a cor da borda de uma forma.
 * @param f Forma a ser modificada.
 * @param novaCorBorda Nova cor da borda (formato "#RRGGBB").
 */
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

/**
 * @brief Altera a cor de preenchimento de uma forma.
 * @param f Forma a ser modificada.
 * @param novaCorPreenchimento Nova cor de preenchimento.
 */
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

/*=======================*/
/* Função de Desenho SVG */
/*=======================*/

/**
 * @brief Desenha uma forma em um arquivo SVG.
 * @param f Forma a ser desenhada.
 * @param svg_file Ponteiro para o arquivo SVG aberto.
 */
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

/*========================================*/
/* Conversão de Forma para Anteparos     */
/*========================================*/

// Estrutura auxiliar para coordenadas de segmento de texto
typedef struct {
    double x1, y1, x2, y2;
} SegmentoCoords;

/**
 * @brief Calcula as coordenadas do segmento equivalente de um texto.
 * @param texto Estrutura interna do texto.
 * @return SegmentoCoords Coordenadas do segmento.
 */
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

// Contador global para IDs únicos de anteparos
static int proximo_id_anteparo = 100000;

/**
 * @brief Converte uma forma em anteparos (segmentos).
 * 
 * - Círculo: 1 segmento (horizontal ou vertical, conforme orientação)
 * - Retângulo: 4 segmentos (os 4 lados)
 * - Linha: 1 segmento (ela mesma)
 * - Texto: 1 segmento (baseado na âncora e comprimento)
 * 
 * @param f Forma a ser convertida.
 * @param orientacao Orientação do segmento para círculos ('h': horizontal, 'v': vertical).
 * @return Lista Lista de anteparos criados, ou NULL em caso de erro.
 */
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
                ant = anteparo_cria(proximo_id_anteparo++, 
                                    cx - r, cy, cx + r, cy, cor);
            } else {  // 'v'
                // Segmento vertical: passa pelo centro
                ant = anteparo_cria(proximo_id_anteparo++, 
                                    cx, cy - r, cx, cy + r, cor);
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
            Anteparo ant1 = anteparo_cria(proximo_id_anteparo++, 
                                          x, y, x + w, y, cor);
            lista_adiciona(anteparos, ant1);
            
            // Lado direito
            Anteparo ant2 = anteparo_cria(proximo_id_anteparo++, 
                                          x + w, y, x + w, y + h, cor);
            lista_adiciona(anteparos, ant2);
            
            // Lado inferior
            Anteparo ant3 = anteparo_cria(proximo_id_anteparo++, 
                                          x + w, y + h, x, y + h, cor);
            lista_adiciona(anteparos, ant3);
            
            // Lado esquerdo
            Anteparo ant4 = anteparo_cria(proximo_id_anteparo++, 
                                          x, y + h, x, y, cor);
            lista_adiciona(anteparos, ant4);
            break;
        }
        
        case TIPO_LINHA: {
            // Linha já é um segmento
            Anteparo ant = anteparo_cria(proximo_id_anteparo++,
                                         forma->dados.linha.x1,
                                         forma->dados.linha.y1,
                                         forma->dados.linha.x2,
                                         forma->dados.linha.y2,
                                         cor);
            lista_adiciona(anteparos, ant);
            break;
        }
        
        case TIPO_TEXTO: {
            // Converte texto em segmento
            SegmentoCoords seg = get_texto_segmento(&forma->dados.texto);
            
            Anteparo ant = anteparo_cria(proximo_id_anteparo++,
                                         seg.x1, seg.y1, seg.x2, seg.y2, cor);
            lista_adiciona(anteparos, ant);
            break;
        }
    }
    
    return anteparos;
}