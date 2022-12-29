#include "bstr.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  bstr str = bstr_new("my first test");
  assert(str.size == 13);

  assert(bstr_equal(str, bstr_new("my first test")));
  assert(bstr_contains(str, bstr_new("y fir")));

  bstring string = bstr_to_bstring(str);
  assert(string.size == 13);
  assert(strcmp(string.string, "my first test") == 0);

  bstring new = bstring_new(" append this");
  size_t old_size = string.size;
  bstring_append(&string, new);
  assert(new.size + old_size == string.size);

  bstring_free(&new);
  new = bstring_new("my first test append this");
  assert(bstring_equal(string, new));

  bstring_free(&new);
  bstring_free(&string);
  assert(string.size == 0);
  assert(string.string == NULL);

  puts("Passed all tests.");
  return 0;
}
