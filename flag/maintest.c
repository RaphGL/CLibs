#include "flag.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  char *argv[] = {"--test=77", "--funnyno", "69420", "first_remaining", "--is-true", "-pi", "3.14159265359", "--hello:world", "second remaining"};
  int argc = sizeof(argv) / sizeof(argv[0]);

  flag_Parser p = flag_new(argc, argv);
  assert(flag_nflags(&p) == 0);
  long *funny_num = flag_long(&p, "funnyno", 0, "the funny number");
  char **hello = flag_str(&p, "hello", "test", "says hello");
  double *pi = flag_double(&p, "pi", 9.3, "the number for pi");
  long *test = flag_long(&p, "test", 99, "get number 99 or something else");
  bool *is_true = flag_bool(&p, "is-true", false, "returns true when used");
  assert(flag_nflags(&p) == 5);

  assert(flag_parsed(&p) == false);
  flag_parse(&p);
  assert(flag_parsed(&p) == true);

  assert(flag_nargs(&p) == 2);
  assert(strcmp(flag_arg(&p, 0), "first_remaining") == 0);
  assert(strcmp(flag_arg(&p, 1), "second remaining") == 0);

  assert(*funny_num == 69420);
  assert(strcmp(*hello, "world") == 0);
  assert(*pi == 3.14159265359);
  assert(*test == 77);
  assert(*is_true);

  flag_free(&p);
  puts("test passed.");
}
