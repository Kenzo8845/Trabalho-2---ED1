#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "formas.h"
#include "svg.h"

#define PATH_LEN 500
#define FILE_NAME_LEN 200

// Declarações das funções (protótipos)
Lista processaGeo(const char *path_geo);
void processaQry(const char *path_qry, Lista formas, 
                 const char *path_svg_saida, const char *path_txt_saida);

int main(int argc, char* argv[]) {
    char dir_entrada[PATH_LEN] = ".";
    char dir_saida[PATH_LEN] = ".";
    char arquivo_geo[FILE_NAME_LEN] = "";
    char arquivo_qry[FILE_NAME_LEN] = "";
    
    // Parse argumentos
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i+1 < argc) {
            strncpy(dir_entrada, argv[++i], PATH_LEN - 1);
            int len = strlen(dir_entrada);
            if (len > 0 && dir_entrada[len-1] == '/') 
                dir_entrada[len-1] = '\0';
        }
        else if (strcmp(argv[i], "-f") == 0 && i+1 < argc) {
            strncpy(arquivo_geo, argv[++i], FILE_NAME_LEN - 1);
        }
        else if (strcmp(argv[i], "-o") == 0 && i+1 < argc) {
            strncpy(dir_saida, argv[++i], PATH_LEN - 1);
            int len = strlen(dir_saida);
            if (len > 0 && dir_saida[len-1] == '/') 
                dir_saida[len-1] = '\0';
        }
        else if (strcmp(argv[i], "-q") == 0 && i+1 < argc) {
            strncpy(arquivo_qry, argv[++i], FILE_NAME_LEN - 1);
        }
    }
    
    if (strlen(arquivo_geo) == 0) {
        printf("Erro: -f é obrigatório\n");
        return 1;
    }
    
    // Monta caminhos
    char caminho_geo[PATH_LEN];
    snprintf(caminho_geo, PATH_LEN, "%s/%s", dir_entrada, arquivo_geo);
    
    // Extrai nome base do arquivo .geo (sem extensão)
    const char* inicio = strrchr(arquivo_geo, '/');
    if (inicio == NULL) inicio = arquivo_geo;
    else inicio++;
    
    char nome_base[FILE_NAME_LEN];
    strcpy(nome_base, inicio);
    char* ponto = strrchr(nome_base, '.');
    if (ponto != NULL) *ponto = '\0';
    
    // Processa .geo
    Lista formas = processaGeo(caminho_geo);
    
    if (formas == NULL) {
        printf("Erro ao processar arquivo .geo\n");
        return 1;
    }
    
    // Desenha SVG inicial
    char path_svg_geo[PATH_LEN];
    snprintf(path_svg_geo, PATH_LEN, "%s/%s.svg", dir_saida, nome_base);
    FILE* svg_geo = svg_inicia(path_svg_geo);
    
    if (svg_geo != NULL) {
        int n;
        void** array = lista_para_array(formas, &n);
        if (array != NULL) {
            for (int i = 0; i < n; i++) {
                Forma f = (Forma)array[i];
                if (f != NULL) forma_desenhaSvg(f, svg_geo);
            }
            free(array);
        }
        svg_finaliza(svg_geo);
    }
    
    // Processa .qry se fornecido
    if (strlen(arquivo_qry) > 0) {
        char caminho_qry[PATH_LEN];
        snprintf(caminho_qry, PATH_LEN, "%s/%s", dir_entrada, arquivo_qry);
        
        // Extrai nome base do .qry
        inicio = strrchr(arquivo_qry, '/');
        if (inicio == NULL) inicio = arquivo_qry;
        else inicio++;
        
        char nome_qry[FILE_NAME_LEN];
        strcpy(nome_qry, inicio);
        ponto = strrchr(nome_qry, '.');
        if (ponto != NULL) *ponto = '\0';
        
        // Cria SVG de saída do .qry
        char path_svg_qry[PATH_LEN];
        char path_txt_qry[PATH_LEN];
        snprintf(path_svg_qry, PATH_LEN, "%s/%s-%s.svg", dir_saida, nome_base, nome_qry);
        snprintf(path_txt_qry, PATH_LEN, "%s/%s-%s.txt", dir_saida, nome_base, nome_qry);
        
        // Processa comando .qry
        processaQry(caminho_qry, formas, path_svg_qry, path_txt_qry);
    }
    
        if (formas != NULL) {
        int n;
        void** array = lista_para_array(formas, &n);
        if (array != NULL) {
            for (int i = 0; i < n; i++) {
                Forma f = (Forma)array[i];
                if (f != NULL) {
                    forma_destroi(f);
                }
            }
            free(array);
        }
        lista_destruir(formas);
    }
    
    return 0;
}