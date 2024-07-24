#include "flag.h"
#include "../bstr/bstr.h"
#include "../vec/vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct flag_flag {
  bstr name;
  bstr usage;

  enum {
    FLAG_BOOL,
    FLAG_STR,
    FLAG_LONG,
    FLAG_ULONG,
    FLAG_LONGLONG,
    FLAG_ULONGLONG,
    FLAG_FLOAT,
    FLAG_DOUBLE,
  } type;

  union {
    bool bool_flag;
    char *str_flag;
    long long_flag;
    unsigned long ulong_flag;
    long long longlong_flag;
    unsigned long long ulonglong_flag;
    float float_flag;
    double double_flag;
  };
};

flag_Parser flag_new(int argc, char *argv[]) {
  return (flag_Parser){
      .argc = argc,
      .argv = argv,
      .flags = vec_new(sizeof(struct flag_flag *)),
      .remaining = vec_new(sizeof(char *)),
      .parsed = false,
  };
}

void flag_free(flag_Parser *p) {
  for (size_t i = 0; i < vec_len(p->flags); i++) {
    struct flag_flag *flag;
    vec_get(p->flags, i, &flag);
    free(flag);
  }

  vec_free(p->flags);
  vec_free(p->remaining);
}

size_t flag_nargs(flag_Parser *p) { return vec_len(p->remaining); }

char *flag_arg(flag_Parser *p, size_t idx) {
  char *arg;
  if (!vec_get(p->remaining, idx, &arg)) {
    return NULL;
  }

  return arg;
}

#define CREATE_FLAG(T, flag_type)                                              \
  T *flag_##T(flag_Parser *p, char *name, T default_val, char *usage) {        \
    struct flag_flag *flag = malloc(sizeof(*flag));                            \
    if (!flag) {                                                               \
      return NULL;                                                             \
    }                                                                          \
                                                                               \
    *flag = (struct flag_flag){                                                \
        .name = bstr_new(name),                                                \
        .usage = bstr_new(usage),                                              \
        .T##_flag = default_val,                                               \
        .type = (flag_type),                                                   \
    };                                                                         \
                                                                               \
    if (!vec_push(p->flags, &flag)) {                                          \
      free(flag);                                                              \
      return NULL;                                                             \
    }                                                                          \
                                                                               \
    return &flag->T##_flag;                                                    \
  }

CREATE_FLAG(long, FLAG_LONG)
CREATE_FLAG(float, FLAG_FLOAT)
CREATE_FLAG(bool, FLAG_BOOL)
CREATE_FLAG(double, FLAG_DOUBLE)
typedef char *str;
CREATE_FLAG(str, FLAG_STR)
typedef long long longlong;
CREATE_FLAG(longlong, FLAG_LONGLONG)
typedef unsigned long ulong;
CREATE_FLAG(ulong, FLAG_ULONG)
typedef unsigned long long ulonglong;
CREATE_FLAG(ulonglong, FLAG_ULONGLONG)

void flag_print_flags(flag_Parser *p) {
  for (size_t i = 0; i < vec_len(p->flags); i++) {
    struct flag_flag *curr_flag;
    vec_get(p->flags, i, &curr_flag);
    printf("--%s\n\t%s", curr_flag->name.cstr, curr_flag->usage.cstr);
    printf(" (default: ");
    switch (curr_flag->type) {
    case FLAG_BOOL:
      printf(curr_flag->bool_flag ? "true" : "false");
      break;
    case FLAG_DOUBLE:
      printf("%lf", curr_flag->double_flag);
      break;
    case FLAG_FLOAT:
      printf("%f", curr_flag->float_flag);
      break;
    case FLAG_LONG:
      printf("%ld", curr_flag->long_flag);
      break;
    case FLAG_LONGLONG:
      printf("%lld", curr_flag->longlong_flag);
      break;
    case FLAG_ULONGLONG:
      printf("%llu", curr_flag->ulonglong_flag);
      break;
    case FLAG_STR:
      printf("%s", curr_flag->str_flag);
      break;
    case FLAG_ULONG:
      printf("%lu", curr_flag->ulong_flag);
      break;
    }
    puts(")");
  }
}

size_t flag_nflags(flag_Parser *p) { return vec_len(p->flags); }

static bool arg_is_flag(bstr *arg) {
  bstr one_dash = bstr_new("-");
  bstr two_dashes = bstr_new("--");

  if (bstr_startswith(*arg, two_dashes)) {
    arg->cstr += 2;
    arg->len -= 2;
  } else if (bstr_startswith(*arg, one_dash)) {
    arg->cstr += 1;
    arg->len -= 1;
  } else {
    return false;
  }

  return true;
}

bool flag_parsed(flag_Parser *p) { return p->parsed; }

void flag_parse(flag_Parser *p) {
  for (int curr_arg_idx = 0; curr_arg_idx < p->argc; curr_arg_idx++) {
    bstr arg = bstr_new(p->argv[curr_arg_idx]);

    if (!arg_is_flag(&arg)) {
      vec_push(p->remaining, &arg.cstr);
      continue;
    }

    bstr flag_name, flag_value;
    size_t sep_idx = 0;
    if (bstr_index(&sep_idx, arg, bstr_new("=")) ||
        bstr_index(&sep_idx, arg, bstr_new(":"))) {
      flag_value = bstr_new(arg.cstr + sep_idx + 1);
      flag_name = arg;
      flag_name.len -= flag_value.len + 1;
    } else {
      flag_name = arg;
      flag_value = bstr_new("");
    }

    struct flag_flag *curr_flag = NULL;
    for (size_t j = 0; j < vec_len(p->flags); j++) {
      vec_get(p->flags, j, &curr_flag);
      if (!bstr_equal(flag_name, curr_flag->name)) {
        continue;
      }

      char *flag_val = NULL;

      if (flag_value.len == 0 && curr_flag->type != FLAG_BOOL) {
        if (++curr_arg_idx >= p->argc) {
          break;
        }

        flag_val = p->argv[curr_arg_idx];
      } else {
        flag_val = flag_value.cstr;
      }

      switch (curr_flag->type) {
      case FLAG_BOOL:
        if (flag_value.len == 0) {
          curr_flag->bool_flag = !curr_flag->bool_flag;
        } else if (bstr_equal(flag_value, bstr_new("true"))) {
          curr_flag->bool_flag = true;
        } else if (bstr_equal(flag_value, bstr_new("false"))) {
          curr_flag->bool_flag = false;
        }
        break;

      case FLAG_STR:
        curr_flag->str_flag = flag_val;
        break;

      case FLAG_LONG:
        curr_flag->long_flag = strtol(flag_val, NULL, 10);
        break;

      case FLAG_ULONG:
        curr_flag->ulong_flag = strtoul(flag_val, NULL, 10);
        break;

      case FLAG_LONGLONG:
        curr_flag->longlong_flag = strtoll(flag_val, NULL, 10);
        break;

      case FLAG_ULONGLONG:
        curr_flag->ulonglong_flag = strtoull(flag_val, NULL, 10);
        break;

      case FLAG_DOUBLE:
        curr_flag->double_flag = strtod(flag_val, NULL);
        break;

      case FLAG_FLOAT:
        curr_flag->float_flag = strtof(flag_val, NULL);
        break;
      }

      // goto to next flag after this flag is parsed
      break;
    }
  }

  p->parsed = true;
}
