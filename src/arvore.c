
#include "arvore.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct No {
    void* elemento;
    struct No* esq;
    struct No* dir;
    int altura;
} NoArvore;

typedef struct {
    NoArvore* raiz;
    FuncaoComparacaoArvore compara;
    void* contexto;  
} EstruturaArvore;

static int altura(NoArvore* no) {
    return (no == NULL) ? 0 : no->altura;
}

// Retorna o maior valor entre a e b, usado na comparação de alturas.
static int max(int a, int b) {
    return (a > b) ? a : b;
}

// Fator de balanceamento de um Node, essencial para manter a arvore AVL equilibrada.
static int fator_balanceamento(NoArvore* no) {
    return (no == NULL) ? 0 : altura(no->esq) - altura(no->dir);
}

// Corrige a altura de um Node.
static void atualiza_altura(NoArvore* no) {
    if (no != NULL) {
        no->altura = 1 + max(altura(no->esq), altura(no->dir));
    }
}

static NoArvore* rotacao_direita(NoArvore* y) {
    NoArvore* x = y->esq;
    NoArvore* B = x->dir;
    
    x->dir = y;
    y->esq = B;
    
    atualiza_altura(y);
    atualiza_altura(x);
    
    return x;
}

static NoArvore* rotacao_esquerda(NoArvore* x) {
    NoArvore* y = x->dir;
    NoArvore* B = y->esq;
    
    y->esq = x;
    x->dir = B;
    
    atualiza_altura(x);
    atualiza_altura(y);
    
    return y;
}

static NoArvore* balancear(NoArvore* no) {
    atualiza_altura(no);
    int fb = fator_balanceamento(no);
    
    // Caso Esquerda-Esquerda
    if (fb > 1 && fator_balanceamento(no->esq) >= 0) {
        return rotacao_direita(no);
    }
    
    // Caso Esquerda-Direita
    if (fb > 1 && fator_balanceamento(no->esq) < 0) {
        no->esq = rotacao_esquerda(no->esq);
        return rotacao_direita(no);
    }
    
    // Caso Direita-Direita
    if (fb < -1 && fator_balanceamento(no->dir) <= 0) {
        return rotacao_esquerda(no);
    }
    
    // Caso Direita-Esquerda
    if (fb < -1 && fator_balanceamento(no->dir) > 0) {
        no->dir = rotacao_direita(no->dir);
        return rotacao_esquerda(no);
    }
    
    return no;
}

// ========== OPERAÇÕES PRINCIPAIS ==========

Arvore arvore_cria(FuncaoComparacaoArvore compara, void* contexto) {
    EstruturaArvore* arv = (EstruturaArvore*)malloc(sizeof(EstruturaArvore));
    if (arv == NULL) return NULL;
    
    arv->raiz = NULL;
    arv->compara = compara;
    arv->contexto = contexto;
    
    return (Arvore)arv;
}

static NoArvore* inserir_no(NoArvore* no, void* elemento, FuncaoComparacaoArvore compara, void* contexto) {
    if (no == NULL) {
        NoArvore* novo = (NoArvore*)malloc(sizeof(NoArvore));
        novo->elemento = elemento;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 1;
        return novo;
    }
    
    
    int cmp = compara(elemento, no->elemento, contexto);
    
    if (cmp < 0) {
        no->esq = inserir_no(no->esq, elemento, compara, contexto);
    } else if (cmp > 0) {
        no->dir = inserir_no(no->dir, elemento, compara, contexto);
    } else {
        return no;
    }
    
    return balancear(no);
}

void arvore_insere(Arvore arv, void* elemento) {
    EstruturaArvore* arvore = (EstruturaArvore*)arv;
    if (arvore == NULL || elemento == NULL) return;
    
    arvore->raiz = inserir_no(arvore->raiz, elemento, arvore->compara, arvore->contexto);
}

static NoArvore* buscar_no(NoArvore* no, void* elemento, FuncaoComparacaoArvore compara, void* contexto) {
    if (no == NULL) return NULL;
    
    int cmp = compara(elemento, no->elemento, contexto);
    
    if (cmp < 0) {
        return buscar_no(no->esq, elemento, compara, contexto);
    } else if (cmp > 0) {
        return buscar_no(no->dir, elemento, compara, contexto);
    } else {
        return no;
    }
}

void* arvore_busca(Arvore arv, void* elemento) {
    EstruturaArvore* arvore = (EstruturaArvore*)arv;
    if (arvore == NULL) return NULL;
    
    NoArvore* no = buscar_no(arvore->raiz, elemento, arvore->compara, arvore->contexto);
    
    return (no != NULL) ? no->elemento : NULL;
}

static NoArvore* achar_minimo(NoArvore* no) {
    while (no->esq != NULL) {
        no = no->esq;
    }
    return no;
}

static NoArvore* remover_no(NoArvore* no, void* elemento, FuncaoComparacaoArvore compara, void* contexto,void** elemento_removido) {
    if (no == NULL) return NULL;
    
    int cmp = compara(elemento, no->elemento, contexto);
    
    if (cmp < 0) {
        no->esq = remover_no(no->esq, elemento, compara, contexto, elemento_removido);
    } else if (cmp > 0) {
        no->dir = remover_no(no->dir, elemento, compara, contexto, elemento_removido);
    } else {
        *elemento_removido = no->elemento;
        
        if (no->esq == NULL) {
            NoArvore* temp = no->dir;
            free(no);
            return temp;
        } else if (no->dir == NULL) {
            NoArvore* temp = no->esq;
            free(no);
            return temp;
        }
        
        NoArvore* temp = achar_minimo(no->dir);
        no->elemento = temp->elemento;
        no->dir = remover_no(no->dir, temp->elemento, compara, contexto, elemento_removido);
    }
    
    return balancear(no);
}

void* arvore_remove(Arvore arv, void* elemento) {
    EstruturaArvore* arvore = (EstruturaArvore*)arv;
    if (arvore == NULL) return NULL;
    
    void* elemento_removido = NULL;
    arvore->raiz = remover_no(arvore->raiz, elemento, arvore->compara, arvore->contexto,&elemento_removido);
    
    return elemento_removido;
}

static void destruir_no(NoArvore* no) {
    if (no == NULL) return;
    destruir_no(no->esq);
    destruir_no(no->dir);
    free(no);
}

void arvore_destroi(Arvore arv) {
    EstruturaArvore* arvore = (EstruturaArvore*)arv;
    if (arvore == NULL) return;
    
    destruir_no(arvore->raiz);
    free(arvore);
}

int arvore_altura(Arvore arv) {
    EstruturaArvore* arvore = (EstruturaArvore*)arv;
    if (arvore == NULL) return 0;
    return altura(arvore->raiz);
}