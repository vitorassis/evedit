//#include <curses.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__ 
    #include "conio_linux.h"
#elif _WIN32
    #include "conio_win.h"
#endif

#include "src/line.h"
#include "interface.c"

int main(){
    int top=0;
    char tecla;
    dLine* lines;
    int mode;
    int exit = 0;
    int *curX, *curY;
    int typed = 0;

    curX = (int*)malloc(sizeof(int));
    curY = (int*)malloc(sizeof(int));

    *curX = MIN_XCURSOR;
    *curY = MIN_YCURSOR;

    initconio();
    
    frame();

    lines = newDLine();
    insertLine(&lines, FIRST_LINE);

    do{
        showEditor(lines, top, &curX, &curY, typed);
        tecla = getch();
        switch (tecla) {
            case 27:    //TECLAS ESPECIAIS LINUX
                switch (getch()) {
                    case 91:    //SETAS + PG LINUX
                        switch (getch()) {
                            case 54: //PGDOWN
                                top = (top + MAX_YCURSOR-MIN_YCURSOR < lines->size) ? top + MAX_YCURSOR-MIN_YCURSOR : top;
                                getch();
                                clearEditor();
                            break;
                            case 53: //PGUP
                                top -= top < (MAX_YCURSOR-MIN_YCURSOR) ? 0 : (MAX_YCURSOR-MIN_YCURSOR);
                                getch();
                                clearEditor();
                            break;
                            case 66: //SETA P BAIXO
                                (*curY)++;
                                if(*curY >= MAX_YCURSOR){   
                                    top += (top+1 <= lines->size);
                                    (*curY) = MAX_YCURSOR-1;
                                    clearEditor();
                                
                                }
                            break;
                            case 65: //SETA P CIMA
                                (*curY)--;
                                if((*curY) <= MIN_YCURSOR){
                                    top -= (top-1 >= 0);
                                    (*curY) = MIN_YCURSOR;
                                    clearEditor();
                                }
                            break;
                        }
                        typed = 0;
                    break;               
                    case 79:    //FN KEYS
                        switch (getch()) {
                            case 83:
                                exit=1;
                            break;
                        }
                        
                    break;             
                }
                typed = 0;
            break;
            case 13:
            case 10:
                insertLine(&lines, NEXT_LINE);
                typed = 1;
            break;
            case 127:
            case 8:
                removeChar(&lines, CURR_CHAR);
                typed = 1;
            break;
            default:
                insertChar(&lines->curr, tecla, NEXT_CHAR);
                typed = 1;
        }
    }while(!exit);

    endwin();
    return 0;
}
