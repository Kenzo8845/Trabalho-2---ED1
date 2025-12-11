#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"


const char* SVG_HEADER_VIEWBOX = "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1000 700\" width=\"1000\" height=\"700\">\n";
const char* SVG_BACKGROUND = "\t<rect width=\"100%\" height=\"100%\" fill=\"#f4f4f4\" />\n";
const char* SVG_FOOTER = "</svg>\n";


FILE* svg_inicia(const char* path_svg) {
    FILE* f = fopen(path_svg, "w");
    if (f == NULL) {
        printf("Erro(0) em svg_inicia: Nao foi possivel criar o arquivo %s\n", path_svg);
        return NULL;
    }

    fprintf(f, "%s", SVG_HEADER_VIEWBOX);
    fprintf(f, "%s", SVG_BACKGROUND);
    
    return f;
}

void svg_finaliza(FILE* svg_file) {
    if (svg_file == NULL) return;
    fprintf(svg_file, "%s", SVG_FOOTER);
    fclose(svg_file);
}

/*===============================*/
/* Funções Primitivas de Desenho */
/*===============================*/

void svg_desenha_circulo(FILE* f, double x, double y, double r, char* corb, char* corp) {
    if (f == NULL) return;
    fprintf(f, "\t<circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.5\" stroke-width=\"1.5\" />\n", x, y, r, corb, corp);
}

void svg_desenha_retangulo(FILE* f, double x, double y, double w, double h, char* corb, char* corp) {
    if (f == NULL) return;
    fprintf(f, "\t<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.5\" stroke-width=\"1.5\" />\n", x, y, w, h, corb, corp);
}

void svg_desenha_linha(FILE* f, double x1, double y1, double x2, double y2, char* cor) {
    if (f == NULL) return;
    fprintf(f, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" stroke-width=\"2\" />\n",x1, y1, x2, y2, cor);
}

void svg_desenha_texto(FILE* f, double x, double y, char* corb, char* corp, char* txto, char* fFamily, char* fWeight, double fSize, char anr) {
    if (f == NULL) return;

    const char* anr_str = "start"; 
    if (anr == 'm') {
        anr_str = "middle";
    } else if (anr == 'f') {
        anr_str = "end";
    }

     const char* weight_svg = "normal";

    if (fWeight != NULL) {
        if (strcmp(fWeight, "n") == 0) {
            weight_svg = "normal";
        } else if (strcmp(fWeight, "b") == 0) {
            weight_svg = "bold";
        } else if (strcmp(fWeight, "b+") == 0) {
            weight_svg = "bolder";
        } else if (strcmp(fWeight, "l") == 0) {
            weight_svg = "lighter";
        } else {
            weight_svg = fWeight;
        }
    }

    const char* family_svg = "sans-serif";
    
    if (fFamily != NULL) {
        if (strcmp(fFamily, "sans") == 0) {
            family_svg = "sans-serif";
        } else if (strcmp(fFamily, "serif") == 0) {
            family_svg = "serif";
        } else if (strcmp(fFamily, "cursive") == 0) {
            family_svg = "cursive";
        } else {
            family_svg = fFamily;
        }
    }

    fprintf(f, "\t<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\" stroke=\"%s\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%.1fpx\" text-anchor=\"%s\">%s</text>\n", 
            x, y, corp, corb, family_svg, weight_svg, fSize, anr_str, txto);
}

void svg_desenha_asterisco(FILE* f, double x, double y) {
    if (f == NULL) return;
    fprintf(f, "\t<text x=\"%.2f\" y=\"%.2f\" fill=\"red\" font-weight=\"bold\" font-size=\"20px\" text-anchor=\"middle\">*</text>\n", x, y);
}

void svg_desenha_trajetoria(FILE* f, double x1, double y1, double x2, double y2) {
    if (f == NULL) return;
    
    fprintf(f, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" ""stroke=\"blue\" stroke-width=\"1.5\" stroke-dasharray=\"5,5\" ""opacity=\"0.6\" />\n", x1, y1, x2, y1);
    
    fprintf(f, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" ""stroke=\"blue\" stroke-width=\"1.5\" stroke-dasharray=\"5,5\" ""opacity=\"0.6\" />\n", x2, y1, x2, y2); 
}