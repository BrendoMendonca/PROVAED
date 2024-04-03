/*Funções usando lista encadeada*/
#ifndef _lista_c_
#define _lista_c_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>   
#include "lista.h"

struct no{ //estrutura de tipo nó representando os elementos da lista
    int info;//inteiro que contém a informação guardada do nó
    struct no* prox;//ponteiro do tipo nó que aponta para o próximo nó
};

struct lista{//estrutura de tipo lista que armazena os elementos(nós)
    struct no* inicio;//ponteiro do tipo nó que sempre aponta para o primeiro elemento da lista
};


No* cria_no(int info){//função para criar nós
    No* n = (No*) malloc(sizeof(No));//alocação dinamica do nó
    if(!n)//verifica se foi alocado
        return NULL;
    n->info = info;//recebimento da informação de acordo com o parâmetro passado
    n->prox = NULL;//o nó aponta para NULL como próximo elemento
    return n;//retorna o nó criado
}

Lista* cria_lista(){//função para criar lista
    Lista* l = (Lista*) malloc(sizeof(Lista));//alocação dinâmica da lista
    if(!l)//verifica se foi alocado
        return NULL;
    l->inicio = NULL;//l->inicio é o primeiro nó da lista e inicialmente está vazio(NULL)
    return l;
}

bool insere_inicio(Lista* l, int info){//função para inserir nó no início da lista
    if(!l)//verifica se a lista é válida
        return NULL;
    No* n = cria_no(info);//criação de um novo nó para ser adicionado à lista
    if(!n)
        return NULL;
    //o nó n será o novo primeiro elemento, então o próximo dele será o antigo primeiro elemento
    n->prox = l->inicio;
    l->inicio = n;
    return true;
}

bool insere_fim(Lista* l, int info){//função para inserir nó no fim da lista
    if(!l)//verifica se a lista é válida
        return false;
    if(l->inicio == NULL)
        insere_inicio(l, info);
    else{ 

        No* aux = l->inicio;//um nó auxiliar é criado para percorrer a lista
        while(aux->prox != NULL)//o nó auxiliar percorre a lista até o próximo elemento que ele se encontra for NULL, ou seja, até chegar até o último elemento da lista
            aux = aux->prox;
        
        aux->prox = cria_no(info);//quando o nó auxiliar chega no último elemento da lista, o próx dele aponta para um novo nó que será o novo último nó da lista
        return(aux->prox != NULL);
    }
}

bool remove_inicio(Lista* l){//função para remover nó no início da lista
    if(!l)//verifica se a lista passada como parâmetro é válida
        return NULL;
    if(l->inicio == NULL)//verifica se a lista está vazia
        return false;
    No* aux = l->inicio->prox; //nó auxiliar para armazenar o elemento que será o novo início da lista
    free(l->inicio);//libera o antigo primeiro elemento da lista
    l->inicio = aux;//o primeiro elemento da lista recebe os dados do antigo segundo elemento da lista
    return true;
}

bool remove_fim(Lista *l){//função para remover o nó no fim da lista
    if(!l)//verifica se a lista passada como parâmetro é válida
        return false;
    if(l->inicio == NULL)//verifica se a lista está vazia
        return false;
    if(l->inicio->prox == NULL)//verifica se só tem um elemento na lista
        return false;
    No* aux = l->inicio;//nó auxiliar criado para percorrer a lista
    while(aux->prox->prox != NULL)//o nó auxiliar percorre a lista até o penúltimo elemento da lista
        aux = aux->prox;
    free(aux->prox);//remove o último elemento da lista
    aux->prox = NULL;//o antipenúltimo elemento aponta para NULL, o tornando o novo último elemento da lista
    return true;
}

No* busca_no(Lista* l, int info){//função que retorna um nó específico de acordo com a informação contida no nó
    if(!l)//verifica se a lista é válida
        return NULL;
    No* aux = l->inicio;//nó auxiliar para percorrer a lista
    while(aux != NULL)//percorre a lista até o fim ou até o elemento ser encontrado
        if(aux->info == info)//se o valor do nó corresponder com o valor do parâmetro, o nó é retornado
            return aux;
        aux = aux->prox;
    return NULL;//caso contrário, NULL é retornado
}

