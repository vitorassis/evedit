#include <curses.h>
#ifdef __linux__ 
    #include "conio_linux.h"
#elif _WIN32
    #include "conio_win.h"
#endif

#define WIDTH 81
#define HEIGTH 24
#define FRAME "#"

#define SETCUR_PREV -1
#define SETCUR_NEXT 1

#define MIN_XCURSOR 2
#define MAX_XCURSOR WIDTH-2

#define MIN_YCURSOR 4
#define MAX_YCURSOR HEIGTH-2


void frame(){
    int i=1;

    textcolor(4);
    gotoxy(38, 2);printw("evedit v"); printw(VERSION)
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
    printw("F4 - Fechar   ");
    printw("F1 - Abrir   ");
    printw("F2 - Salvar   ");
    printw("F3 - Procurar");
    textcolor(15);
}


void showEditor(dLine *lines, int typed){
    // line* currentLine;
    // charac* currentChar;
    // int lastX, x=lastX=MIN_XCURSOR;
    // int lastY, y=lastY=MIN_YCURSOR;
    // int curX = x, curY = y;

    // currentLine = lines->curr;
    // currentChar = lines->curr->chars->curr;

    // lines->curr = lines->first;
    // lines->curr->chars->curr = lines->curr->chars->first;

    // lines->curr->chars->curr = lines->curr->chars->first;

    // for(y=MIN_YCURSOR; y<MAX_YCURSOR; y++){
    //     if(lines->curr != NULL){
    //         for(x=MIN_XCURSOR; x<MAX_XCURSOR; x++){
    //             if(lines->curr->chars->curr != NULL){
    //                 if(typed && currentLine == lines->curr && currentChar == lines->curr->chars->curr){                             
    //                     curX = x+1; 
    //                     curY = y;
    //                 }
    //                 gotoxy(x, y);printw("%c", lines->curr->chars->curr->value);
    //                 lastX = x;
    //                 lastY = y;
    //                 if(lines->curr->chars->curr->next != NULL)
    //                     lines->curr->chars->curr = lines->curr->chars->curr->next;
    //                 else 
    //                    x = MAX_XCURSOR;
    //             }else {
    //                 gotoxy(x, y);printw(" ");
    //             }
    //         }
    //         if(lines->curr->chars->curr == NULL || lines->curr->chars->curr->next == NULL){
    //             if(lines->curr->next != NULL){
    //                 lines->curr = lines->curr->next;
    //                 lines->curr->chars->curr = lines->curr->chars->first;
    //             }else
    //                 y = MAX_YCURSOR;
    //         }
    //     }
    //     else
    //         y = MAX_YCURSOR;
    // }
    // for(y = lastY; y < MAX_YCURSOR && y < lastY+1; y++)
    //     for(x = y==lastY ? lastX+1 : MIN_XCURSOR; x < MAX_XCURSOR; x++){
    //         gotoxy(x,y);printw(" ");
    //     }

    // gotoxy(curX, curY);

    // lines->curr = currentLine;
    // lines->curr->chars->curr = currentChar;

    lines->aCurr = lines->curr;
    lines->aCurr->chars->aCurr = lines->curr->chars->curr;
    int lastX, x=lastX=MIN_XCURSOR;
    int lastY, y=lastY=MIN_YCURSOR;
    int curX = x, curY = y;

    lines->curr = lines->first;
    lines->curr->chars->curr = lines->curr->chars->first;


    for(y=MIN_YCURSOR; y<MAX_YCURSOR; y++){
        if(lines->curr != NULL){
            for(x=MIN_XCURSOR; x<MAX_XCURSOR; x++){
                if(lines->curr->chars->curr != NULL){
                    if(typed && lines->aCurr->chars->aCurr == lines->curr->chars->curr){                             
                        curX = x; 
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
    for(y = lastY; y < MAX_YCURSOR && y < lastY+1; y++)
        for(x = y==lastY ? lastX : MIN_XCURSOR; x < MAX_XCURSOR; x++){
            gotoxy(x,y);printw(" ");
        }
    

    gotoxy(curX, curY);

    lines->curr = lines->aCurr;
    lines->curr->chars->curr = lines->aCurr->chars->aCurr;

}

void clearEditor(){
    int x, y;

    for(x=MIN_XCURSOR; x<MAX_XCURSOR; x++){
        for(y=MIN_YCURSOR; y<MAX_YCURSOR; y++){
            gotoxy(x, y);printw(" ");
        }
    }
}

void setXCursor(dLine **lines, int mode){
    switch (mode) {
        case SETCUR_PREV:
            if(!isDCharacEmpty((*lines)->curr->chars) && 
            (*lines)->curr->chars->curr != NULL){
                (*lines)->curr->chars->curr = (*lines)->curr->chars->curr->prev;
            }else
                if((*lines)->curr->prev != NULL){
                    (*lines)->curr = (*lines)->curr->prev;
                    (*lines)->curr->chars->curr = (*lines)->curr->chars->last;
                }
        break;
        case SETCUR_NEXT:
        break;
    }

    gotoxy(25,22);printw("Curr: %10u", (*lines)->curr->chars->curr);
}

void setYCursor(dLine **lines, int mode){

}