//TAD charac

#define CURR_CHAR 0
#define FIRST_CHAR 1
#define LAST_CHAR 2
#define NEXT_CHAR 3
#define PREV_CHAR 4

struct charac{
    int pos;
    char value;
    struct charac *prev, *next; 
};
typedef struct charac charac;

struct dCharac{
    charac *first, *last, *curr;
    int size;
};
typedef struct dCharac dCharac;

//START dCharac functions
dCharac* newDCharac();
int isDCharacEmpty(dCharac *chars);
//END dCharac functions

//START charac functions
charac* newCharac();
//END charac functions

/*

====START FUNCTIONS====

*/

dCharac* newDCharac(){
    dCharac* chars = (dCharac*)malloc(sizeof(dCharac));
    chars->curr = chars->first = chars->last = NULL;
    chars->size = 0;
}

int isDCharacEmpty(dCharac *chars){
    return chars == NULL || chars->size == 0;
}

charac *newCharac(){
    charac *_char = (charac*)malloc(sizeof(charac));
    _char->next = _char->prev = NULL;
    _char->pos = _char->value = 0;

    return _char;
}