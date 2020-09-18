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
        (*anterior)->prox = l;
        l->ant = (*anterior);
    }
}

void showLinha(linha *l){
    showCarac(l->caracs);
    if(l->prox != NULL){    
        printf("\n");
        showLinha(l->prox);
    }
}