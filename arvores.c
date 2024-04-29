#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct no {
    int info;
    struct no* esq;
    struct no* dir;
};

typedef struct no No;

No* cria_no(int info) {
    No* n = (No*)malloc(sizeof(No));
    if (!n) return NULL;
    n->info = info;
    n->esq = NULL;
    n->dir = NULL;
    return n;
}

bool insere_arvore(No** raiz, int info) {
    if (*raiz == NULL) {
        *raiz = cria_no(info);
        return true;
    }
    if (info < (*raiz)->info) {
        return insere_arvore(&(*raiz)->esq, info);
    } else if (info > (*raiz)->info) {
        return insere_arvore(&(*raiz)->dir, info);
    }
    return false;
}

No* remove_arvore(No* raiz, int info) {
    if (raiz == NULL) {
        return NULL;
    }
    if (info < raiz->info) {
        raiz->esq = remove_arvore(raiz->esq, info);
    } else if (info > raiz->info) {
        raiz->dir = remove_arvore(raiz->dir, info);
    } else {
        // Nó com um filho ou nenhum filho
        if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        // Nó com dois filhos: Pegue o sucessor in-order (menor na subárvore direita)
        No* temp = raiz->dir;
        while (temp && temp->esq != NULL) {
            temp = temp->esq;
        }
        raiz->info = temp->info;
        raiz->dir = remove_arvore(raiz->dir, temp->info);
    }
    return raiz;
}

void exibe_pre_ordem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->info);
        exibe_pre_ordem(raiz->esq);
        exibe_pre_ordem(raiz->dir);
    }
}

void exibe_in_ordem(No* raiz) {
    if (raiz != NULL) {
        exibe_in_ordem(raiz->esq);
        printf("%d ", raiz->info);
        exibe_in_ordem(raiz->dir);
    }
}

void exibe_pos_ordem(No* raiz) {
    if (raiz != NULL) {
        exibe_pos_ordem(raiz->esq);
        exibe_pos_ordem(raiz->dir);
        printf("%d ", raiz->info);
    }
}

int main() {
    No* raiz = NULL;
    insere_arvore(&raiz, 10);
    insere_arvore(&raiz, 5);
    insere_arvore(&raiz, 15);
    insere_arvore(&raiz, 2);
    insere_arvore(&raiz, 7);

    printf("Exibição em pré-ordem: ");
    exibe_pre_ordem(raiz);
    printf("\n");

    printf("Exibição em ordem simétrica (in-order): ");
    exibe_in_ordem(raiz);
    printf("\n");

    printf("Exibição em pós-ordem: ");
    exibe_pos_ordem(raiz);
    printf("\n");

    raiz = remove_arvore(raiz, 10);

    printf("Após remover o elemento 10:\n");
    printf("Exibição em ordem simétrica (in-order): ");
    exibe_in_ordem(raiz);
    printf("\n");

    return 0;
}
