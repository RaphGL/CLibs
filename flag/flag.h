#include <stddef.h>
#include <stdbool.h>

typedef struct flag_parser {
  int argc;
  char **argv;
  bool parsed;
  struct vec_vector *flags;
} flag_Parser;

flag_Parser flag_new(int argc, char *argv[]);
void flag_free(flag_Parser *p);
size_t flag_nflags(flag_Parser *p);
void flag_parse(flag_Parser *p);
bool flag_parsed(flag_Parser *p);

long *flag_long(flag_Parser *p, char *name, long default_val, char *usage);
float *flag_float(flag_Parser *p, char *name, float default_val, char *usage);
bool *flag_bool(flag_Parser *p, char *name, bool default_val, char *usage);
double *flag_double(flag_Parser *p, char *name, double default_val, char *usage);
char **flag_str(flag_Parser *p, char *name, char *default_val, char *usage);
long long *flag_longlong(flag_Parser *p, char *name, long long default_val, char *usage);
unsigned long *flag_ulong(flag_Parser *p, char *name, unsigned long default_val, char *usage);
unsigned long long *flag_ulonglong(flag_Parser *p, char *name, unsigned long long default_val, char *usage);
