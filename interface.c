#include <curses.h>
#define WIDTH 81
#define HEIGTH 24
#define FRAME "#"


#define MIN_XCURSOR 2
#define MAX_XCURSOR WIDTH-2

#define MIN_YCURSOR 4
#define MAX_YCURSOR HEIGTH-2


void frame(){
    int i=1;

    textcolor(4);
    gotoxy(38, 2);printw("evedit");
    textcolor(10);

    for(i; i<WIDTH; i++){
        gotoxy(i, 1);printw(FRAME);
        gotoxy(i, 3);printw(FRAME);
        gotoxy(i, HEIGTH);printw(FRAME);
    }

    for(i=1; i<HEIGTH; i++){
        gotoxy(1, i);printw(FRAME);
        gotoxy(WIDTH-1, i);printw(FRAME);
    }

    textcolor(9);
    gotoxy(5, HEIGTH-1);
    printw("ESC - Fechar   ");
    printw("F1 - Abrir   ");
    printw("F2 - Salvar   ");
    printw("F3 - Procurar");
    textcolor(15);
}


void showEditor(dLine *lines, int top){
    line* currentLine;
    charac* currentChar;
    int lastX, x=lastX=MIN_XCURSOR;
    int lastY, y=lastY=MIN_YCURSOR;
    int curX=x, curY=y;
    
    int i=0;
    while(i<lines->size  && i++ < top) 
        lines->curr = lines->curr->next;

    currentLine = lines->curr;
    currentChar = lines->curr->chars->curr;

    lines->curr = lines->first;
    lines->curr->chars->curr = lines->curr->chars->first;

    for(y=MIN_YCURSOR; y<MAX_YCURSOR; y++){
        if(lines->curr != NULL){
            for(x=MIN_XCURSOR; x<MAX_XCURSOR; x++){
                if(lines->curr->chars->curr != NULL){
                    if(currentLine == lines->curr && currentChar == lines->curr->chars->curr){                             
                        curX = x+1; 
                        curY = y;
                    }
                    gotoxy(x, y);printw("%c", lines->curr->chars->curr->value);
                    lastX = x;
                    lastY = y;
                    if(lines->curr->chars->curr->next != NULL)
                        lines->curr->chars->curr = lines->curr->chars->curr->next;
                    else 
                        x = MAX_XCURSOR;
                }else {
                    gotoxy(x, y);printw(" ");
                }
            }
            if(lines->curr->chars->curr == NULL || lines->curr->chars->curr->next == NULL){
                if(lines->curr->next != NULL){
                    lines->curr = lines->curr->next;
                    lines->curr->chars->curr = lines->curr->chars->first;
                }else
                    y = MAX_YCURSOR;
            }
        }
        else
            y = MAX_YCURSOR;
    }
    if(curX == lastX+1 && curY == lastY){
        gotoxy(lastX+1, lastY);printw(" ");
    }

    gotoxy(curX, curY);
}