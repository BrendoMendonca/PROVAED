#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura para um elemento não-zero na matriz esparsa
struct nnz {
    double info;      // Valor do elemento não-zero
    int linha;        // Índice da linha
    int coluna;       // Índice da coluna
    struct nnz* prox; // Ponteiro para o próximo elemento não-zero na mesma linha
};

// Definição da estrutura para uma linha na matriz esparsa, que contém elementos não-zero
struct linha {
    int linha;            // Índice da linha
    struct nnz* inicio;   // Ponteiro para o primeiro elemento não-zero na linha
    struct linha* prox;   // Ponteiro para a próxima linha que contém elementos não-zero
};

// Definição da estrutura para a matriz esparsa como um todo
struct mesparsa {
    struct linha* inicio; // Ponteiro para a primeira linha que contém elementos não-zero
};

typedef struct nnz Nnz;
typedef struct linha Linha;
typedef struct mesparsa Mesparsa;

// Função para criar um novo elemento não-zero
Nnz* cria_nnz(int linha, int coluna, double info) {
    Nnz* n = (Nnz*)malloc(sizeof(Nnz));
    if (!n) {
        return NULL; // Falha na alocação de memória
    }
    n->linha = linha;
    n->coluna = coluna;
    n->info = info;
    n->prox = NULL;
    return n;
}

// Função para criar uma nova linha
Linha* cria_linha(int linha) {
    Linha* l = (Linha*)malloc(sizeof(Linha));
    if (!l) {
        return NULL; // Falha na alocação de memória
    }
    l->linha = linha;
    l->inicio = NULL;
    l->prox = NULL;
    return l;
}

// Função para criar uma matriz esparsa vazia
Mesparsa* cria_mesparsa() {
    Mesparsa* m = (Mesparsa*)malloc(sizeof(Mesparsa));
    if (!m) {
        return NULL; // Falha na alocação de memória
    }
    m->inicio = NULL;
    return m;
}

// Função para contar a quantidade de linhas na matriz esparsa
int qtd_linhas(Mesparsa* m) {
    if (!m) {
        return 0;
    }
    if (m->inicio == NULL) {
        return 0;
    }
    int count = 1;
    Linha* aux = m->inicio;
    while (aux->prox != NULL) {
        aux = aux->prox;
        count++;
    }
    return count;
}

// Função para contar a quantidade de elementos não-zero em uma linha
int qtd_nnz(Linha* linha) {
    if (!linha) {
        return 0;
    }
    if (linha->inicio == NULL) {
        return 0;
    }
    int count = 1;
    Nnz* aux2 = linha->inicio;
    while (aux2->prox != NULL) {
        aux2 = aux2->prox;
        count++;
    }
    return count;
}

// Função para liberar toda a memória alocada para a matriz esparsa
void libera_mesparsa(Mesparsa** matriz) {
    if (!(*matriz)) {
        return;
    }
    Linha* aux = (*matriz)->inicio;
    while (aux != NULL) {
        Nnz* aux2 = aux->inicio;
        while (aux2 != NULL) {
            aux->inicio = aux2->prox;
            free(aux2); // Libera cada elemento não-zero
            aux2 = aux->inicio;
        }
        (*matriz)->inicio = aux->prox;
        free(aux); // Libera a linha
        aux = (*matriz)->inicio;
    }
    free((*matriz)); // Libera a matriz esparsa
    *matriz = NULL;
}

// Função para inserir um novo elemento não-zero em uma linha específica
int insere_na_linha(Linha* l, int linha, int coluna, double info) {
    if (l->inicio == NULL) {
        Nnz* n = cria_nnz(linha, coluna, info);
        if (!n) {
            return 0; // Falha na criação do elemento
        }
        l->inicio = n;
        return 1;
    }
    Nnz* n = cria_nnz(linha, coluna, info);
    if (!n) {
        return 0;
    }
    // Inserção mantém ordem crescente das colunas
    if (l->inicio->coluna > coluna) {
        n->prox = l->inicio;
        l->inicio = n;
        return 1;
    }
    Nnz* aux2 = l->inicio;
    while (aux2->prox != NULL && aux2->prox->coluna < coluna) {
        aux2 = aux2->prox;
    }
    if (aux2->prox == NULL) {
        aux2->prox = n;
        return 1;
    }
    n->prox = aux2->prox;
    aux2->prox = n;
    return 1;
}

// Função para inserir um elemento não-zero na matriz esparsa
int insere_nnz(Mesparsa* matriz, int linha, int coluna, double info) {
    if (!matriz) {
        return 0;
    }
    Linha* l = cria_linha(linha);
    if (!l) {
        return 0; // Falha na criação da linha
    }
    // Inserção de linha mantém ordem crescente das linhas
    if (matriz->inicio == NULL) {
        matriz->inicio = l;
        return insere_na_linha(l, linha, coluna, info);
    }
    Linha* aux = matriz->inicio;
    while (aux->prox != NULL && aux->linha != linha && aux->prox->linha <= linha) {
        aux = aux->prox;
    }
    if (aux->linha > linha) {
        l->prox = aux;
        matriz->inicio = l;
        return insere_na_linha(l, linha, coluna, info);
    }
    if (aux->linha == linha) {
        return insere_na_linha(aux, linha, coluna, info);
    }
    if (aux->prox == NULL) {
        aux->prox = l;
        return insere_na_linha(l, linha, coluna, info);
    }
    l->prox = aux->prox;
    aux->prox = l;
    return insere_na_linha(l, linha, coluna, info);
}

// Função para remover um elemento não-zero da matriz esparsa
int remove_nnz(Mesparsa* matriz, int linha, int coluna) {
    if (!matriz) {
        return 0;
    }
    if (matriz->inicio == NULL) {
        return 0;
    }
    Linha* aux = matriz->inicio;
    while (aux != NULL && aux->linha != linha) {
        aux = aux->prox;
    }
    if (aux == NULL) {
        return 0; // Linha não encontrada
    }
    if (aux->inicio == NULL) {
        return 0; // Linha vazia
    }
    Nnz* aux2 = aux->inicio;
    if (aux->inicio->coluna == coluna) {
        aux->inicio = aux2->prox;
        free(aux2);
        return 1;
    }
    while (aux2->prox != NULL && aux2->prox->coluna != coluna) {
        aux2 = aux2->prox;
    }
    if (aux2->prox == NULL) {
        return 0; // Elemento não encontrado
    }
    Nnz* aux3 = aux2->prox;
    aux2->prox = aux3->prox;
    free(aux3);
    return 1;
}

// Função para imprimir a matriz esparsa
void imprime_mesparsa(Mesparsa* matriz) {
    if (!matriz) {
        return;
    }
    if (matriz->inicio == NULL) {
        return; // Matriz vazia
    }
    Linha* aux = matriz->inicio;
    while (aux != NULL) {
        if (aux->inicio == NULL) {
            aux = aux->prox;
            continue; // Pula linhas vazias
        }
        Nnz* nnz = aux->inicio;
        while (nnz != NULL) {
            printf("[(%d, %d)=%.2f]", nnz->linha, nnz->coluna, nnz->info);
            nnz = nnz->prox;
        }
        printf("\n");
        aux = aux->prox;
    }
}
