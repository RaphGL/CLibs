#include "bstr.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bstr bstr_new(char *restrict str) {
  size_t strsiz;
  for (strsiz = 1; str[strsiz] != '\0'; strsiz++)
    ;
  return (bstr){
      .cstr = str,
      .len = strsiz,
  };
}

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

#define BSTRING_TO_BSTR(str_struct)                                            \
  ((bstr){.cstr = (str_struct).cstr, .len = (str_struct).len})

void bstring_free(bstring *str) {
  str->len = 0;
  free(str->cstr);
  str->cstr = NULL;
}

bstring bstr_to_bstring(bstr str) { return bstring_new(str.cstr); }

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
  return bstr_equal(BSTRING_TO_BSTR(str1), BSTRING_TO_BSTR(str2));
}
bool bstring_equal_bstr(bstring str1, bstr str2) {
  return bstr_equal(BSTRING_TO_BSTR(str1), str2);
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

bool bstring_append(bstring *restrict str1, bstring str2) {
  return bstring_append_bstr(str1, BSTRING_TO_BSTR(str2));
}

bstr bstr_copy(bstr str) { return bstr_new(str.cstr); }

bstring bstring_copy(bstring str) { return bstring_new(str.cstr); }

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
  return bstr_contains(BSTRING_TO_BSTR(str1), BSTRING_TO_BSTR(str2));
}

bool bstring_contains_bstr(bstring str1, bstr str2) {
  return bstr_contains(BSTRING_TO_BSTR(str1), str2);
}

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

bool bstr_startswith(bstr str, bstr start_str) {
  if (start_str.len > str.len) {
    return false;
  }

  for (size_t i = 0; i < start_str.len; i++) {
    if (str.cstr[i] != start_str.cstr[i])
      return false;
  }

  return true;
}

bool bstring_startswith(bstring str, bstring start_str) {
  return bstr_startswith(BSTRING_TO_BSTR(str), BSTRING_TO_BSTR(start_str));
}

bool bstring_startswith_bstr(bstring str, bstr start_str) {
  return bstr_startswith(BSTRING_TO_BSTR(str), start_str);
}

bool bstr_endswith(bstr str, bstr end_str) {
  if (end_str.len > str.len) {
    return false;
  }

  const size_t endstr_start = str.len - end_str.len;
  for (size_t i = endstr_start; i < str.len; i++) {
    if (str.cstr[i] != end_str.cstr[i - endstr_start]) {
      return false;
    }
  }

  return true;
}

bool bstring_endswith(bstring str, bstring end_str) {
  return bstr_endswith(BSTRING_TO_BSTR(str), BSTRING_TO_BSTR(end_str));
}

bool bstring_endswith_bstr(bstring str, bstr end_str) {
  return bstr_endswith(BSTRING_TO_BSTR(str), end_str);
}

bstr bstr_reverse(bstr str) {
  bstr tmp = bstr_copy(str);
  size_t i = 0;
  for (size_t reverse_i = str.len; i > 0; i--) {
    i++;
    tmp.cstr[i] = str.cstr[reverse_i];
  }

  return tmp;
}

bstring bstring_reverse(bstring str) {
  bstr tmp = bstr_reverse(BSTRING_TO_BSTR(str));
  return bstr_to_bstring(tmp);
}

bstring bstring_to_lower(bstring str) {
  for (size_t i = 0; i < str.len; i++) {
    switch (str.cstr[i]) {
    case 'A':
      str.cstr[i] = 'a';
      break;
    case 'B':
      str.cstr[i] = 'b';
      break;
    case 'C':
      str.cstr[i] = 'c';
      break;
    case 'D':
      str.cstr[i] = 'd';
      break;
    case 'E':
      str.cstr[i] = 'e';
      break;
    case 'F':
      str.cstr[i] = 'f';
      break;
    case 'G':
      str.cstr[i] = 'g';
      break;
    case 'H':
      str.cstr[i] = 'h';
      break;
    case 'I':
      str.cstr[i] = 'i';
      break;
    case 'J':
      str.cstr[i] = 'j';
      break;
    case 'K':
      str.cstr[i] = 'k';
      break;
    case 'L':
      str.cstr[i] = 'l';
      break;
    case 'M':
      str.cstr[i] = 'm';
      break;
    case 'N':
      str.cstr[i] = 'n';
      break;
    case 'O':
      str.cstr[i] = 'o';
      break;
    case 'P':
      str.cstr[i] = 'p';
      break;
    case 'Q':
      str.cstr[i] = 'q';
      break;
    case 'R':
      str.cstr[i] = 'r';
      break;
    case 'S':
      str.cstr[i] = 's';
      break;
    case 'T':
      str.cstr[i] = 't';
      break;
    case 'U':
      str.cstr[i] = 'u';
      break;
    case 'V':
      str.cstr[i] = 'v';
      break;
    case 'W':
      str.cstr[i] = 'w';
      break;
    case 'X':
      str.cstr[i] = 'x';
      break;
    case 'Y':
      str.cstr[i] = 'y';
      break;
    case 'Z':
      str.cstr[i] = 'z';
      break;
    }
  }

  return str;
}

bstring bstring_to_upper(bstring str) {
  for (size_t i = 0; i < str.len; i++) {
    switch (str.cstr[i]) {
    case 'a':
      str.cstr[i] = 'A';
      break;
    case 'b':
      str.cstr[i] = 'B';
      break;
    case 'c':
      str.cstr[i] = 'C';
      break;
    case 'd':
      str.cstr[i] = 'D';
      break;
    case 'e':
      str.cstr[i] = 'E';
      break;
    case 'f':
      str.cstr[i] = 'F';
      break;
    case 'g':
      str.cstr[i] = 'G';
      break;
    case 'h':
      str.cstr[i] = 'H';
      break;
    case 'i':
      str.cstr[i] = 'I';
      break;
    case 'j':
      str.cstr[i] = 'J';
      break;
    case 'k':
      str.cstr[i] = 'K';
      break;
    case 'l':
      str.cstr[i] = 'L';
      break;
    case 'm':
      str.cstr[i] = 'M';
      break;
    case 'n':
      str.cstr[i] = 'N';
      break;
    case 'o':
      str.cstr[i] = 'O';
      break;
    case 'p':
      str.cstr[i] = 'P';
      break;
    case 'q':
      str.cstr[i] = 'Q';
      break;
    case 'r':
      str.cstr[i] = 'R';
      break;
    case 's':
      str.cstr[i] = 'S';
      break;
    case 't':
      str.cstr[i] = 'T';
      break;
    case 'u':
      str.cstr[i] = 'U';
      break;
    case 'v':
      str.cstr[i] = 'V';
      break;
    case 'w':
      str.cstr[i] = 'W';
      break;
    case 'x':
      str.cstr[i] = 'X';
      break;
    case 'y':
      str.cstr[i] = 'Y';
      break;
    case 'z':
      str.cstr[i] = 'Z';
      break;
    }
  }

  return str;
}
