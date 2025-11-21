#include "string_adt.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BASE_CAPACITY 8
#define GROW_FACTOR 1.5

static inline ssize_t ssabs(ssize_t a) {
    return (a < 0) ? -a : a;
}

typedef struct string_type {
    size_t len;
    size_t cap;
    char *buf;
} string_type;

string_t string_new(void) {
    string_type *s = malloc(sizeof(*s));
    if (!s) goto ERR_ALLOC_STRING;

    s->buf = malloc(BASE_CAPACITY * sizeof(char));
    if (!s->buf) goto ERR_ALLOC_STRING_BUF;

    s->len = 0;
    s->cap = BASE_CAPACITY;
    s->buf[0] = '\0';
    return s;

    ERR_ALLOC_STRING_BUF:
    free(s);
    ERR_ALLOC_STRING:
    return NULL;
}

string_t string_init(const char *cstr) {
    assert(cstr != NULL);

    size_t len = strlen(cstr);
    size_t cap = len < BASE_CAPACITY ? BASE_CAPACITY : len * GROW_FACTOR;

    string_type *s = malloc(sizeof(*s));
    if (!s) goto ERR_ALLOC_STRING;

    s->buf = malloc(cap * sizeof(char));
    if (!s->buf) goto ERR_ALLOC_STRING_BUF;
    
    s->len = len;
    s->cap = cap;
    memcpy(s->buf, cstr, len + 1);
    return s;

    ERR_ALLOC_STRING_BUF:
    free(s);
    ERR_ALLOC_STRING:
    return NULL;
}

void string_delete(string_t s) {
    assert(s != NULL);
    free(s->buf);
    free(s);
}

string_t string_assign(string_t dest, const string_t src) {
    assert(src != NULL);
    return string_assign_cstr(dest, src->buf);
}

string_t string_assign_cstr(string_t dest, const char *cstr) {
    assert(dest != NULL);
    assert(cstr != NULL);

    size_t len = strlen(cstr);

    if (len >= dest->cap) {
        if (!string_grow(dest, len)) {
            return NULL;
        }
    }

    dest->len = len;
    memcpy(dest->buf, cstr, len + 1);
    return dest;
}

size_t string_copy(string_t s, char *buf, size_t pos, size_t len) {
    assert(s != NULL);
    assert(buf != NULL);
    assert(pos < s->len);

    const size_t len_copy = s->len - pos <= len ? len : s->len - pos;
    memcpy(buf, &s->buf[pos], len_copy);

    return len_copy;
}

size_t string_len(const string_t s) {
    assert(s != NULL);
    return s->len;
}

size_t string_cap(const string_t s) {
    assert(s != NULL);
    return s->cap;
}

bool string_grow(string_t s, size_t new_capacity) {
    assert(s != NULL);
    if (new_capacity < s->cap) return true;

    new_capacity *= GROW_FACTOR;
    char *rs_buf = realloc(s->buf, new_capacity);
    if (!rs_buf) return false;

    s->buf = rs_buf;
    s->cap = new_capacity;
    return true;
}

string_t string_clear(string_t s) {
    assert(s != NULL);
    s->len = 0;
    s->buf[0] = '\0';
    return s;
}

string_t string_append(string_t s, const char *suffix) {
    assert(s != NULL);
    assert(suffix != NULL);

    size_t len = strlen(suffix);
    size_t total_len = len + s->len;

    if (total_len >= s->cap) {
        if (!string_grow(s, total_len)) {
            return NULL;
        }
    }

    s->len = total_len;
    strcat(s->buf, suffix);
    return s;
}

string_t string_insert(string_t s, size_t pos, const char *substr) {
    assert(s != NULL);
    assert(substr != NULL);
    assert(pos < s->len);

    size_t len = strlen(substr);
    size_t total_len = s->len + len;

    if (total_len >= s->cap) {
        if (!string_grow(s, total_len)) {
            return NULL;
        }
    }

    memmove(&s->buf[pos+len], &s->buf[pos], s->len - pos);
    memcpy(&s->buf[pos], substr, len);

    s->len = total_len;
    s->buf[total_len] = '\0';
    return s;
}

string_t string_erase(string_t s, size_t pos, size_t len) {
    assert(s != NULL);
    assert(pos < s->len);
    assert(len <= (s->len - pos));

    memmove(&s->buf[pos], &s->buf[pos + len], (s->len - pos - len) + 1);
    s->len -= len;
    return s;
}

string_t string_concat(string_t dest, const string_t src) {
    assert(dest != NULL);
    assert(src != NULL);

    if (!string_append(dest, src->buf))
        return NULL;
    return dest;
}

const char *string_cstr(const string_t s) {
    assert(s != NULL);
    return s->buf;
}

char string_get(const string_t s, size_t index) {
    assert(s != NULL);
    assert(index < s->len);
    return s->buf[index];
}

void string_set(string_t s, size_t index, char c) {
    assert(s != NULL);
    assert(index < s->len);

    s->buf[index] = c;
}

int string_compare(const string_t s1, const string_t s2) {
    return string_compare_cstr(s1, s2->buf);
}

int string_compare_cstr(const string_t s1, const char *s2) {
    assert(s1 != NULL);
    assert(s2 != NULL);
    return strcmp(s1->buf, s2);
}

bool string_equals(const string_t s1, const string_t s2) {
    return string_equals_cstr(s1, s2->buf);
}

bool string_equals_cstr(const string_t s1, const char *s2) {
    return string_compare_cstr(s1, s2) == 0;
}

ssize_t string_find(const string_t s, const char *substr) {
    assert(s != NULL);
    assert(substr != NULL);

    char *sp = strstr(s->buf, substr);
    if (sp == NULL) return -1;

    return ssabs(s->buf - sp);
}

bool string_empty(const string_t s) {
    assert(s != NULL);
    return s->len == 0;
}

void string_swap(string_t s1, string_t s2) {
    assert(s1 != NULL);
    assert(s2 != NULL);

    string_type tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}
