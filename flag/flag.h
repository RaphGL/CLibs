#include <stddef.h>
#include <stdbool.h>

// todo: create doc comments

typedef struct flag_parser {
  int argc;
  char **argv;
  bool parsed;
  struct vec_vector *flags;
  struct vec_vector *remaining;
} flag_Parser;

// Initializes parser.
// Parser should later be freed with `flag_free`.
flag_Parser flag_new(int argc, char *argv[]);
void flag_free(flag_Parser *p);

// Parses flags that have been setup by the `flag_<type>` functions.
// This function should only be called after the setup has done. 
void flag_parse(flag_Parser *p);
// Returns true if flags have been parsed.
bool flag_parsed(flag_Parser *p);
// Returns the number of flags that have been configured.
size_t flag_nflags(flag_Parser *p);
// Prints all the flags that have been setup for the parser.
void flag_print_flags(flag_Parser *p);


// Returns the number of remaining args after flags have been handled.
size_t flag_nargs(flag_Parser *p);
// Retrieves remaining args after flags have been handled by index starting from 0.
char *flag_arg(flag_Parser *p, size_t idx);

long *flag_long(flag_Parser *p, char *name, long default_val, char *usage);
float *flag_float(flag_Parser *p, char *name, float default_val, char *usage);
bool *flag_bool(flag_Parser *p, char *name, bool default_val, char *usage);
double *flag_double(flag_Parser *p, char *name, double default_val, char *usage);
char **flag_str(flag_Parser *p, char *name, char *default_val, char *usage);
long long *flag_longlong(flag_Parser *p, char *name, long long default_val, char *usage);
unsigned long *flag_ulong(flag_Parser *p, char *name, unsigned long default_val, char *usage);
unsigned long long *flag_ulonglong(flag_Parser *p, char *name, unsigned long long default_val, char *usage);
