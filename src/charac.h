//TAD charac

#define CURR_CHAR 0
#define FIRST_CHAR 1
#define LAST_CHAR 2
#define NEXT_CHAR 3
#define PREV_CHAR 4

struct charac{
    char value;
    struct charac *prev, *next; 
};
typedef struct charac charac;

//START charac functions
charac* newCharac();
//END charac functions

/*

====START FUNCTIONS====

*/

int isLineEmpty(charac *chars){
    return chars == NULL;
}

charac *newCharac(){
    charac *_char = (charac*)malloc(sizeof(charac));
    _char->next = _char->prev = NULL;
    _char->value = 0;

    return _char;
}