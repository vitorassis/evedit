#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN64
#include "conio_win.h"
#else
#include "conio_linux.h"
#endif

#include "src/line.h"
#include "interface.c"

int main(){
    char tecla;
    dLine* lines;
    int mode;

    initconio();
    
    frame();

    lines = newDLine();
    insertLine(&lines, FIRST_LINE);

    do{
        showEditor(&lines);
        tecla = getch();
        gotoxy(15, 15);printw("DEBUG: %d", tecla);
        switch (tecla) {
            case 13:
            case 10:
                insertLine(&lines, NEXT_LINE);
                break;
            case 127:
                removeChar(&lines->curr, CURR_CHAR);
                break;
            default:
                insertChar(&lines->curr, tecla, NEXT_CHAR);
        }
    }while(tecla != 27);

    getch();
    endwin();
    return 0;
}