#include <stdio.h>
#include <stdlib.h>
#include "src/cursor.h"

int main(){
    linha *linhas = newLinha();
    cursor *atual;
    addLinha(&linhas);

    atual = newCursor(&linhas, &linhas->caracs);

    addCarac(atual->aCarac, 'a');
    moveCarac(&atual, PROX);
    addCarac(atual->aCarac, 'c');
    moveCarac(&atual, PROX);
    addCarac(atual->aCarac, 'b');

    addLinha(atual->aLinha);
    moveLinha(&atual, PROX);
    addCarac(atual->aCarac, 'd');

    addLinha(atual->aLinha);
    moveLinha(&atual, PROX);
    addCarac(atual->aCarac, 'e');
    moveCarac(&atual, ANTE);
    addCarac(atual->aCarac, 'f');

    showLinha(linhas);

    return 0;
}