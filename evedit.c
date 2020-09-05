#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN64
#include "meuconio.h"
#else
#include "conio_linux.h"
#endif
#include "src/line.h"
#include "interface.c"

int main(){
    initconio();
    
    //frame();

    dLine* lines = newDLine();
    insertLine(&lines, CURR_LINE);
    insertChar(&lines->curr, 'a', LAST_CHAR);
    insertChar(&lines->curr, 'b', LAST_CHAR);
    insertChar(&lines->curr, 'c', LAST_CHAR);

    insertLine(&lines, NEXT_LINE);
    insertChar(&lines->last, 'd', LAST_CHAR);
    insertChar(&lines->last, 'e', LAST_CHAR);

    insertChar(&lines->first, 'f', LAST_CHAR);
    insertChar(&lines->first, 'g', LAST_CHAR);

    insertLine(&lines, NEXT_LINE);
    insertChar(&lines->curr->next, 'h', FIRST_CHAR);

    showLines(lines);


    getch();
    endwin();
    return 0;
}