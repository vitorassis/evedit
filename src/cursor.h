#include "line.h"

struct sCursor{
    line *cLine, *top;
    charac *cCharac;
    int curX, cur;
};
typedef struct sCursor sCursor;