#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define _TAM_ 40

struct elemento{
    int info;
    struct elemento* prox;
};

struct fila{
    struct elemento* fim;
};

typedef struct elemento Elemento;
typedef struct fila Fila;

Elemento* cria_no(int info){
    Elemento* no = (Elemento*) malloc(sizeof(Elemento));
    if(!no)
        return NULL;
    no->info = info;
    no->prox = NULL;
    return no;
}

Fila* cria_fila(){
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if(!f)
        return NULL;
    f->fim = NULL;
    return f;
}

bool insere_fila(Fila* f, int info){
    if(!f)
        return false;
    Elemento* no = cria_no(info);
    if(f->fim == NULL)    {
        f->fim = no;
        return true;
    }
    no->prox = f->fim;
    f->fim = no;
    return true;
}

bool retira_fila(Fila* f){
    if(!f || f->fim == NULL)
        return false;
    Elemento* aux = f->fim;
    while(aux->prox->prox != NULL)
        aux = aux->prox;
    Elemento* aux2 = aux->prox;
    aux->prox = NULL;
    free(aux2);
    return true;   
    
}
