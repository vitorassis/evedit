#define VERSION "3.0"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/cursor.h"
#include "interface.c"

int main(){
    linha *linhas = newLinha();
    cursor *atual;
    int *exit = (int*)malloc(sizeof(int)), *topo =(int*)malloc(sizeof(int));
    addLinha(&linhas);
  //  topo=0;

    atual = newCursor(&linhas, &linhas->caracs);

    initconio();
    frame();
    menuInicial();

    do{
        showEditor(linhas, atual, *topo);
        triggerKey(&linhas, &atual, &exit, &topo);
    }while(!*exit);

    getch();
    endconio();

    return 0;
}