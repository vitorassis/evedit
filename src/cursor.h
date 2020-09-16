#include "line.h"

struct sCursor{
    line *cLine, *top;
    charac *cCharac;
    int curX, curY;
};
typedef struct sCursor sCursor;