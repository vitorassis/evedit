#include "carac.h"

struct linha{
    struct linha *ant, *prox;
    carac *caracs;
};
typedef struct linha linha;

linha *newLinha();
void addLinha(linha**);

linha *newLinha(){
    linha *l = (linha*)malloc(sizeof(linha));
    l->ant = l->prox = NULL;
    l->caracs = NULL;

    addCarac(&l->caracs, 0);

    return l;
}

void addLinha(linha **anterior){
    linha *l = newLinha();

    if((*anterior) == NULL)
        (*anterior) = l;
    else{
        if((*anterior)->prox == NULL){
            (*anterior)->prox = l;
            l->ant = (*anterior);
        }else{
            (*anterior)->prox->ant = l;
            l->prox = (*anterior)->prox;
            (*anterior)->prox = l;
            l->ant = (*anterior);
        }
    }
}

void removeLinha(linha **remover){
    linha *aux = (*remover);

    while(removeCarac(&(*remover)->caracs) != -1);

    free((*remover)->caracs);
    (*remover)->caracs = NULL;

    if((*remover)->prox == NULL && (*remover)->ant == NULL){
        (*remover) = NULL;
        addLinha(remover);
    }else{
        if((*remover)->prox == NULL)
            (*remover)->ant->prox = NULL;
        else{
            if((*remover)->ant == NULL){
                (*remover)->prox->ant = NULL;
                (*remover) = (*remover)->prox;
            }else{
                (*remover)->ant->prox = (*remover)->prox;
                (*remover)->prox->ant = (*remover)->ant;
            }
        }
    }
    free(aux);
}

void debugLinha(linha *l){
    debugCarac(l->caracs);
    if(l->prox != NULL){    
        printf("\n");
        debugLinha(l->prox);
    }
}