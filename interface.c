#include <curses.h>
#ifdef __linux__ 
    #include "conio_linux.h"
#elif _WIN32
    #include "conio_win.h"
#endif

#define WIDTH 80
#define HEIGHT 24
#define MIN_X 2
#define MAX_X WIDTH-2
#define MIN_Y 4
#define MAX_Y HEIGHT-3

void showFileName(char fileName[]){
    int xInicio = WIDTH;

    xInicio -= strlen(fileName);

    textcolor(5);
    gotoxy(xInicio, 2);printw("%s", fileName);
    textcolor(7);
}

void frame(){
    int x, y;

    textbackground(4);

    for (x = 1; x <= WIDTH; x++) {
        gotoxy(x, 1);printw(" ");
        gotoxy(x, 3);printw(" ");
        gotoxy(x, HEIGHT-2);printw(" ");
        gotoxy(x, HEIGHT);printw(" ");
    }

    for (y = 1; y <= HEIGHT; y++) {
        gotoxy(1, y);printw(" ");
        gotoxy(WIDTH, y);printw(" ");
    }

    textbackground(0);

    textcolor(10);
    gotoxy(2, 2);printw("evedit ");printw(VERSION);
    showFileName("Sem_Titulo");
}

void menuInicial(){
    textcolor(9);

    gotoxy(MIN_X, HEIGHT-1);
    printw("F1- Abrir   ");
    printw("F2- Procurar   ");
    printw("F3- Salvar   ");
    printw("F4- Fechar");

    textcolor(7);
}

void showEditor(linha *l, cursor *c, int topo){
    linha *_l = l;
    carac *caracter;
    int x, y, i, cx, cy;

    i=0;
    while(i++ < topo && _l->prox != NULL)
        _l = _l->prox;

    caracter = _l->caracs;
    for(y=MIN_Y; y <= MAX_Y; y++){
        if(_l != NULL){
            for(x=MIN_X; x <= MAX_X; x++){
                gotoxy(x, y);
                if(caracter != NULL){
                    if(caracter == (*c->aCarac)){
                        cx = x;
                        cy = y;
                    }
                    printw("%c", caracter->valor);
                    caracter = caracter->prox;
                }else{
                    printw(" ");
                }
            }
            if(caracter == NULL){
                if(_l->prox != NULL){
                    _l = _l->prox;
                    caracter = _l->caracs;
                }
            }
        }
    }

    gotoxy(cx, cy);
}

#ifdef __linux__ 
    #include "key_mapping_linux.c"
#elif _WIN32
    #include "key_mapping_win.c"
#endif