void imprime_lista(Lista* l){//função para imprimir a lista
    if(!l)//verifica se a lista é válida
        return;
    No* aux = l->inicio;//nó auxiliar para percorrer a lista
    while(aux != NULL){//o nó auxiliar percorre a lista até o fim imprimindo cada elemento
        printf("%d ", aux->info);
        aux = aux->prox;
    }
}


bool modifica_info(Lista* l, int info, int nova_info){//função para modificar a informação de um nó
    No* aux = busca_no(l, info);//nó auxiliar recebe o retorno da função de busca, ou seja, recebe o nó que possui o valor que será alterado
    if(aux == NULL)
        return false;
    aux->info = nova_info;//atribuição da nova informação ao nó
    return true;
}

void libera_lista(Lista** l){//função para liberar a lista da memória
    if(!(*l))//verifica se a lista é válida
        return;
    while((*l)->inicio != NULL)//percorre a lista até o fim para eliminar todo os nós
        remove_inicio(*l);//função de remoção no início
    free(*l);
    *l = NULL;
}
int ultimo(Lista* l){//função que retorna o último elemento da lista
    if(!l)//verifica se a lista é válida
        return -1;
    No* aux = l->inicio;//nó auxiliar para percorrer a lista
    while(aux->prox != NULL){//percorre a lista até o último elemento
        aux = aux->prox;
    }
    return aux->info;//retorno do último elemento
}

int comprimento(Lista* l){//função que retorna a quantidade de elementos na lista
    if(!l)
        return -1;
    int tamanho = 0;//variável que irá calcular a quantidade de elementos
    No* aux = l->inicio;//nó auxiliar para percorrer a lista
    while (aux != NULL){//percorre toda a lista
        tamanho++;//incremento da quantidade de elementos
        aux = aux->prox;
    }
    return tamanho;//retorno da quantidade de elementos da lista
 }

int maiores (Lista* l, int x){//função que retorna a quantidade de elementos maiores que o parâmentro "x"
    if(!l)
        return -1;
    int quant_maiores = 0;//variável que armazena a quantidade de maiores
    No* aux = l->inicio;//nó auxiliar para percorrer a lista
    while (aux != NULL){
        if(aux->info > x)//verifica se o elemento da lista é maior que o parêmentro
            quant_maiores++;//incremento da quantidade de elementos
        aux = aux->prox;
    return quant_maiores;
    }
 }

void concatena(Lista* l1, Lista* l2){//função que concatena a segunda lista ao final da primeira e esvazia a segunda
    if(!l1 || !l2)//verifica se as listas são válidas
        return;
    if(l2->inicio == NULL)//verifica se a segunda lista está vazia
        return;
    No* aux = l1->inicio;//nó auxiliar para percorrer a primeira lista
    if(aux == NULL)//verifica se a primeira lista está vazia
        l1->inicio = l2->inicio;//se estiver vazia, o início da segunda lista se torna o início da primeira lista
    else{
        while(aux->prox != NULL)//percorre a lista até o último elemento da primeira lista
            aux = aux->prox;
        aux->prox = l2->inicio;//o próximo do último elemento aponta para o início da segunda lista  e assim as listas são concatenadas
    }
    //esvazia a segunda lista
    l2->inicio = NULL;
    libera_lista(&l2);
 }

void retira_n (Lista* l, int x){//função para retirar um elemento "x" da lista
    if(!l || !l->inicio)//verifica se a lista é válida
        return;
    No* aux = l->inicio;//nó auxiliar para percorrer a lista
    No* aux2 = NULL;//nó auxiliar que armazena o elemento removido da lista
    while(aux->prox != NULL){
        if(aux == l->inicio && aux->info == x)//caso o primeiro elemento da lista seja igual a "x"
            remove_inicio(l);

        else if(aux->prox->info == x){//verifica o conteúdo do próximo elemento
            aux2 = aux->prox;//aux2 aponta para o elemento que será removido
            aux->prox = aux2->prox;//o próximo de aux aponta para o elemento posterior do nó que será removido
            free(aux2);//libera o nó removido
        }
        aux = aux->prox;//incremento de aux
    }   
 }

