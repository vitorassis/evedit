#include <stdio.h>
struct carac{
    struct carac *ant, *prox;
    char valor;
};
typedef struct carac carac;

carac *newCarac();
void addCarac(carac**, char);

carac *newCarac(){
    carac *c = (carac*)malloc(sizeof(carac));
    c->ant = c->prox = NULL;
    c->valor = 0;

    return c;
}

void addCarac(carac **anterior, char valor){
    carac *novo = newCarac();
    novo->valor = valor;

    if((*anterior) == NULL) //PRIMEIRO (SENTINELA)
        (*anterior) = novo;
    else{
        if((*anterior)->valor == 0){ //PRIMEIRO NÃO-SENTINELA
            (*anterior)->ant = novo;
            novo->prox = (*anterior);
            (*anterior) = novo;
        // }else if((*anterior)->prox->valor == 0){
        //     (*anterior)->prox = novo;
        //     novo->ant = (*anterior);
        }else{
            (*anterior)->prox->ant = novo;
            novo->prox = (*anterior)->prox;
            (*anterior)->prox = novo;
            novo->ant = *anterior;
        }
    }
}

void showCarac(carac *c){
    printf("%c", c->valor);
    if(c->valor != 0)
        showCarac(c->prox);
}