#ifndef _pilha_c_
#define _pilha_c_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"
#define  TAM 10 //tamanho de elementos que pode ter na pilha definida

struct elemento{//struct que representa os elementos da pilha
    int info;
    struct elemento* prox;
};

struct pilha{//pilha que contém os elementos
    struct elemento* topo;
    int tamanho;
};


Elemento* cria_elemento(int info){//função para criar um elemento
    Elemento* e = (Elemento*) malloc(sizeof(Elemento));//alocação de memória
    if(!e)//verifica se a alocação deu certo
        return NULL;
    e->info = info;//recebimento da informação
    e->prox = NULL;//prox aponta para null
    return e;
}

Pilha* cria_pilha(){//criação de pilha
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    if(!p)
        return NULL;
    p->topo = NULL;//inicialmente o topo aponta para null
    p->tamanho = 0;//tamanho da pilha zerado
    return p;
}

bool pilha_vazia(Pilha* p){//função que verifica se a pilha está vazia
    if(!p)
        return false;
    return (p->tamanho == 0);//verifica se o tamanho é igual a zero e retorna o valor booleano
}

bool pilha_cheia(Pilha* p){//verifica se a pilha está cheia
    if(!p)
        return false;
    return (p->tamanho == TAM);//verifica se o tamanho da pilha é igual ao tamanho estabelecida e retorna o valor booelano
}

bool push(Pilha* p, int info){//função para inserir elementos na pilha(push)
    if(!p)
        return false;
    if(pilha_cheia(p)){//verifica se a pilha já está cheia
        printf("Pilha cheia\n");
        return false;
    }       
    
    Elemento* e = cria_elemento(info);//cria o novo elemento
    if(!e)
        return false;

    e->prox = p->topo;//o proximo do novo elemento sempre é o topo
    p->topo = e;//e o topo recebe o novo elemento adicionado
    p->tamanho+=1;//incremento do tamanho da pilha     
    return true;
}

bool pop(Pilha* p){//função que remove um elemento da pilha(pop)
    if(!p)
        return false;
    if(pilha_vazia(p))//verifica se a pilha está vazia
        return false;
    Elemento* aux = p->topo;//elemento auxiliar para armazenar o antigo topo
    p->topo = p->topo->prox;//o novo topo será o próximo elemento abaixo do topo
    free(aux);//liberação do antigo topo
    return true;
}

void libera_pilha(Pilha** p){//função que esvazia a pilha
    if(!(*p))
        return;

    Elemento* aux = (*p)->topo;
    while((*p)->topo != NULL){
        pop(*p);
    }
    free(*p);
    *p = NULL;
}

void imprime_pilha(Pilha* p){//função para imprimir os elementos da pilha
    if(!p)
        return;
    Elemento* aux = p->topo;//nó auxiliar para percorrer a pilha
    printf("\n");
    while(aux != NULL){
        printf("%d \n", aux->info);//exibição dos elementos
        aux = aux->prox;
    }
    printf("\n");
}

int topo(Pilha* p){//função que retorna o topo da pilha
    if(!p)
        return -1;
    if(pilha_vazia(p))//verifica se a pilha está vazia
        return -1;
    
    return p->topo->info;    
}

void concatena_pilhas(Pilha* p1, Pilha* p2){//função que une a segunda pilha com a primeira, o topo da segunda pilha se torna o topo da primeira pilha
    if(!p1 || !p2)
        return;
    if(pilha_vazia(p2))//verifica se a segunda pilha está vazia
        return;
    Elemento* aux = p2->topo;//nó auxiliar para percorrer a segunda pilha
    while(aux->prox != NULL)
        aux = aux->prox;//chega até o fim da segunda lista
    aux->prox = p1->topo;//o fim da segunda pilha aponta para o topo da primeira pilha
    p1->topo = p2->topo;//o novo topo da primeira pilha é o topo da segunda pilha
    p2->topo = NULL;//esvaziamento da segunda pilha

    p1->tamanho += p2->tamanho;//incremento do tamanho da pilha 1
    p2->tamanho = 0;
}

Pilha* copia_pilha(Pilha* p){//função que faz a cópia de uma pilha
    if(!p)
        return NULL;
    Pilha* p_aux = cria_pilha();//cria uma pilha auxiliar para copiar a pilha original na ordem inversa
    Elemento* aux = p->topo;//nó auxiliar para percorrer a pilha original
    while(aux != NULL){
        push(p_aux, aux->info);//inserção dos elementos na pilha auxiliar, o topo da pilha original será o último elemento da pilha auxiliar e assim por diante
        aux = aux->prox;
    }
    Pilha* p_copia = cria_pilha();//pilha cópia
    aux = p_aux->topo;//o nó auxiliar será usado para percorrer a pilha auxiliar e retomar a ordem da pilha original
    while(aux != NULL){
        push(p_copia, aux->info);//adição dos elementos na pilha cópia, o topo da pilha auxiliar será o último elemento da pilha cópia e assim por diante. Assim, mantém a ordem da pilha original
        aux = aux->prox;
    }
    libera_pilha(&p_aux);//liberação da pilha auxiliar
    return p_copia;
}

#endif