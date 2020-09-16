#include <stdio.h>
#include <stdlib.h>

#include "src/file.h"
#define VERSION "2.0"
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
    int *typed;

    exit = (int*)malloc(sizeof(int));
    typed = (int*)malloc(sizeof(int));

    initconio();
    
    frame();

    file* f = newFile();

    do{
        triggerKey(&lines, getch(), &exit, &typed);

        showEditor(lines, *typed);
        
    }while(!*exit);

    endwin();
    return 0;
}
