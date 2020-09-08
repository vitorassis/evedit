#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__ 
    #include "conio_linux.h"
#elif _WIN32
    #include "conio_win.h"
#else

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
        switch (tecla) {
            case 13:
            case 10:
                insertLine(&lines, NEXT_LINE);
                break;
            case 127:
                removeChar(&lines, CURR_CHAR);
                break;
            default:
                insertChar(&lines->curr, tecla, NEXT_CHAR);
        }
    }while(tecla != 27);

    getch();
    endwin();
    return 0;
}