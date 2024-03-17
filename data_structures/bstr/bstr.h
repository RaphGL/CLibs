#ifndef BSTR_H
#define BSTR_H
#include <stdbool.h>
#include <stdlib.h>

// static string
// 
// immutable string. attempting to modify it will result in a segfault.
typedef struct bstr_bstr {
  char *cstr;
  size_t len;
} bstr;

// heap allocated string
//
// mutable string type allocated on the heap.
typedef struct bstr_bstring {
  char *cstr;
  size_t len;
} bstring;

// creates a stack allocated string
bstr bstr_new(char *restrict str);
bstring bstring_new(char *restrict str);
bstring bstr_to_bstring(bstr str);
bool bstr_equal(bstr str1, bstr str2);
bool bstring_equal(bstring str1, bstring str2);
bool bstring_equal_bstr(bstring str1, bstr str2);
bool bstr_contains(bstr str1, bstr str2);
bool bstring_contains(bstring str1, bstring str2);
bool bstring_contains_bstr(bstring str1, bstr str2);
bool bstring_append(bstring *restrict str1, bstring str2);
bool bstring_append_bstr(bstring *restrict str1, bstr str2);
void bstring_free(bstring *str);
// creates a deep copy of a string
bstr bstr_copy(bstr str);
// creates a deep copy of a string
bstring bstring_copy(bstring str);
// remove whitespace from beginning and end
bool bstring_trim(bstring *str);
bool bstr_startswith(bstr str, bstr start_str);
bool bstring_startswith(bstring str, bstring start_str);
bool bstring_startswith_bstr(bstring str, bstr start_str);
bool bstr_endswith(bstr str, bstr end_str);
bool bstring_endswith_bstr(bstring str, bstr end_str);
bstr bstr_reverse(bstr str);
bstring bstring_reverse(bstring str);
bstring bstring_to_lower(bstring str);
bstring bstring_to_upper(bstring str);

#endif
