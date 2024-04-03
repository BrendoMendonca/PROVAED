#ifndef _lista_dup_c_
#define _lista_dup_c_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>   
#include "lista_dup.h"

struct nod{//elemento da lista
    int info;
    struct nod* ant;
    struct nod* prox;
};

struct listad{//lista duplamente encadeada
    struct nod* inicio;
    struct nod* fim;
};


Nod* cria_no(int info){//função que cria nó com dupla referência
    Nod* no = (Nod*) malloc(sizeof(Nod));
    if(!no)
        return NULL;
    no->ant = NULL;
    no->prox = NULL;
    no->info = info;
    return no;
}

Listad* cria_lista(){//função que cria a lista duplamente encadeada
    Listad* l = (Listad*) malloc(sizeof(Listad));
    if(!l)
        return NULL;

    l->inicio = NULL;
    l->fim = NULL;
    return l;
}

bool insere_inicio(Listad* l, int info){//função que insere o elemento no início da lista
    if(!l)
        return false;
    Nod* no = cria_no(info);//criação do novo elemento que será inserido na lista
    if(!no)
        return false;
    if(l->inicio == NULL){//verifica se a lista está vazia
        //se a lista estiver vazia, o início e o fim apontam para o novo elemento adicionado
        l->inicio = no;
        l->fim = no;
        return true;
    }
    //caso a lista já tenha elementos:
    l->inicio->ant = no;//o elemento anterior de inicio aponta para o novo nó
    no->prox = l->inicio;//o prox do novo nó aponta para o início
    l->inicio = no;//e o início recebe o novo nó, tornando assim o novo nó no início
    return true;
}

bool insere_fim(Listad* l, int info){//função que insere um elemento no fim da lista
    if(!l)
        return false;
    Nod* novo = cria_no(info);//novo nó que será inserido na lista
    if(!novo)
        return false;
    
    if(l->fim == NULL){//verifica se a lista está vazia
        l->inicio = novo;
        l->fim = novo;
        return true;
    }    
    //caso não seja vazia
    novo->ant = l->fim;//o anterior do novo elemento aponta para o fim da lista
    l->fim->prox = novo;//o prox do fim da lista aponta para o novo elemento
    l->fim = novo;//o fim recebe o novo nó, tornando assim o fim da lista
    return true;        
}

void retira_inicio(Listad* l){//função que retira um elemento do início da lista
    if(!l || l->inicio == NULL)
        return;
    if(l->inicio->prox == NULL){//verifica se só tem um elemento na lista
        l->inicio = NULL;
        l->fim = NULL;
    }
    else{//caso tenha mais de um elemento na lista
        Nod* aux = l->inicio;//nó auxiliar armazena o primeiro elemtno da lista
        l->inicio = l->inicio->prox;//o início da lista recebe o segundo elemento da lista que será o novo primeiro elemento
        l->inicio->ant = NULL;//o anterior do novo inicio recebe null
        free(aux);
    }
}

void retira_final(Listad* l){//função para retirar um elemento no final da lista
    if(!l || l->inicio == NULL)
        return;
    if(l->inicio == l->fim){//verifica se só tem um elemento na fila
        l->inicio = NULL;
        l->fim = NULL;
    }
    else{
        Nod* aux = l->fim;//nó auxiliar para armazenar a referência do último elemento        
        l->fim = l->fim->ant;//o último elemento aponta para seu anterior e assim fazendo o novo fim
        l->fim->prox = NULL;//o prox do último elemento recebe NULL
        free(aux);
    }
}

void imprime_lista_dup(Listad* l){
    if(!l)
        return;
    Nod* aux = l->inicio;
    printf("\n");
    while(aux != NULL){
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");

}

#endif