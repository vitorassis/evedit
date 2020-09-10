#include <stdio.h>
#include <unistd.h>
#ifdef __linux__ 
    #include "conio_linux.h"
#elif _WIN32
    #include "conio_win.h"
#endif

int main(){
    int tecla;
    char ch;
    initconio();

    while((tecla = getch()) || true){
        printw("%c => %d\n", tecla, tecla);
        
        // ch = getc(stdin);
        // if (ch == EOF)
        //     printw("stdin is empty");
        // else{
        //     printw("BUFFER: %d\n", ch);
        //     // ungetc(ch, stdin);
        // }
    }
    endconio();
}