Lista* separa(Lista* l, int x){//função que cria outra lista a partir da lista passada como parâmetro e do inteiro que será o início da nova lista
    if(!l)//verifica se a lista é válida
        return NULL;
    Lista* l2 = cria_lista();//criação da nova lista
    No* aux = l->inicio;//nó auxiliar para percorrer a lista
    No* aux2 = NULL;//segundo nó auxilar para determinar o ponto de separação
    while(aux != NULL && aux->info != x){//percorre a lista até encontrar o elemento que dá inicio à nova lista ou até a lista original acabar
        aux2 = aux;//enquanto não encontrar o elemento, aux2 recebe uma cópia de aux
        aux = aux->prox;//incremento da posição de aux
    }
    if(aux2 != NULL)
        aux2->prox = NULL;//finaliza a lista original apontando seu novo último elemento para null
    l2->inicio = aux;//o início da segunda lista será o prox do último elemento da lista original que foi dividida
    return l2;
 }

Lista* merge(Lista* l1, Lista* l2){//função que une duas listas
    if(!l1 || !l2)//verifica se as  duas listas são válidas
        return NULL;
    Lista* l3 = cria_lista();//criação da lista que será a união das duas passadas como parâmetro
    No* aux1 = l1->inicio;//nó axiliar para percorrer a lista 1
    No* aux2 = l2 ->inicio;//nó axiliar para percorrer a lista 1
    while(aux1 != NULL || aux2 != NULL){
        
        if(aux1 != NULL){//verifica se aux1 já chegou ao fim da lista
            if(l3->inicio == NULL)//caso ainda não tenha elemento na lista l3
                insere_inicio(l3, aux1->info);
            else{
                insere_fim(l3, aux1->info);
            }
            aux1 = aux1->prox;
        }

        if(aux2 != NULL){//verifica se aux2 já chegou ao fim da lista
            if(l3->inicio == NULL)//caso ainda não tenha elemento na lista l3
                insere_inicio(l3, aux2->info);
            else{
                insere_fim(l3, aux2->info);
            }            
            aux2 = aux2->prox;
        }
    }
    //liberação das listas originais
    l1->inicio = NULL;
    libera_lista(&l1);
    l2->inicio = NULL;
    libera_lista(&l2);
    return l3;
 }

void inverte(Lista* l){//função que inverte a ordem de uma lista
    if(!l)
        return;
    No* aux = l->inicio;//nó auxiliar para percorrer a lista
    No* anterior = NULL;//nó para armazenar o nó anterior de aux
    No* sucessor = NULL;//nó para guardar o nó sucessor de aux, pois o prox será usado para apontar o elemento anterior de aux e assim inverter a ordem

    while(aux != NULL){

        sucessor = aux->prox;//recebe o elemento sucessor de aux
        aux->prox = anterior;//o prox passa a fazer referencia ao elemento anterior de aux
        anterior = aux;//atualização do novo anterior de aux
        aux = sucessor;//atualização de aux para a próxima posição
    }
    //no final do loop aux armazena o último elemento da lista, que passará a ser o primeiro elemento
    l->inicio = anterior;//o início da lista agora é o último elemento
}

Lista* copia(Lista* l){//função que copia uma lista e retorna a lista copiada
    if(!l)
        return NULL;
    Lista* l2 = cria_lista();//lista que receberá os elementos copiados
    No* aux = l->inicio;//nó auxiliar para percorrer a lista original

    while(aux != NULL){
        insere_fim(l2, aux->info);//para cada elemento percorrido na lista original, esse mesmo elemento é inserido no final da lista cópia
        aux = aux->prox;        
    }
    return l2;
}

void para_circular (Lista* l){//função que transforma uma lista simples em uma lista circular
    if (!l)
        return;
    No* aux = l->inicio;//nó auxiliar para percorrer a lista
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = l->inicio;//faz o último elemento da lista apontar para o primeiro elemento da lista, fazendo assim uma lista circular
}

void imprime_circular(Lista* l){//função para imprimir a lista circular
    if(!l)
        return;
    No* aux = l->inicio;//nó auxiliar para percorrer a lista
    do{
        printf("%d ", aux->info);//print do conteúdo
        aux = aux->prox;//incrementeo de aux para a próxima posição
    } while (aux != l->inicio);//imprime até que aux seja igual ao início novamente
    
}
#endif
