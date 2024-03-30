// TODO: add cap size to bstring to avoid unnecessary allocations

#include "bstr.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bstr bstr_new(char *restrict str) {
  size_t strsiz;
  for (strsiz = 0; str[strsiz] != '\0'; strsiz++)
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
  char *newstr = BSTR_MALLOC(strsiz * sizeof(newstr) + 1);
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
  BSTR_FREE(str->cstr);
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

bool bstr_contains(bstr str, bstr substr) {
  size_t matched_len = 0;

  for (size_t i = 0; i < str.len + substr.len; i++) {
    for (size_t j = 0; j < substr.len; j++) {
      if (i + j >= str.len) {
        break;
      }

      if (str.cstr[i + j] == substr.cstr[j]) {
        ++matched_len;
      } else {
        matched_len = 0;
      }
    }

    if (matched_len == substr.len) {
      return true;
    }
  }

  return false;
}

bool bstring_contains(bstring str1, bstring str2) {
  return bstr_contains(BSTRING_TO_BSTR(str1), BSTRING_TO_BSTR(str2));
}

bool bstring_contains_bstr(bstring str1, bstr str2) {
  return bstr_contains(BSTRING_TO_BSTR(str1), str2);
}

// returns index of when alnum begins at the start of a string
static size_t __bstring_trim_offset_beg(bstring *str) {

  size_t begin_offset = 0;
  for (size_t i = 0; i < str->len; i++) {
    if (isalnum(str->cstr[i])) {
      break;
    }

    if (isspace(str->cstr[i])) {
      begin_offset++;
    }
  }

  return begin_offset;
}

// returns index of when alnum begins at the end of a string
static size_t __bstring_trim_offset_end(bstring *str) {
  size_t end_offset = 0;
  for (size_t i = str->len; i > 0; i--) {
    if (isalnum(str->cstr[i])) {
      break;
    }

    if (isspace(str->cstr[i])) {
      end_offset++;
    }
  }

  return end_offset;
}

static bool __bstring_trim(bstring *str, size_t trimmed_size,
                           size_t begin_offset) {
  char *trimmed_str = BSTR_MALLOC(sizeof(*str->cstr) * trimmed_size + 1);
  if (!trimmed_str) {
    return false;
  }

  for (size_t i = 0; i < trimmed_size; i++) {
    trimmed_str[i] = str->cstr[begin_offset + i];
  }
  trimmed_str[trimmed_size] = '\0';
  BSTR_FREE(str->cstr);

  str->cstr = trimmed_str;
  str->len = trimmed_size;
  return true;
}

bool bstring_trim(bstring *str) {
  size_t begin_offset = __bstring_trim_offset_beg(str);
  size_t end_offset = __bstring_trim_offset_end(str);

  size_t trimmed_size = str->len - begin_offset - end_offset;
  return __bstring_trim(str, trimmed_size, begin_offset);
}

bool bstring_trim_left(bstring *str) {
  size_t begin_offset = __bstring_trim_offset_beg(str);
  size_t trimmed_size = str->len - begin_offset;
  return __bstring_trim(str, trimmed_size, begin_offset);
}

bool bstring_trim_right(bstring *str) {
  size_t end_offset = __bstring_trim_offset_end(str);
  size_t trimmed_size = str->len - end_offset;
  return __bstring_trim(str, trimmed_size, 0);
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
    str.cstr[i] = tolower(str.cstr[i]);
  }

  return str;
}

bstring bstring_to_upper(bstring str) {
  for (size_t i = 0; i < str.len; i++) {
    str.cstr[i] = toupper(str.cstr[i]);
  }

  return str;
}

bool bstr_index(size_t *idx, bstr str, bstr substr) {
  size_t match_count = 0;
  for (size_t i = 0; i + substr.len - 1 < str.len; i++) {
    for (size_t j = 0; j < substr.len; j++) {
      if (str.cstr[i + j] == substr.cstr[j]) {
        ++match_count;
      } else {
        match_count = 0;
        break;
      }
    }

    if (match_count == substr.len) {
      *idx = i;
      return true;
    }
  }

  return false;
}

bool bstring_index(size_t *idx, bstring str, bstring substr) {
  return bstr_index(idx, BSTRING_TO_BSTR(str), BSTRING_TO_BSTR(substr));
}

