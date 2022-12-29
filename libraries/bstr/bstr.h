#ifndef BSTR_H
#define BSTR_H
#include <stdlib.h>
#include <stdbool.h>

// static string
typedef struct bstr_bstr {
  char *string;
  size_t size;
} bstr;

// allocated string
typedef struct bstr_bstring {
  char *string;
  size_t size;
} bstring;

bstr bstr_new(char *restrict str);
bstring bstring_new(char *restrict str);
bstring bstr_to_bstring(bstr str);
bool bstr_equal(bstr str1, bstr str2);
bool bstring_equal(bstring str1, bstring str2);
bool bstr_contains(bstr str1, bstr str2);
bool bstring_contains(bstr str1, bstr str2);
bool bstring_append(bstring *restrict str1, bstring str2);
void bstring_free(bstring *str);
bstr bstr_copy(bstr str);
bstring bstring_copy(bstring str);

//TODO
void bstr_tok();
void bstring_tok();

#endif
