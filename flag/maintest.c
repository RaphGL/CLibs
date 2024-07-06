#include "flag.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  char *argv[] = {"--funnyno", "69420", "-pi", "3.14159265359", "--hello", "world"};
  int argc = sizeof(argv) / sizeof(argv[0]);

  flag_Parser p = flag_new(argc, argv);
  assert(flag_nflags(&p) == 0);
  long *funny_num = flag_long(&p, "funnyno", 0, "the funny number");
  char **hello = flag_str(&p, "hello", "test", "says hello");
  double *pi = flag_double(&p, "pi", 0, "the number for pi");
  assert(flag_nflags(&p) == 3);

  assert(flag_parsed(&p) == false);
  flag_parse(&p);
  assert(flag_parsed(&p) == true);

  assert(*funny_num == 69420);
  assert(strcmp(*hello, "world") == 0);
  assert(*pi == 3.14159265359);

  flag_free(&p);
  puts("test passed.");
}
