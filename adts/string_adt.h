#ifndef STRING_ADT_H
#define STRING_ADT_H

#include <sys/types.h>
#include <stdbool.h>

typedef struct string_type *string_t;

// Creates string object with base capacity
string_t string_new(void);

// Creates and initializes string object with C string 'cstr'
string_t string_init(const char *cstr);

// Deletes string object and it's content
void string_delete(string_t s);

// Get the char specified by 'index' in the string
char string_get(const string_t s, size_t index);

// Set the char specified by 'index' into 's'
void string_set(string_t s, size_t index, char c);

// Return a pointer to an char array null-terminated representing the value of
// the string object
const char *string_cstr(const string_t s);  // obtém o buffer C interno

// Returns the length of the string, in terms of bytes
size_t string_len(const string_t s);

// Returns the size of the storage space currently allocated for the string,
// expressed in terms of bytes.
size_t string_cap(const string_t s);

// Requests that the string capacity be increased to the value specified by
// new_capacity. Returns NULL if a reallocation attempt fails.
bool string_grow(string_t s, size_t new_capacity);

// Requests the string to reduce its capacity to fit its size.
int string_shrink_to_fit(string_t s);

// Assigns a new value to the string, replacing its current contents.
string_t string_assign(string_t dest, const char *cstr);

// Copies string 'src' to the string 'dest'
string_t string_copy(string_t dest, const string_t src);

string_t string_clear(string_t s);
string_t string_append(string_t s, const char *suffix);
string_t string_concat(string_t dest, const string_t src);

// Inserts 'substr' into the string right before the character indicated by 'pos'
string_t string_insert(string_t s, size_t pos, const char *substr);

string_t string_erase(string_t s, size_t pos, size_t len);
string_t string_push_back(string_t s, char c);
char string_pop_back(string_t s);

int string_compare(const string_t s1, const string_t s2);
bool string_equals(const string_t s1, const string_t s2);
bool string_equals_cstr(const string_t s1, const char *s2);

ssize_t string_find(const string_t s, const char *substr);
ssize_t string_rfind(const string_t s, const char *substr);

bool string_empty(const string_t s);
void string_swap(string_t s1, string_t s2);

#endif
