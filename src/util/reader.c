#include "reader.h"

void reader_create(struct reader* reader, char* ptr) {
    reader->ptr = ptr;
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
    reader->ptr++;
}

bool reader_is(struct reader* reader, char c) {
    return reader_get(reader) == c;
}

bool reader_is_any(struct reader* reader, const char* c) {
    size_t  index;

    for (index = 0; c[index] != '\0'; index++) {
        if (reader_get(reader) == c[index])
            return true;
    }

    return false;
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

bool reader_checks(struct reader* reader, const char* str) {
    // TODO
    return false;
}
