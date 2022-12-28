#include <stdlib.h>
#include <stdio.h>
#include "bstr.h"

int main(void) {
  bstr str = bstr_new("my first test");
  puts(str.string);
  printf("len: %ld\n", str.size);
  if (bstr_equal(str, bstr_new("my first test"))) {
    puts("Strings are equal");
  }

  if (bstr_contains(str, bstr_new("y fir"))) {
    puts("String contained");
  }

  puts(str.string);
  printf("len: %ld\n", str.size);

  bstring string = bstr_to_bstring(str);
  printf("string: %s\n", string.string);
  bstring_free(string);
  return 0;
}
