struct carac{
    struct carac *ant, *prox;
    char valor;
};
typedef struct carac carac;

carac *newCarac();
void addCarac(carac**, char);
int removeCarac(carac **);

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

int removeCarac(carac **remover){
    carac *aux = *remover;
    if((*remover)->valor == 0) //LINHA VAZIA
        return -1;

    if((*remover)->ant == NULL && (*remover)->prox->valor == 0) //QUANDO É O ÚNICO CARACTER DA LINHA
        (*remover) = (*remover)->prox;
    else{
        if((*remover)->prox->valor == 0)
            (*remover)->ant->prox = (*remover)->prox;
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
    return 1;
}

void debugCarac(carac *c){
    printf("%c", c->valor);
    if(c->valor != 0)
        debugCarac(c->prox);
}