bool bstring_index_bstr(size_t *idx, bstring str, bstr substr) {
  return bstr_index(idx, BSTRING_TO_BSTR(str), substr);
}

size_t bstr_count(bstr str, bstr substr) {
  if (substr.len == 0) {
    return 0;
  }

  if (substr.len == 1) {
    size_t count = 0;
    for (size_t i = 0; i < str.len; i++) {
      if (str.cstr[i] == substr.cstr[0]) {
        ++count;
      }
    }

    return count;
  }

  size_t count = 0;

  for (size_t i = 0;; i++) {
    str.cstr += i;
    str.len -= i;
    if (!bstr_index(&i, str, substr)) {
      return count;
    }

    ++count;
  }

  return count;
}

size_t bstring_count(bstring str, bstring substr) {
  return bstr_count(BSTRING_TO_BSTR(str), BSTRING_TO_BSTR(substr));
}

// TODO
bool bstr_replace(bstr str, bstr old, bstr new, size_t times);

// TODO
void bstr_replace_all(bstr str, bstr old, bstr new);

bool bstr_is_kebabcase(bstr str) {
  for (size_t i = 0; i < str.len; i++) {
    const char c = str.cstr[i];
    if (islower(c) && isalnum(c) || c == '-')
      continue;
    else
      return false;
  }

  return true;
}

bool bstring_is_kebabcase(bstring str) {
  return bstr_is_kebabcase(BSTRING_TO_BSTR(str));
}

bool bstr_is_upper_kebabcase(bstr str) {
  for (size_t i = 0; i < str.len; i++) {
    const char c = str.cstr[i];
    if (isupper(c) && isalnum(c) || c == '-')
      continue;
    else
      return false;
  }

  return true;
}

bool bstring_is_upper_kebabcase(bstring str) {
  return bstr_is_upper_kebabcase(BSTRING_TO_BSTR(str));
}

bool bstr_is_snakecase(bstr str) {
  for (size_t i = 0; i < str.len; i++) {
    const char c = str.cstr[i];
    if (islower(c) && isalnum(c) || c == '_')
      continue;
    else
      return false;
  }

  return true;
}

bool bstring_is_snakecase(bstring str) {
  return bstr_is_snakecase(BSTRING_TO_BSTR(str));
}

bool bstr_is_upper_snakecase(bstr str) {
  for (size_t i = 0; i < str.len; i++) {
    const char c = str.cstr[i];
    if (isupper(c) && isalnum(c) || c == '_')
      continue;
    else
      return false;
  }

  return true;
}

bool bstring_is_upper_snakecase(bstring str) {
  return bstr_is_upper_snakecase(BSTRING_TO_BSTR(str));
}

bool bstr_is_camelcase(bstr str) {
  if (str.len == 0)
    return false;
  if (isupper(str.cstr[0]))
    return false;

  for (size_t i = 1; i < str.len; i++) {
    const char c = str.cstr[i];
    if (isalnum(c))
      continue;
    else
      return false;
  }

  return true;
}

bool bstring_is_camelcase(bstring str) {
  return bstr_is_camelcase(BSTRING_TO_BSTR(str));
}

bool bstr_is_pascalcase(bstr str) {
  if (str.len == 0)
    return false;
  if (islower(str.cstr[0]))
    return false;

  for (size_t i = 1; i < str.len; i++) {
    const char c = str.cstr[i];
    if (isalnum(c))
      continue;
    else
      return false;
  }

  return true;
}

bool bstring_is_pascalcase(bstring str) {
  return bstr_is_pascalcase(BSTRING_TO_BSTR(str));
}

bool bstr_is_adacase(bstr str) {
  if (str.len == 0)
    return false;
  if (islower(str.cstr[0]))
    return false;

  for (size_t i = 1; i < str.len; i++) {
    const char c = str.cstr[i];
    if (isalnum(c))
      continue;
    else if (i + 1 < str.len && c == '_') {
      if (islower(str.cstr[i + 1]))
        return false;
    } else
      return false;
  }

  return true;
}

bool bstring_is_adacase(bstring str) {
  return bstr_is_adacase(BSTRING_TO_BSTR(str));
}
