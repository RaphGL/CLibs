# Bstr

A proper string type for C that wraps the standard null terminated string in C
There are 2 types of strings in this library:

- `bstr` - a static string type
- `bstring` - a heap allocated string that can dynamically grow

## Usage

Create a static string

```c
bstr static_str = bstr_new("my new static string");
```

Create a dynamic string

```c
bstring dyn_str = bstring_new("my new dynamic string");
```

Free dynamic string

```c
bstring_free(dyn_str);
```

**Note: Almost all bstr functions will have a bstring equivalent**

Check if strings are equal

```c
if (bstr_equal(str1, str2))
{
    puts("they're equal");
}
```

Check if a string is contained in another

```c
if (bstr_contains(og_str, bstr_new("is this contained?")))
{
    // do something
}
```

Get string size

```c
printf("size: %ld", str.len);
```

Get underlying C string

```c
printf("string: %s", str.cstr);
```

For more info on the operations available check `bstr.h` for API and `maintest.c` for usage examples.
