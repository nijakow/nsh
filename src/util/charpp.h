#ifndef NSH_UTIL_CHARPP_H
#define NSH_UTIL_CHARPP_H

#include "../defs.h"

struct charpp {
    char**  data;
    size_t  alloc;
    size_t  fill;
};

void charpp_create(struct charpp* charpp);
void charpp_destroy(struct charpp* charpp);

void charpp_append(struct charpp* charpp, const char* str);

#endif