# Vector
Rust inspired vector for C.
It tries to minimize memory foot print by allocating memory in chunks and growing or shrinking depending on how many elements it has.

## Usage
---
To use this vector you will have to link the math library:
```sh
$ CC -lm vector.o your_program.o
```
---

Create vector
```c
vec_Vector *vector = vec_new();
```

Delete Vector
```c
vec_free(vector);
```

Push items
```c
vec_push(vector, (int *)1);
```

Pop items
```c
int item = *(int *)vec_pop(vector);
```

Get item at index:
```c
int item = *(int *)vec_get(vector, index);
```

Remove item at index
```c
vec_remove(vector, index);
```

Append a vector to another
```c
vec_append(destvec, srcvec);
```

Print vector
```c
vec_printf("%d", vector);
```

Get length
```c
vec_len(vector);
```

Get capacity (memory allocated)
```c
vec_capacity(vector);
```

Check if vector is empty
```c
vec_is_empty(vector);
```