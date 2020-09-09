//#include <curses.h>
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
    int top=0;
    char tecla;
    dLine* lines;
    int mode;

    initconio();
    
    frame();

    lines = newDLine();
    insertLine(&lines, FIRST_LINE);

    do{
        tecla = getch();
        switch (tecla) {
            case 13:
            case 10:
                insertLine(&lines, NEXT_LINE);
                break;
            case 127:
            case 8:
                removeChar(&lines, CURR_CHAR);
                break;
            default:
                insertChar(&lines->curr, tecla, NEXT_CHAR);
        }
        showEditor(lines, top);
    }while(tecla != 27);

    getch();
    endwin();
    return 0;
}
