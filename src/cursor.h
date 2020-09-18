#include "linha.h"

#define ANTE -1
#define PROX 1

struct cursor{
    linha **aLinha;
    carac **aCarac;
};
typedef struct cursor cursor;

cursor* newCursor(linha**, carac**);
void moveCarac(cursor**, int);
void moveLinha(cursor**, int);

cursor *newCursor(linha **l, carac **c){
    cursor *cu = (cursor*)malloc(sizeof(cursor));
    cu->aLinha = l;
    cu->aCarac = c;

    return cu;
}

void moveCarac(cursor **cu, int modo){
    switch (modo) {
        case PROX:
            if((*(*cu)->aCarac)->prox != NULL)
                (*cu)->aCarac = &((*(*cu)->aCarac)->prox);
            
            else{
                if((*(*cu)->aLinha)->prox != NULL){
                    (*cu)->aLinha = &((*(*cu)->aLinha)->prox);
                    (*cu)->aCarac = &((*(*cu)->aLinha)->caracs);
                }
            }
        break;
        case ANTE:
            if((*(*cu)->aCarac)->ant != NULL)
                (*cu)->aCarac = &((*(*cu)->aCarac)->ant);
            
            else{
                if((*(*cu)->aLinha)->ant != NULL){
                    (*cu)->aLinha = &((*(*cu)->aLinha)->ant);
                    (*cu)->aCarac = &(*(*cu)->aLinha)->caracs;

                    while((*(*cu)->aCarac)->prox != NULL)
                        (*cu)->aCarac = &(*(*cu)->aCarac)->prox;
                }
            }
        break;
    }
}

void moveLinha(cursor **cu, int modo){
    int nPosLinhaAnt = 0, i;

    while((*(*cu)->aCarac) != NULL){
        nPosLinhaAnt++;
        (*cu)->aCarac = &((*(*cu)->aCarac)->ant);;
    }

    switch (modo) {
        case PROX:
            if((*(*cu)->aLinha)->prox != NULL)
                (*cu)->aLinha = &((*(*cu)->aLinha)->prox);
        break;
        case ANTE:
            if((*(*cu)->aLinha)->ant != NULL)
                (*cu)->aLinha = &((*(*cu)->aLinha)->ant);
        break;
    }

    (*cu)->aCarac = &((*(*cu)->aLinha)->caracs);

    for(i = 0; i<nPosLinhaAnt; i++)
        moveCarac(cu, modo);
}