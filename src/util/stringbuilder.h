#ifndef NSH_UTIL_STRINGBUILDER_H
#define NSH_UTIL_STRINGBUILDER_H

#include "../defs.h"

struct stringbuilder {
    char*   buffer;
    size_t  alloc;
    size_t  fill;
};

void stringbuilder_create(struct stringbuilder* sb);
void stringbuilder_destroy(struct stringbuilder* sb);

void stringbuilder_append_char(struct stringbuilder* sb, char c);
void stringbuilder_append_cstr(struct stringbuilder* sb, const char* str);

const char* stringbuilder_get_static(struct stringbuilder* sb);

#endif
