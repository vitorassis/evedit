#include "cursor.h"

//TAD file

struct confFile{
    char fileName[100];
    int saved;
};
typedef struct confFile confFile;

struct file{
    sCursor *cursor;
    line *lines;
    confFile config;
};
typedef struct file file;

file* newFile();

void addLine(file**);
void addChar(file**, char);

char isFileEmpty(file*);

void removeLine(file**, int);
void removeChar(file**, int);

file* newFile(){
    file* f = (file*)malloc(sizeof(file));
    addLine(&f);
    addChar(&f, 0);
    f->cursor->cLine = f->lines;
    f->cursor->cCharac = f->lines->chars;

    return f;
}

void addLine(file** f){
    line* nLine = newLine();
    if(isFileEmpty(*f))       // SE É A PRIMEIRA LINHA  
        (*f)->lines = nLine;
    else{                     // SE JÁ HÁ LINHAS
        if((*f)->cursor->cLine->next == NULL){  // SE FOR A ÚLTIMA LINHA
            
        }
        else if((*f)->cursor->cLine->prev == NULL){  // SE FOR A PRIMEIRA LINHA
            
        }
        else{                                   // QUALQUER OUTRO CASO
            
            
        }
    }
}