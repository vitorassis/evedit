#include "charac.h"
//TAD line

struct line{
    struct line *prev, *next;
    charac *chars;
};
typedef struct line line;

//START dLine functions
void insertLine(dLine **lines, int mode); //AS LINHAS SEMPRE SÃO INSERIDAS VAZIAS
int removeLine(dLine **lines, int mode);
line* getLine(dLine *lines, int mode);
void moveLineTo(dLine **lines, int mode);
int isDLineEmpty(dLine *lines);
void showLines(dLine* lines);
//END dLine functions

//START line functions
line* newLine();
void insertChar(line** _line, char character, int mode);
char removeChar(dLine** lines, int mode);
void showLine(line *_line);
//END line functions


/*

====START FUNCTIONS====

*/

void insertLine(dLine **lines, int mode){
    int pos = 0;
    line *_line = newLine();
    if(isDLineEmpty(*lines))
        (*lines)->first = (*lines)->curr = (*lines)->last = _line;
    else
        switch (mode) {
            case FIRST_LINE:
                _line->next = (*lines)->first;
                (*lines)->first->prev = _line;
                (*lines)->first = _line;
                break;
            case LAST_LINE:
                _line->prev = (*lines)->last;
                _line->prev->next = _line;
                (*lines)->last = _line;
                break;
            case NEXT_LINE:
                if((*lines)->curr->next != NULL){
                    _line->next = (*lines)->curr->next;
                    (*lines)->curr->next->prev = _line;
                    _line->prev = (*lines)->curr;
                    (*lines)->curr->next = _line;
                }else{
                    _line->next = (*lines)->curr->next;
                    (*lines)->last = _line;
                    _line->prev = (*lines)->curr;
                    (*lines)->curr->next = _line;
                }
                break;
            case PREV_LINE:
                if((*lines)->curr->prev != NULL){
                    _line->prev = (*lines)->curr->prev;
                    (*lines)->curr->prev->next = _line;
                    _line->next = (*lines)->curr;
                    (*lines)->curr->prev = _line;
                }else{
                    _line->prev = (*lines)->curr->prev;
                    (*lines)->first = _line;
                    _line->next = (*lines)->curr;
                    (*lines)->curr->prev = _line;
                }
        }
    
    (*lines)->size ++;
    (*lines)->curr = _line;
    insertChar(&(*lines)->curr, 0, LAST_CHAR);
}

int removeLine(dLine **lines, int mode){
    line *aux;

    if((*lines)->size < 2)
        return 0;

    switch (mode) {
        case CURR_LINE:
            aux = (*lines)->curr;

            if(aux == (*lines)->first){
                aux->next->prev = NULL;
                (*lines)->first = (*lines)->curr = aux->next;
            }else if(aux == (*lines)->last){
                (*lines)->last = (*lines)->curr = aux->prev;
                aux->prev->next = NULL;
            }else{
                aux->prev->next = aux->next;
                (*lines)->curr = aux->next->prev = aux->prev;
            }
            break;
    }

    free(aux);
    (*lines)->size--;
    return 1;
}

line* getLine(dLine *lines, int mode){
    line *_line = NULL;

    if(!isDLineEmpty(lines))
        switch (mode) {
            case CURR_LINE:
                _line = lines->curr;
                break;
            case FIRST_LINE:
                _line = lines->first;
                break;
            case LAST_LINE:
                _line = lines->last;
                break;
            case NEXT_LINE:
                if(lines->curr->next != NULL)
                    _line = lines->curr->next;
                break;
            case PREV_LINE:
                if(lines->curr->prev != NULL)
                    _line = lines->curr->prev;
        }
    return _line;
}

void moveLineTo(dLine **lines, int mode){
    if(!isDLineEmpty(*lines))
        switch (mode) {
            case CURR_LINE:
                (*lines)->curr = (*lines)->curr;
                break;
            case FIRST_LINE:
                (*lines)->curr = (*lines)->first;
                break;
            case LAST_LINE:
                (*lines)->curr = (*lines)->last;
                break;
            case NEXT_LINE:
                if((*lines)->curr != NULL)
                    (*lines)->curr = (*lines)->curr->next;
                break;
            case PREV_LINE:
                if((*lines)->curr != NULL)
                    (*lines)->curr = (*lines)->curr->prev;
        }
}

