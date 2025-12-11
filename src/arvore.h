#ifndef ARVORE_H
#define ARVORE_H

/*
* TAD Árvore Binária de Busca Balanceada (AVL/Rubro-Negra).
* Estrutura fundamental para o algoritmo de varredura (Sweep Line).
* Armazena os "Segmentos Ativos" ordenados pela intersecção com o raio de varredura.
* Suporta contexto na função de comparação para ordenação dinâmica.
*/

typedef void* Arvore;

/*
* Ponteiro para função de comparação.
* Retorna <0 se a < b, 0 se a == b, >0 se a > b.
* O parâmetro 'contexto' permite passar dados externos (ex: linha de varredura atual)
* para decidir a ordem entre 'a' e 'b'.
*/
typedef int (*FuncaoComparacaoArvore)(void* a, void* b, void* contexto);

/*==========================*/
/* Construtor e Destrutor   */
/*==========================*/
/**
 * @brief Cria uma árvore vazia.
 * @param compara Função de callback para comparar dois elementos.
 * @param contexto Ponteiro genérico passado para a função de comparação (opcional).
 * @return Arvore A nova árvore criada.
 */
Arvore arvore_cria(FuncaoComparacaoArvore compara, void* contexto);

/**
 * @brief Destrói a árvore e libera seus nós internos.
 * @param arv A árvore a ser destruída.
 */
void arvore_destroi(Arvore arv);

/*==========================*/
/* Operações Principais     */
/*==========================*/
/**
 * @brief Insere um elemento na árvore mantendo o balanceamento.
 * @param arv A árvore.
 * @param elemento O dado a ser inserido.
 */
void arvore_insere(Arvore arv, void* elemento);

/**
 * @brief Remove um elemento da árvore.
 * @param arv A árvore.
 * @param elemento O elemento a ser removido (usando a função de comparação para achar).
 * @return void* O ponteiro para o dado removido, ou NULL se não encontrado.
 */
void* arvore_remove(Arvore arv, void* elemento);

/**
 * @brief Busca um elemento na árvore.
 * @param arv A árvore.
 * @param elemento O elemento chave de busca.
 * @return void* O elemento encontrado na árvore, ou NULL.
 */
void* arvore_busca(Arvore arv, void* elemento);

/*==========================*/
/* Consultas de Ordem       */
/*==========================*/
/**
 * @brief Encontra o sucessor (menor elemento estritamente maior que o dado).
 * Útil para encontrar o vizinho "acima" na linha de varredura.
 * @param arv A árvore.
 * @param elemento O elemento de referência.
 * @return void* O sucessor, ou NULL se não houver.
 */
void* arvore_sucessor(Arvore arv, void* elemento);

/**
 * @brief Encontra o antecessor (maior elemento estritamente menor que o dado).
 * Útil para encontrar o vizinho "abaixo" na linha de varredura.
 * @param arv A árvore.
 * @param elemento O elemento de referência.
 * @return void* O antecessor, ou NULL se não houver.
 */
void* arvore_predecessor(Arvore arv, void* elemento);

/*==========================*/
/* Auxiliares               */
/*==========================*/
/**
 * @brief Retorna a altura atual da árvore (profundidade máxima).
 * @param arv A árvore.
 * @return int A altura (0 se vazia).
 */
int arvore_altura(Arvore arv);

#endif