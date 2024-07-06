# Vector

Flag parser inspired by Go's flag package.

## Usage

Create a parser

```c
flag_Parser p = flag_new(argc, argv);
```

Declare a flag

```c
// long *flag_long(flag_Parser *p, char *name, long default_val, char *usage);
long *n = flag_long(&p, "n", 0, "a number");
char **user = flag_str(&p, "user", 0, "get user name");
```

Cleanup

```c
flag_free(&p);
```

---

On the terminal:
```sh
# both - and -- are accepted
$ program -n 200 --user root
```

## Dependencies
`flag` depends on the `bstr` and `vector` libraries to function.