line* newLine(){
    line* _line = (line*)malloc(sizeof(line));
    _line->prev = _line->next = NULL;
    _line->pos = 0;
    _line->chars = NULL;
    
    return _line;
}

void insertChar(line **_line, char character, int mode){
    // int pos = 0;
    // charac* _charac = newCharac();
    // _charac->value = character;

    // if(isDCharacEmpty((*_line)->chars)){
    //     (*_line)->chars->first = (*_line)->chars->curr = (*_line)->chars->last = _charac;
    // }
    // else if((*_line)->chars->size == 1){
    //     (*_line)->chars->first = _charac;
    //     (*_line)->chars->last->prev = _charac;
    //     (*_line)->chars->curr = (*_line)->chars->last;
    // }else
    //     switch (mode) {
            
    //         case LAST_CHAR:
    //             _charac->prev = (*_line)->chars->last;
    //             _charac->prev->next = _charac;
    //             (*_line)->chars->last = _charac;
    //             break;
    //         case NEXT_CHAR:
    //             if((*_line)->chars->curr == (*_line)->chars->last){     // É O ÚLTIMO
    //                 _charac->next = (*_line)->chars->last;
    //                 (*_line)->chars->last->prev->next = _charac;
    //                 _charac->prev = (*_line)->chars->last->prev->prev;
    //                 (*_line)->chars->last->prev = _charac;
                    
    //             }else{                   
    //                 if((*_line)->chars->curr == NULL){                                                        
    //                     _charac->next = (*_line)->chars->first;
    //                     (*_line)->chars->first->next->prev = _charac;
    //                     _charac->prev = NULL;
    //                     (*_line)->chars->first = _charac;
    //                 }else{
    //                     _charac->next = (*_line)->chars->curr->next;
    //                     (*_line)->chars->curr->next->prev = _charac;
    //                     _charac->prev = (*_line)->chars->curr;
    //                     (*_line)->chars->curr->next = _charac;
    //                 }
    //             }
    //             break;
    //     }
    // (*_line)->chars->size++;
    // (*_line)->chars->curr = _charac;
}

void showLines(dLine *lines){
    moveLineTo(&lines, FIRST_LINE);
    while(getLine(lines, CURR_LINE) != NULL){
        showLine(getLine(lines, CURR_LINE));
        moveLineTo(&lines, NEXT_LINE);
        printw("\n");
    }

}

void showLine(line *_line){
    _line->chars->curr = _line->chars->first;
    while(_line->chars->curr != NULL){
        printw("%c", _line->chars->curr->value);
        _line->chars->curr = _line->chars->curr->next;
    }
}

char removeChar(dLine **_lines, int mode){
    charac *aux;

    switch (mode) {
        case CURR_CHAR:

            if((*_lines)->curr->chars->size == 0)
                return removeLine(_lines, CURR_LINE);

            aux = (*_lines)->curr->chars->curr;

            if((*_lines)->curr->chars->size == 1){ //SE CARAC É O ÚNICO
                (*_lines)->curr->chars = newDCharac();
                (*_lines)->curr->chars->size++;
            }else if(aux == (*_lines)->curr->chars->last){ //SE O CARAC É O ÚLTIMO
                aux->prev->next = NULL;
                (*_lines)->curr->chars->last = aux->prev;
                (*_lines)->curr->chars->curr = aux->prev;
            }else if(aux != (*_lines)->curr->chars->first){
                aux->prev->next = aux->next;
                aux->next->prev = aux->prev;
                (*_lines)->curr->chars->curr = aux->prev;
            }
            break;
        case PREV_CHAR:
            break;
    }

    (*_lines)->curr->chars->size--;

    free(aux);
}
