#include "bstr.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  bstr str = bstr_new("my first test");
  assert(str.len == 13);

  assert(bstr_equal(str, bstr_new("my first test")));
  assert(bstr_contains(str, bstr_new("y fir")));

  bstring string = bstr_to_bstring(str);
  assert(string.len == 13);
  assert(strcmp(string.cstr, "my first test") == 0);

  bstring new = bstring_new(" append this");
  size_t old_size = string.len;
  bstring_append(&string, new);
  assert(new.len + old_size == string.len);

  bstring_free(&new);
  new = bstring_new("my first test append this");
  assert(bstring_equal(string, new));

  bstring_free(&new);
  bstring_free(&string);
  assert(string.len == 0);
  assert(string.cstr == NULL);

  bstr to_trim = bstr_new("     remove spaces pwease?    ");
  bstring trim_this = bstr_to_bstring(to_trim);
  bstring_trim(&trim_this);
  assert(strcmp(trim_this.cstr, "remove spaces pwease?") == 0);

  bstring_append_bstr(&trim_this, bstr_new(" appended"));
  assert(bstring_equal_bstr(trim_this, bstr_new("remove spaces pwease? appended")));

  bstring_free(&trim_this);
  puts("Passed all tests.");
  return 0;
}
