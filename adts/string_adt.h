#ifndef STRING_ADT_H
#define STRING_ADT_H

#include <sys/types.h>
#include <stdbool.h>

typedef struct string_type *string_t;

// Creates string object with base capacity.
string_t string_new(void);

// Creates and initializes string object with C string 'cstr'.
string_t string_init(const char *cstr);

// Deletes string object and it's content.
void string_delete(string_t s);

// Get the char specified by 'index' in the string.
char string_get(const string_t s, size_t index);

// Set the char specified by 'index' into 's'.
void string_set(string_t s, size_t index, char c);

// Return a pointer to an char array null-terminated representing the value of
// the string object.
const char *string_cstr(const string_t s);

// Returns the length of the string, in terms of bytes.
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

// Copies string 'src' to the string 'dest'.
string_t string_copy(string_t dest, const string_t src);

// Erases the contents of the string. In practice, defining its length as zero.
string_t string_clear(string_t s);

// Extends the string by appending additional characters at the end of its
// current value.
string_t string_append(string_t s, const char *suffix);

// Concatenates the value of string 'src' to the string dest.
// Act as an alias for string_append(s1, string_cstr(s2)).
string_t string_concat(string_t dest, const string_t src);

// Inserts 'substr' into the string right before the character indicated by 'pos'.
string_t string_insert(string_t s, size_t pos, const char *substr);

// Erases part of the string, reducing its length.
string_t string_erase(string_t s, size_t pos, size_t len);

// Appends character c to the end of the string, increasing its length by one.
string_t string_push_back(string_t s, char c);

// Erases the last character of the string, reducing its length by one.
char string_pop_back(string_t s);

// Compares the value of the string object s1 with the value of s2.
int string_compare(const string_t s1, const string_t s2);

// Returns whether the values of the strings 's1' and 's2' are equal.
bool string_equals(const string_t s1, const string_t s2);

// Returns whether the values of the string 's1' and the character array 's2'
// are equal.
bool string_equals_cstr(const string_t s1, const char *s2);

// Searches the string for the first occurrence of the sequence specified by
// its arguments.
ssize_t string_find(const string_t s, const char *substr);

// Searches the string for the last occurrence of the sequence specified by
// its arguments.
ssize_t string_rfind(const string_t s, const char *substr);

// Returns whether the string is empty (i.e. whether its length is 0).
bool string_empty(const string_t s);

// Exchanges the content of 's1' by the content of 's2'.
void string_swap(string_t s1, string_t s2);

#endif
