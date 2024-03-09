#include "bstr.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// bstr    = static string
bstr bstr_new(char *restrict str) {
  size_t strsiz;
  for (strsiz = 1; str[strsiz] != '\0'; strsiz++)
    ;
  return (bstr){
      .cstr = str,
      .len = strsiz,
  };
}

// bstring = allocated string
bstring bstring_new(char *restrict str) {
  size_t strsiz;
  for (strsiz = 1; str[strsiz] != '\0'; strsiz++)
    ;
  char *newstr = malloc(strsiz * sizeof(newstr) + 1);
  for (size_t i = 0; i < strsiz + 1; i++) {
    newstr[i] = str[i];
  }
  return (bstring){
      .cstr = newstr,
      .len = strsiz,
  };
}

// converts bstr to bstring
bstring bstr_to_bstring(bstr str) { return bstring_new(str.cstr); }

// compares whehter two strings are equal
bool bstr_equal(bstr str1, bstr str2) {
  if (str1.len != str2.len) {
    return false;
  }

  for (size_t i = 0; i < str1.len; i++) {
    if (str1.cstr[i] != str2.cstr[i]) {
      return false;
    }
  }

  return true;
}
bool bstring_equal(bstring str1, bstring str2) {
  return bstr_equal(bstr_new(str1.cstr), bstr_new(str2.cstr));
}
bool bstring_equal_bstr(bstring str1, bstr str2) {
  return bstr_equal(bstr_new(str1.cstr), str2);
}

bool bstring_append_bstr(bstring *restrict str1, bstr str2) {
  size_t newsiz = str1->len + str2.len;
  void *tmp = realloc(str1->cstr, sizeof(*str1->cstr) * newsiz + 1);
  if (!tmp) {
    return false;
  }

  const size_t oldsiz = str1->len;
  *str1 = (bstring){.len = newsiz, .cstr = tmp};
  for (size_t i = oldsiz; i <= newsiz; i++) {
    str1->cstr[i] = str2.cstr[i - oldsiz];
  }

  return true;
}
// appends str2 to str1
bool bstring_append(bstring *restrict str1, bstring str2) {
  return bstring_append_bstr(str1, bstr_new(str2.cstr));
}

// makes a deep copy of string from src to dest
bstr bstr_copy(bstr str) { return bstr_new(str.cstr); }

bstring bstring_copy(bstring str) { return bstring_new(str.cstr); }

// returns whether a str2 is contained in the str1 string
bool bstr_contains(bstr str1, bstr str2) {
  bool *status = calloc(str2.len - 1, sizeof(str2.cstr));

  for (size_t i = 0; i < str1.len + str2.len; i++) {
    for (size_t j = 0; j < str2.len; j++) {
      if (i + j >= str1.len) {
        break;
      }

      if (str1.cstr[i + j] == str2.cstr[j]) {
        status[j] = true;
      } else {
        status[j] = false;
      }
    }

    bool is_contained = true;
    for (size_t j = 0; j < str2.len; j++) {
      if (status[j] == false) {
        is_contained = false;
      }
    }

    if (is_contained) {
      free(status);
      return true;
    }
  }

  free(status);
  return false;
}

bool bstring_contains(bstring str1, bstring str2) {
  return bstr_contains(bstr_new(str1.cstr), bstr_new(str2.cstr));
}

bool bstring_contains_bstr(bstring str1, bstr str2) {
  return bstr_contains(bstr_new(str1.cstr), str2);
}

// returns string that separated by sep one by one
// TODO
void bstr_tok();
void bstring_tok();

bool bstring_trim(bstring *str) {
  size_t begin_offset = 0;
  for (size_t i = 0; i < str->len; i++) {
    if (isalnum(str->cstr[i])) {
      break;
    }

    if (isspace(str->cstr[i])) {
      begin_offset++;
    }
  }

  size_t end_offset = 0;
  for (size_t i = str->len; i > 0; i--) {
    if (isalnum(str->cstr[i])) {
      break;
    }

    if (isspace(str->cstr[i])) {
      end_offset++;
    }
  }

  size_t trimmed_size = str->len - begin_offset - end_offset;
  char *trimmed = malloc(sizeof(*str->cstr) * trimmed_size + 1);
  if (!trimmed) {
    return false;
  }

  for (size_t i = 0; i < trimmed_size; i++) {
    trimmed[i] = str->cstr[begin_offset + i];
  }
  trimmed[trimmed_size] = '\0';
  free(str->cstr);

  str->cstr = trimmed;
  str->len = trimmed_size;
  return true;
}

// frees allocated string from memory
void bstring_free(bstring *str) {
  str->len = 0;
  free(str->cstr);
  str->cstr = NULL;
}
