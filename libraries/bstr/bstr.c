#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstr.h"
#include <ctype.h>

// bstr    = static string
bstr bstr_new(char *restrict str)
{
  size_t strsiz;
  for (strsiz = 1; str[strsiz] != '\0'; strsiz++)
    ;
  return (bstr){
      .string = str,
      .size = strsiz,
  };
}

// bstring = allocated string
bstring bstring_new(char *restrict str)
{
  size_t strsiz;
  for (strsiz = 1; str[strsiz] != '\0'; strsiz++)
    ;
  char *newstr = malloc(strsiz * sizeof(newstr));
  memcpy(newstr, str, strsiz + 1);
  return (bstring){
      .string = newstr,
      .size = strsiz,
  };
}

// converts bstr to bstring
bstring bstr_to_bstring(bstr str) { return bstring_new(str.string); }

// compares whehter two strings are equal
#define STR_EQUAL                         \
  if (str1.size != str2.size)             \
  {                                       \
    return false;                         \
  }                                       \
                                          \
  for (size_t i = 0; i < str1.size; i++)  \
  {                                       \
    if (str1.string[i] != str2.string[i]) \
    {                                     \
      return false;                       \
    }                                     \
  }                                       \
                                          \
  return true;

bool bstr_equal(bstr str1, bstr str2)
{
  STR_EQUAL
}
bool bstring_equal(bstring str1, bstring str2) { STR_EQUAL }
bool bstring_equal_bstr(bstring str1, bstr str2) { STR_EQUAL }

#define STR_APPEND                                                  \
  size_t newsiz = str1->size + str2.size;                           \
  void *tmp = realloc(str1->string, sizeof(str1->string) * newsiz); \
  if (!tmp)                                                         \
  {                                                                 \
    return false;                                                   \
  }                                                                 \
                                                                    \
  const size_t oldsiz = str1->size;                                 \
  *str1 = (bstring){.size = newsiz, .string = tmp};                 \
  for (size_t i = oldsiz; i <= newsiz; i++)                         \
  {                                                                 \
    str1->string[i] = str2.string[i - oldsiz];                      \
  }                                                                 \
                                                                    \
  return true;

// appends str2 to str1
bool bstring_append(bstring *restrict str1, bstring str2) { STR_APPEND }

bool bstring_append_bstr(bstring *restrict str1, bstr str2){STR_APPEND}

// makes a deep copy of string from src to dest
bstr bstr_copy(bstr str)
{
  return bstr_new(str.string);
}

bstring bstring_copy(bstring str) { return bstring_new(str.string); }

// returns whether a str2 is contained in the str1 string
#define STR_CONTAINS                                         \
  bool *status = calloc(str2.size - 1, sizeof(str2.string)); \
                                                             \
  for (size_t i = 0; i < str1.size + str2.size; i++)         \
  {                                                          \
    for (size_t j = 0; j < str2.size; j++)                   \
    {                                                        \
      if (i + j >= str1.size)                                \
      {                                                      \
        break;                                               \
      }                                                      \
                                                             \
      if (str1.string[i + j] == str2.string[j])              \
      {                                                      \
        status[j] = true;                                    \
      }                                                      \
      else                                                   \
      {                                                      \
        status[j] = false;                                   \
      }                                                      \
    }                                                        \
                                                             \
    bool is_contained = true;                                \
    for (size_t j = 0; j < str2.size; j++)                   \
    {                                                        \
      if (status[j] == false)                                \
      {                                                      \
        is_contained = false;                                \
      }                                                      \
    }                                                        \
                                                             \
    if (is_contained)                                        \
    {                                                        \
      free(status);                                          \
      return true;                                           \
    }                                                        \
  }                                                          \
                                                             \
  free(status);                                              \
  return false;

bool bstr_contains(bstr str1, bstr str2)
{
  STR_CONTAINS
}
bool bstring_contains(bstring str1, bstring str2) { STR_CONTAINS }
bool bstring_contains_bstr(bstring str1, bstr str2) { STR_CONTAINS }

// returns string that separated by sep one by one
// TODO
void bstr_tok();
void bstring_tok();

bool bstring_trim(bstring *str)
{
  size_t begin_offset = 0;
  for (size_t i = 0; i < str->size; i++)
  {
    if (isalnum(str->string[i]))
    {
      break;
    }

    if (isspace(str->string[i]))
    {
      begin_offset++;
    }
  }

  size_t end_offset = 0;
  for (size_t i = str->size; i > 0; i--)
  {
    if (isalnum(str->string[i]))
    {
      break;
    }

    if (isspace(str->string[i]))
    {
      end_offset++;
    }
  }

  size_t trimmed_size = str->size - begin_offset - end_offset;
  char *trimmed = malloc(sizeof(str->string) * trimmed_size);
  if (!trimmed)
  {
    return false;
  }

  memcpy(trimmed, &str->string[begin_offset], sizeof(str->string) * trimmed_size);
  trimmed[trimmed_size] = '\0';
  free(str->string);

  str->string = trimmed;
  str->size = trimmed_size;
  return true;
}

// frees allocated string from memory
void bstring_free(bstring *str)
{
  str->size = 0;
  free(str->string);
  str->string = NULL;
}