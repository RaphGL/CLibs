#ifndef BSTR_H
#define BSTR_H
#include <stdbool.h>
#include <stdlib.h>

// Statically allocated string
//
// Immutable string. Attempting to modify it will result in a segfault.
typedef struct bstr_bstr {
  char *cstr;
  size_t len;
} bstr;

// Dynamically allocated string
//
// Mutable string.
typedef struct bstr_bstring {
  char *cstr;
  size_t len;
  size_t cap;
} bstring;

// Creates a statically allocated string
bstr bstr_new(char *restrict str);
// Creates a dynamically allocated string
bstring bstring_new(char *restrict str);
// Initializes an empty bstring with preallocated size
bstring bstring_with_capacity(size_t capacity);

// Increases the capacity for a bstring
//
// returns: false if new capacity is smaller than length or if allocation fails
bool bstring_reserve(bstring *str, size_t capacity);
// Creates a new bstring with the contents of `str`
bstring bstr_to_bstring(bstr str);

// Compares the strings of str1 and str2 and returns whether they're equal or not
bool bstr_equal(bstr str1, bstr str2);
// Compares the strings of str1 and str2 and returns whether they're equal or not
bool bstring_equal(bstring str1, bstring str2);
// Compares the strings of str1 and str2 and returns whether they're equal or not
bool bstring_equal_bstr(bstring str1, bstr str2);

bool bstr_contains(bstr str, bstr substr);
bool bstring_contains(bstring str, bstring substr);
bool bstring_contains_bstr(bstring str, bstr substr);

// Appends `str2` to `str1`
bool bstring_append(bstring *restrict str1, bstring str2);
// Appends `str2` to `str1`
bool bstring_append_bstr(bstring *restrict str1, bstr str2);

// Frees memory allocated by bstring
void bstring_free(bstring *str);
// Creates a deep copy of a string
bstr bstr_copy(bstr str);
// Creates a deep copy of a string
bstring bstring_copy(bstring str);

// Remove whitespace at the beginning and end of `str`
bool bstring_trim(bstring *str);
// Remove whitespace at the start of the `str`
bool bstring_trim_left(bstring *str);
// Remove whitespace at the end of `str`
bool bstring_trim_right(bstring *str);

bool bstr_startswith(bstr str, bstr start_str);
bool bstring_startswith(bstring str, bstring start_str);
bool bstring_startswith_bstr(bstring str, bstr start_str);

bool bstr_endswith(bstr str, bstr end_str);
bool bstring_endswith(bstring str, bstring end_str);
bool bstring_endswith_bstr(bstring str, bstr end_str);

// Returns a reversed str
//
// Note: the original string is not modified.
bstr bstr_reverse(bstr str);
// Returns a reversed str
//
// Note: the original string is not modified, a new string is allocated to store the reversed string.
bstring bstring_reverse(bstring str);

// Convert all characters into their lower case variants.
//
// Returns: the same str that was passed in, this allows the function to be used directly as an expression
//
// Note: there's no bstr_to_lower as modifying a char* would result in SEGFAULT
bstring bstring_to_lower(bstring *str);
// Convert all characters into their upper case variants.
//
// Returns: the same str that was passed in, this allows the function to be used directly as an expression
//
// Note: there's no bstr_to_upper as modifying a char* would result in SEGFAULT
bstring bstring_to_upper(bstring *str);

// Writes the index for the susbtring to idx if the substring exists.
//
// Return: false if substring doesn't exist.
bool bstr_index(size_t *idx, bstr str, bstr substr);
// Writes the index for the susbtring to idx if the substring exists.
//
// Returns: false if substring doesn't exist.
bool bstring_index(size_t *idx, bstring str, bstring substr);
// Writes the index for the susbtring to idx if the substring exists.
//
// Returns: false if substring doesn't exist.
bool bstring_index_bstr(size_t *idx, bstring str, bstr substr);

// Counts how many times substr occurs in str
size_t bstr_count(bstr str, bstr substr);
// Counts how many times substr occurs in str
size_t bstring_count(bstring str, bstring substr);
// Counts how many times substr occurs in str
size_t bstring_count_bstr(bstring str, bstr substr);

// Replaces the `old` string by the `new` string `times` times.
bool bstring_replace(bstring *str, bstring old, bstring new, size_t times);
// Replaces the `old` string by the `new` string `times` times.
bool bstring_replace_bstr(bstring *str, bstr old, bstr new, size_t times);
// Replaces the `old` string by the `new` string `times` times.
void bstring_replace_all(bstring *str, bstring old, bstring new);
// Replaces the `old` string by the `new` string `times` times.
void bstring_replace_all_bstr(bstring *str, bstr old, bstr new);

// Returns: true if string is a valid `kebab-case-string`.
bool bstr_is_kebabcase(bstr str);
// Returns: true if string is a valid `kebab-case-string`.
bool bstring_is_kebabcase(bstring str);
// Returns: true if string is a valid `KEBAB-CASE-STRING`.
bool bstr_is_upper_kebabcase(bstr str);
// Returns: true if string is a valid `KEBAB-CASE-STRING`.
bool bstring_is_upper_kebabcase(bstring str);

// Returns: true if string is a valid `snake_case_string`.
bool bstr_is_snakecase(bstr str);
// Returns: true if string is a valid `snake_case_string`.
bool bstring_is_snakecase(bstring str);
// Returns: true if string is a valid `SNAKE_CASE_STRING`.
bool bstring_is_upper_snakecase(bstring str);
// Returns: true if string is a valid `SNAKE_CASE_STRING`.
bool bstr_is_upper_snakecase(bstr str);

// Returns: true if string is a valid `camelCaseString`.
bool bstr_is_camelcase(bstr str);
// Returns: true if string is a valid `camelCaseString`.
bool bstring_is_camelcase(bstring str);

// Returns: true if string is a valid `PascalCaseString`.
bool bstr_is_pascalcase(bstr str);
// Returns: true if string is a valid `PascalCaseString`.
bool bstring_is_pascalcase(bstring str);

// Returns: true if string is a valid `Ada_Case_String`.
bool bstr_is_adacase(bstr str);
// Returns: true if string is a valid `Ada_Case_String`.
bool bstring_is_adacase(bstring str);
#endif
