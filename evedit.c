//#include <curses.h>
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>

#include "src/line.h"
#include "interface.c"

#ifdef __linux__ 
    #include "key_mapping_linux.c"
#elif _WIN32
    #include "key_mapping_win.c"
#endif

int main(){
    int top=0;
    char tecla;
    dLine* lines;
    int mode;
    int *exit;
    int *curX, *curY;
    int *typed;

    curX = (int*)malloc(sizeof(int));
    curY = (int*)malloc(sizeof(int));
    exit = (int*)malloc(sizeof(int));
    typed = (int*)malloc(sizeof(int));


    *curX = MIN_XCURSOR;
    *curY = MIN_YCURSOR;

    initconio();
    
    frame();

    lines = newDLine();
    insertLine(&lines, FIRST_LINE);

    do{
        triggerKey(&lines, getch(), &exit, &curX, &curY, &typed);

        showEditor(lines, top, &curX, &curY, *typed);
        gotoxy(40, 2);printw("Curr char_: %c", lines->curr->chars->curr->value);
    }while(!*exit);

    endwin();
    return 0;
}
