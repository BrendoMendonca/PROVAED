#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct elemento{
    int info;
    struct elemento* ant;
    struct elemento* prox;
};

struct fila{
    struct elemento* inicio;
    struct elemento* fim;
};

typedef struct elemento Elemento;
typedef struct fila Fila;

Elemento* cria_no(int info){
    Elemento* no = (Elemento*) malloc(sizeof(Elemento));
    if(!no)
        return NULL;
    no->info = info;
    no->ant = NULL;
    no->prox = NULL;
    return no;
}

Fila* cria_fila(){
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if(!f)
        return NULL;
    f->fim = NULL;
    f->inicio = NULL;
    return f;
}

bool insere_fila(Fila* f, int info){
    if(!f)
        return false;
    Elemento* no = cria_no(info);
    if(f->inicio == NULL){
        f->inicio = no;
        f->fim = no;
        return true;
    }
    f->fim->prox = no;
    no->ant = f->fim;
    f->fim = no;    
    
    return true;
}

bool retira_fila(Fila* f){
    if(!f || f->fim == NULL)
        return false;
    if(f->fim == f->inicio){
        f->inicio = NULL;
        f->fim = NULL;
        return true;
    }
    
    Elemento* aux = f->inicio;
    f->inicio = aux->prox;
    f->inicio->ant = NULL;
    free(aux);
    return true;
    
}

void combina_filas (Fila* f_res, Fila* f1 , Fila* f2 ){
    if(!f1 || !f2 || !f_res)
        return;
    Elemento* aux1 = f1->fim;
    Elemento* aux2 = f2->fim;
    while(aux1 != NULL && aux2 != NULL){
        if(aux1 != NULL){
            insere_fila(f_res, aux1->info);
            aux1 = aux1->prox;
        }
        if(aux2 != NULL){
            insere_fila(f_res, aux2->info);
            aux2 = aux2->prox;
        }
    }
}