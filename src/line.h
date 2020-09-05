#include "charac.h"
#include <curses.h>
//TAD line

#define CURR_LINE 0
#define FIRST_LINE 1
#define LAST_LINE 2
#define NEXT_LINE 3
#define PREV_LINE 4

struct line{
    int pos;
    struct line *prev, *next;
    dCharac* chars;
};
typedef struct line line;

struct dLine{
    line *first, *last, *curr;
    int size;
};
typedef struct dLine dLine;

//START dLine functions
dLine* newDLine();
void insertLine(dLine **lines, int mode); //AS LINHAS SEMPRE SÃO INSERIDAS VAZIAS
line* getLine(dLine *lines, int mode);
void moveLineTo(dLine *lines, int mode);
int isDLineEmpty(dLine *lines);
void showLines(dLine* lines);
//END dLine functions

//START line functions
line* newLine();
void insertChar(line** _line, char character, int mode);
void showLine(line *_line);
//END line functions


/*

====START FUNCTIONS====

*/

dLine* newDLine(){
    dLine* lines = (dLine*)malloc(sizeof(dLine));
    lines->curr = lines->first = lines->last = NULL;
    lines->size = 0;

    return lines;
}

void insertLine(dLine **lines, int mode){
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

void moveLineTo(dLine *lines, int mode){
    if(!isDLineEmpty(lines))
        switch (mode) {
            case CURR_LINE:
                lines->curr = lines->curr;
                break;
            case FIRST_LINE:
                lines->curr = lines->first;
                break;
            case LAST_LINE:
                lines->curr = lines->last;
                break;
            case NEXT_LINE:
                if(lines->curr != NULL)
                    lines->curr = lines->curr->next;
                break;
            case PREV_LINE:
                if(lines->curr != NULL)
                    lines->curr = lines->curr->prev;
        }
}

int isDLineEmpty(dLine *lines){
    return lines == NULL || lines->size == 0;
}

line* newLine(){
    line* _line = (line*)malloc(sizeof(line));
    _line->prev = _line->next = NULL;
    _line->pos = 0;
    _line->chars = NULL;
    
    return _line;
}

void insertChar(line **_line, char character, int mode){
    charac* _charac = newCharac();
    _charac->value = character;

    if(isDCharacEmpty((*_line)->chars)){
        (*_line)->chars = newDCharac();
        (*_line)->chars->first = (*_line)->chars->last = (*_line)->chars->curr = _charac;
    }else
        switch (mode) {
            case FIRST_CHAR:
                _charac->next = (*_line)->chars->first;
                _charac->next->prev = _charac;
                (*_line)->chars->first = _charac;
                break;
            case LAST_CHAR:
                _charac->prev = (*_line)->chars->last;
                _charac->prev->next = _charac;
                (*_line)->chars->last = _charac;
                break;
            case NEXT_CHAR:
                _charac->next = (*_line)->chars->curr->next;
                (*_line)->chars->curr->next->prev = _charac;
                _charac->prev = (*_line)->chars->curr;
                (*_line)->chars->curr->next = _charac;
                break;
            case PREV_CHAR:
                _charac->prev = (*_line)->chars->curr->prev;
                (*_line)->chars->curr->prev->next = _charac;
                _charac->next = (*_line)->chars->curr;
                (*_line)->chars->curr->prev = _charac;
        }
    (*_line)->chars->size++;
}

void showLines(dLine *lines){
    moveLineTo(lines, FIRST_LINE);
    while(getLine(lines, CURR_LINE) != NULL){
        showLine(getLine(lines, CURR_LINE));
        moveLineTo(lines, NEXT_LINE);
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