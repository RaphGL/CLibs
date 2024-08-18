# CLibs
My set of C libraries

| **Library** | **Purpose**                               |
|-------------|-------------------------------------------|
| vec         | generic dynamic array data structure      |
| bstr        | high level string library                 |
| flag        | CLI flag parsing library inspired by Go's |

Note: This set of libraries still depend on libc for memory allocation, the str* functions, etc. It is not meant to be a standalone library at least for now.
It is not possible to change the memory allocator used for now but I'll change that later possibly.

## Building
The recommended way is to just build everything and then take whatever libraries you want from the generated `lib` directory
and it's corresponding header file from said library directory.

```sh
$ cmake . -DCMAKE_BUILD_TYPE=Release
$ make
```
