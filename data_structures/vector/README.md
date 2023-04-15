# Vector

Rust inspired vector for C.
It tries to minimize memory foot print by allocating memory in chunks and growing or shrinking depending on how many elements it has.

## Usage

---

To use this vector you will have to link the math library:

```sh
$ cc -lm vector.o your_program.o
```

---

Create vector for type T

```c
vec_Vector *int_vec = vec_new(sizeof(int));
```

Create vector from array
```c
int arr[] = {1, 2, 3, 4, 5};
vec_Vector *int_vec = vec_from(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]));
```

Delete Vector

```c
vec_free(int_vec);
```

Push items

```c
int i = 0;
vec_push(int_vec, &i);
```

Pop items

```c
int item;
vec_pop(vector, &item);
// if you don't want the popped value
vec_pop(vector, NULL);
```

Get item at index:

```c
int item;
vec_get(vector, index, &item);
```

Remove item at index

```c
int item;
vec_remove(vector, index, &item);
// if you don't want the removed value
vec_remove(vector, index, NULL);
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

---
**Note**: Using other types is as simple as passing `sizeof(T)` where T is the desired type.
