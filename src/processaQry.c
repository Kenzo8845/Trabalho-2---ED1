#include "lista.h"
#include "formas.h"
#include "anteparo.h"
#include "visibilidade.h"
#include "svg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processaQry(const char *path_qry, Lista formas, const char *path_svg_saida, const char *path_txt_saida) {
    
    FILE *arquivo_qry = fopen(path_qry, "r");
    if (arquivo_qry == NULL) {
        printf("Erro ao abrir arquivo .qry: %s\n", path_qry);
        return;
    }
    
    FILE *svg_saida = svg_inicia(path_svg_saida);
    FILE *txt_saida = fopen(path_txt_saida, "w");
    
    if (svg_saida == NULL || txt_saida == NULL) {
        printf("Erro ao criar arquivos de saída\n");
        fclose(arquivo_qry);
        return;
    }
    
    char buffer[512];
    char comando[16];
    Lista anteparos = lista_cria();
    
    while (fgets(buffer, sizeof(buffer), arquivo_qry) != NULL) {
        // Ignora linhas vazias e comentários
        if (buffer[0] == '\n' || buffer[0] == '#') {
            continue;
        }
        
        comando[0] = '\0';
        sscanf(buffer, "%s", comando);
        
        // Comando 'a': Transformar forma em anteparo
        if (strcmp(comando, "a") == 0) {
            int id_min, id_max;
            char orientacao[8] = "h";
            sscanf(buffer, "a %d %d %s", &id_min, &id_max, orientacao);
            
            char orient = orientacao[0];
            
            fprintf(txt_saida, "[*] a %d %d %c\n", id_min, id_max, orient);
            
            // Cria lista temporária de formas a remover
            Lista formas_remover = lista_cria();
            
            // Percorre formas e transforma em anteparos
            int n;
            void** array = lista_para_array(formas, &n);
            if (array != NULL) {
                for (int i = 0; i < n; i++) {
                    Forma f = (Forma)array[i];
                    int id = forma_getId(f);
                    
                    if (id >= id_min && id <= id_max) {
                        // Cria anteparos da forma
                        Lista anteparos_forma = forma_para_anteparos(f, orient);
                        if (anteparos_forma != NULL) {
                            int n_ant;
                            void** arr_ant = lista_para_array(anteparos_forma, &n_ant);
                            if (arr_ant != NULL) {
                                for (int j = 0; j < n_ant; j++) {
                                    lista_adiciona(anteparos, arr_ant[j]);
                                }
                                free(arr_ant);
                            }
                            lista_destruir(anteparos_forma);
                        }
                        
                        fprintf(txt_saida, "Forma %d transformada em anteparo\n", id);
                        lista_adiciona(formas_remover, f);
                    }
                }
                free(array);
            }
            
            // Remove e destroi as formas depois do loop
            int n_rem;
            void** arr_rem = lista_para_array(formas_remover, &n_rem);
            if (arr_rem != NULL) {
                for (int i = 0; i < n_rem; i++) {
                    Forma f = (Forma)arr_rem[i];
                    lista_retira(formas, f);
                    forma_destroi(f);
                }
                free(arr_rem);
            }
            lista_destruir(formas_remover);
        }
        
        // Comando 'd': Bomba de destruição
        else if (strcmp(comando, "d") == 0) {
            double x, y;
            char sufx[64] = "-";
            sscanf(buffer, "d %lf %lf %s", &x, &y, sufx);
            
            fprintf(txt_saida, "[*] d %.2f %.2f\n", x, y);
            
            // Desenha anteparos primeiro
            int n_ant;
            void** arr_ant = lista_para_array(anteparos, &n_ant);
            if (arr_ant != NULL) {
                for (int i = 0; i < n_ant; i++) {
                    Anteparo a = (Anteparo)arr_ant[i];
                    anteparo_desenha_svg(a, svg_saida);
                }
                free(arr_ant);
            }

            svg_desenha_asterisco(svg_saida, x, y);
            
            // Calcula região de visibilidade
            Poligono vis = calcula_regiao_visibilidade(x, y, anteparos);
            
            if (vis != NULL) {
                // Desenha região de visibilidade
                poligono_desenha_svg(vis, svg_saida, "#FF6B6B");
                
                // Cria lista temporária de formas a remover
                Lista formas_remover = lista_cria();
                
                // Encontra formas dentro da região
                int n;
                void** array = lista_para_array(formas, &n);
                if (array != NULL) {
                    for (int i = 0; i < n; i++) {
                        Forma f = (Forma)array[i];
                        if (f != NULL && forma_sobrepoe_visibilidade(f, vis)) {
                            fprintf(txt_saida, "Destruída: forma %d\n", forma_getId(f));
                            lista_adiciona(formas_remover, f);
                        }
                    }
                    free(array);
                }
                
                // Remove e destroi depois do loop
                int n_rem;
                void** arr_rem = lista_para_array(formas_remover, &n_rem);
                if (arr_rem != NULL) {
                    for (int i = 0; i < n_rem; i++) {
                        Forma f = (Forma)arr_rem[i];
                        lista_retira(formas, f);
                        forma_destroi(f);
                    }
                    free(arr_rem);
                }
                lista_destruir(formas_remover);
                
                poligono_destroi(vis);
            }
        }
        
        // Comando 'p': Bomba de pintura
        else if (strcmp(comando, "p") == 0) {
            double x, y;
            char cor[32];
            char sufx[64] = "-";
            sscanf(buffer, "p %lf %lf %s %s", &x, &y, cor, sufx);
            
            fprintf(txt_saida, "[*] p %.2f %.2f %s\n", x, y, cor);
            
            // Desenha anteparos
            int n_ant;
            void** arr_ant = lista_para_array(anteparos, &n_ant);
            if (arr_ant != NULL) {
                for (int i = 0; i < n_ant; i++) {
                    Anteparo a = (Anteparo)arr_ant[i];
                    anteparo_desenha_svg(a, svg_saida);
                }
                free(arr_ant);
            }
            

            Poligono vis = calcula_regiao_visibilidade(x, y, anteparos);
            
            if (vis != NULL) {
                poligono_desenha_svg(vis, svg_saida, "#4ECDC4");
                
                // Pinta formas dentro da região
                int n;
                void** array = lista_para_array(formas, &n);
                if (array != NULL) {
                    for (int i = 0; i < n; i++) {
                        Forma f = (Forma)array[i];
                        if (f != NULL && forma_sobrepoe_visibilidade(f, vis)) {
                            fprintf(txt_saida, "Pintada: forma %d\n", forma_getId(f));
                            forma_setCorPreenchimento(f, (char*)cor);
                            forma_setCorBorda(f, (char*)cor);
                        }
                    }
                    free(array);
                }
                
                poligono_destroi(vis);
            }
        }
        
        // Comando 'cln': Bomba de clonagem
        else if (strcmp(comando, "cln") == 0) {
            double x, y, dx, dy;
            char sufx[64] = "-";
            sscanf(buffer, "cln %lf %lf %lf %lf %s", &x, &y, &dx, &dy, sufx);
            
            fprintf(txt_saida, "[*] cln %.2f %.2f %.2f %.2f\n", x, y, dx, dy);
            
            // Desenha anteparos
            int n_ant;
            void** arr_ant = lista_para_array(anteparos, &n_ant);
            if (arr_ant != NULL) {
                for (int i = 0; i < n_ant; i++) {
                    Anteparo a = (Anteparo)arr_ant[i];
                    anteparo_desenha_svg(a, svg_saida);
                }
                free(arr_ant);
            }
            
            // Calcula região de visibilidade
            Poligono vis = calcula_regiao_visibilidade(x, y, anteparos);
            
            if (vis != NULL) {
                poligono_desenha_svg(vis, svg_saida, "#95E1D3");
                
                // Clona formas dentro da região
                int n;
                void** array = lista_para_array(formas, &n);
                if (array != NULL) {
                    for (int i = 0; i < n; i++) {
                        Forma f = (Forma)array[i];
                        if (f != NULL && forma_sobrepoe_visibilidade(f, vis)) {
                            Forma clone = forma_clonar(f, dx, dy);
                            if (clone != NULL) {
                                fprintf(txt_saida, "Clonada: forma %d como %d\n", 
                                        forma_getId(f), forma_getId(clone));
                                lista_adiciona(formas, clone);
                            }
                        }
                    }
                    free(array);
                }
                
                poligono_destroi(vis);
            }
        }
    }
    
    // Limpa anteparos
    int n;
    void** array = lista_para_array(anteparos, &n);
    if (array != NULL) {
        for (int i = 0; i < n; i++) {
            anteparo_destroi((Anteparo)array[i]);
        }
        free(array);
    }
    lista_destruir(anteparos);
    
    // Desenha formas finais
    array = lista_para_array(formas, &n);
    if (array != NULL) {
        for (int i = 0; i < n; i++) {
            Forma f = (Forma)array[i];
            if (f != NULL) {
                forma_desenhaSvg(f, svg_saida);
            }
        }
        free(array);
    }
    
    svg_finaliza(svg_saida);
    fclose(txt_saida);
    fclose(arquivo_qry);
}