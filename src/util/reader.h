#ifndef NSH_UTIL_READER_H
#define NSH_UTIL_READER_H

#include "../defs.h"

struct reader {
    char*  ptr;
};

void reader_create(struct reader* reader, const char* ptr);
void reader_destroy(struct reader* reader);

bool reader_has(struct reader* reader);
char reader_get(struct reader* reader);
void reader_advance(struct reader* reader);
char reader_get_and_advance(struct reader* reader);

bool reader_is(struct reader* reader, char c);
bool reader_is_any(struct reader* reader, const char* c);
bool reader_is_space(struct reader* reader);
bool reader_iss(struct reader* reader, const char* str);

bool reader_check(struct reader* reader, char c);
bool reader_check_any(struct reader* reader, const char* c);
bool reader_check_space(struct reader* reader);
bool reader_checks(struct reader* reader, const char* str);

void reader_skip_whitespaces(struct reader* reader);

#endif
