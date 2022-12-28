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

  bstring_free(&string);
  assert(string.size == 0);
  assert(string.string == NULL);

  puts("Passed all tests.");
  return 0;
}
