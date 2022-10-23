#include "reader.h"

void reader_create(struct reader* reader, const char* ptr) {
    reader->ptr = (char*) ptr;
}

void reader_destroy(struct reader* reader) {

}

bool reader_has(struct reader* reader) {
    return *reader->ptr != '\0';
}

char reader_get(struct reader* reader) {
    return *reader->ptr;
}

void reader_advance(struct reader* reader) {
    if (reader_has(reader))
        reader->ptr++;
}

char reader_get_and_advance(struct reader* reader) {
    char c;
    
    c = reader_get(reader);
    reader_advance(reader);
    return c;
}

bool reader_is(struct reader* reader, char c) {
    return reader_get(reader) == c;
}

bool reader_is_any(struct reader* reader, const char* c) {
    size_t  index;

    for (index = 0; c[index] != '\0'; index++) {
        if (reader_is(reader, c[index]))
            return true;
    }

    return false;
}

bool reader_is_space(struct reader* reader) {
    return reader_is_any(reader, " \t\n\r");
}


bool reader_check(struct reader* reader, char c) {
    if (reader_is(reader, c)) {
        reader_advance(reader);
        return true;
    }
    return false;
}

bool reader_check_any(struct reader* reader, const char* c) {
    if (reader_is_any(reader, c)) {
        reader_advance(reader);
        return true;
    }
    return false;
}

bool reader_check_space(struct reader* reader) {
    if (reader_is_space(reader)) {
        reader_advance(reader);
        return true;
    }
    return false;
}

bool reader_checks(struct reader* reader, const char* str) {
    size_t  index;

    for (index = 0; str[index] != '\0' && str[index] == reader->ptr[index]; index++);
    if (str[index] == '\0') {
        reader->ptr += index;
        return true;
    }
    return false;
}

void reader_skip_whitespaces(struct reader* reader) {
    while (reader_check_space(reader));
}
