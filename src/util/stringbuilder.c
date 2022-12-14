#include "stringbuilder.h"


static bool stringbuilder_ensure_space(struct stringbuilder* sb, size_t size) {
    char*  new_buffer;

    if (sb->alloc >= size) return true;

    if (size < sb->alloc * 2)
        size = sb->alloc * 2;

    new_buffer = nsh_realloc(sb->buffer, size * sizeof(char));

    if (new_buffer != NULL) {
        sb->buffer = new_buffer;
        sb->alloc  = size;
        return true;
    }

    return false;
}


void stringbuilder_create(struct stringbuilder* sb) {
    sb->buffer = NULL;
    sb->alloc  = 0;
    sb->fill   = 0;
}

void stringbuilder_destroy(struct stringbuilder* sb) {
    if (sb->buffer != NULL) nsh_free(sb->buffer);
}

void stringbuilder_clear(struct stringbuilder* sb) {
    sb->fill = 0;
}

void stringbuilder_append_char(struct stringbuilder* sb, char c) {
    if (!stringbuilder_ensure_space(sb, sb->fill + 2))
        return;
    sb->buffer[sb->fill++] = c;
    sb->buffer[sb->fill]   = '\0';
}

void stringbuilder_append_cstr(struct stringbuilder* sb, const char* str) {
    size_t  index;

    for (index = 0; str[index] != '\0'; index++)
        stringbuilder_append_char(sb, str[index]);
}

const char* stringbuilder_get_static(struct stringbuilder* sb) {
    return (sb->buffer == NULL || sb->fill == 0) ? "" : sb->buffer;
}

char* stringbuilder_get(struct stringbuilder* sb) {
    return nsh_strdup(stringbuilder_get_static(sb));
}
