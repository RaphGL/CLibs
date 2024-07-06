#include "bstr.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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
  char *newstr = malloc(strsiz * sizeof(newstr) + 1);
  for (size_t i = 0; i < strsiz + 1; i++) {
    newstr[i] = str[i];
  }
  return (bstring){
      .cstr = newstr,
      .len = strsiz,
      .cap = strsiz,
  };
}

bstring bstring_with_capacity(size_t capacity) {
  bstring str = (bstring){
      .cstr = malloc(capacity),
      .len = 0,
      .cap = capacity,
  };

  for (size_t i = 0; i < capacity; i++) {
    str.cstr[i] = '\0';
  }
  return str;
}

bool bstring_reserve(bstring *str, size_t capacity) {
  if (capacity <= str->len || capacity == str->cap) {
    return false;
  }

  char *tmp = realloc(str->cstr, capacity);
  if (!tmp) {
    return false;
  }

  str->cstr = tmp;
  str->cap = capacity;
  return true;
}

#define BSTRING_TO_BSTR(str_struct)                                            \
  ((bstr){.cstr = (str_struct).cstr, .len = (str_struct).len})

void bstring_free(bstring *str) {
  str->len = 0;
  free(str->cstr);
  *str = (bstring){0};
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
  const size_t oldsiz = str1->len;
  const size_t newsiz = str1->len + str2.len;

  if (str1->cap < newsiz) {
    void *tmp = realloc(str1->cstr, sizeof(*str1->cstr) * newsiz + 1);
    if (!tmp) {
      return false;
    }

    str1->cap = newsiz;
    str1->cstr = tmp;
  }

  str1->len = newsiz;
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
    // compare whether str[i..i+substr.len] == substr
    for (size_t j = 0; j < substr.len; j++) {
      // avoid segfaulting
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
  // shift everything from `begin_offset` to the start of the string
  for (size_t i = 0; i < trimmed_size; i++) {
    str->cstr[i] = str->cstr[begin_offset + i];
  }
  // discard everything after the `trimmed_size` by termianting with '\0'
  str->cstr[trimmed_size] = '\0';
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

bstr bstr_to_lower(bstr str) {
  for (size_t i = 0; i < str.len; i++) {
    str.cstr[i] = tolower(str.cstr[i]);
  }

  return str;
}

bstring bstring_to_lower(bstring *str) {
  str->cstr = bstr_to_lower(BSTRING_TO_BSTR(*str)).cstr;
  return *str;
}

bstr bstr_to_upper(bstr str) {
  for (size_t i = 0; i < str.len; i++) {
    str.cstr[i] = toupper(str.cstr[i]);
  }

  return str;
}

bstring bstring_to_upper(bstring *str) {
  str->cstr = bstr_to_upper(BSTRING_TO_BSTR(*str)).cstr;
  return *str;
}

bool bstr_index(size_t *idx, bstr str, bstr substr) {
  size_t match_count = 0;
  for (size_t i = 0; i + substr.len - 1 < str.len; i++) {
    // find when str[i..substr.len] == substr
    for (size_t j = 0; j < substr.len; j++) {
      if (str.cstr[i + j] == substr.cstr[j]) {
        ++match_count;
      } else {
        // match_count = 0 whenever any of the characters on the substr differ
        match_count = 0;
        break;
      }
    }

    // if the substrings match their length would match
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

  // if substr is a single character, just count how many times that letter
  // occurs
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
    // increment by `i` every time so bstr_index wouldn't return the same substr
    // but the next substr that matches
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

size_t bstring_count_bstr(bstring str, bstr substr) {
  return bstr_count(BSTRING_TO_BSTR(str), substr);
}

// TODO: fix broken function
bool bstring_replace_bstr(bstring *str, bstr old, bstr new, size_t times) {
  if (bstr_equal(old, new) || times == 0) {
    return false;
  }

  // finds out how many times the word should be replaced
  size_t count = times;
  size_t occurrences = bstr_count(BSTRING_TO_BSTR(*str), old);
  if (occurrences == 0) {
    return false;
  } else if (occurrences < times) {
    count = occurrences;
  }

  // reallocate string to fit the new size
  size_t newsiz = str->len + count * (new.len - old.len) + 1;
  bstring_reserve(str, newsiz);
  bstring build_str = bstring_with_capacity(newsiz);
  char *strbeg = build_str.cstr;

  bstr tmp = (bstr){
      .cstr = str->cstr,
      .len = str->len,
  };
  size_t start = 0;

  for (size_t i = 0; i < count; i++) {
    bstr_index(&start, tmp, old);

    // writes all strings before replace old word is reached
    memcpy(build_str.cstr, tmp.cstr, start);
    build_str.cstr += start;
    // replaces old word by new word
    memcpy(build_str.cstr, new.cstr, new.len);
    build_str.cstr += new.len;
    build_str.len += start + new.len;

    tmp.cstr += start + old.len;
    tmp.len -= start + old.len;
  }

  if (build_str.len < newsiz) {
    memcpy(build_str.cstr, tmp.cstr, tmp.len);
  }
  build_str.cstr = strbeg;
  // adds length to count for null character
  ++build_str.len;
  // writes the newly built string to the old address to avoid having dangling
  // pointers if the user is already using the string elsewhere since it's
  // passed by value
  memcpy(str->cstr, build_str.cstr, newsiz);
  str->len = newsiz - 1;
  bstring_free(&build_str);
  return true;
}

bool bstring_replace(bstring *str, bstring old, bstring new, size_t times) {
  return bstring_replace_bstr(str, BSTRING_TO_BSTR(old), BSTRING_TO_BSTR(new),
                              times);
}

void bstring_replace_all_bstr(bstring *str, bstr old, bstr new) {
  size_t count = bstring_count_bstr(*str, old);
  bstring_replace_bstr(str, old, new, count);
}

void bstring_replace_all(bstring *str, bstring old, bstring new) {
  size_t count = bstring_count(*str, old);
  bstring_replace(str, old, new, count);
}

bool bstr_is_kebabcase(bstr str) {
  for (size_t i = 0; i < str.len; i++) {
    const char c = str.cstr[i];
    if ((islower(c) && isalnum(c)) || c == '-')
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
    if ((isupper(c) && isalnum(c)) || c == '-')
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
    if ((islower(c) && isalnum(c)) || c == '_')
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
    if ((isupper(c) && isalnum(c)) || c == '_')
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
