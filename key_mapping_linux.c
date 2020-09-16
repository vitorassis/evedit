#include <curses.h>
void triggerKey(dLine **lines, char tecla, int **exit, int **typed){
    switch (tecla) {
        case 27:    //TECLAS ESPECIAIS LINUX
            switch (getch()) {
                case 91:    //SETAS + PG LINUX
                    switch (getch()) {
                        case 54: //PGDOWN
                            // top = (top + MAX_YCURSOR-MIN_YCURSOR < lines->size) ? top + MAX_YCURSOR-MIN_YCURSOR : top;
                            // getch();
                            // clearEditor();

                            //pgdown func
                        break;
                        case 53: //PGUP
                            // top -= top < (MAX_YCURSOR-MIN_YCURSOR) ? 0 : (MAX_YCURSOR-MIN_YCURSOR);
                            // getch();
                            // clearEditor();

                            //pgup func
                        break;
                        case 66: //SETA P BAIXO
                            setYCursor(lines, SETCUR_NEXT);
                        break;
                        case 65: //SETA P CIMA
                            setYCursor(lines, SETCUR_PREV);
                        break;
                        case 68: //SETA P ESQUERDA
                            setXCursor(lines, SETCUR_PREV);
                    }
                    **typed = 1;
                break;               
                case 79:    //FN KEYS
                    switch (getch()) {
                        case 83: // f4
                            **exit=1;
                        break;
                    }
                    
                break;             
            }
        break;
        case 10:
            insertLine(lines, NEXT_LINE);
            **typed = 1;
        break;
        case 127:
            removeChar(lines, PREV_CHAR);
            **typed = 1;
        break;
        default:
            insertChar(&((*lines)->curr), tecla, NEXT_CHAR);
            **typed = 1;
    }
}