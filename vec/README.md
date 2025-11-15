# Vector

Rust inspired vector for C.

## Usage

---

To use this vector you will have to link the math library:

```sh
$ cc -lm vector.o your_program.o
```


---

Create vector for type T

```c
// Choose your type
#define VEC_ITEM_TYPE T
// If the type is not a valid identifier you can use a suffix
#define VEC_SUFFIX mytype
// then include the header
#include "vector.h"
```

If you're using it in your `.c` files, don't forget to `#define VEC_IMPLEMENTATION`, this will instantiate the functions for your type.
On headers you should include without the implementation "directive". This will only paste in the declarations.

#### Usage examples with type `int`:

```c
vec_Vector *int_vec = vec_new_int();
```

Create vector from array
```c
int arr[] = {1, 2, 3, 4, 5};
vec_Vector *int_vec = vec_from_int(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]));
```

Delete Vector

```c
vec_free_int(int_vec);
```

Push items

```c
int i = 20;
vec_push_int(int_vec, i);
```

Pop items

```c
int item;
vec_pop_int(vector, &item);
// if you don't want the popped value
vec_pop_int(vector, NULL);
```

Get item at index:

```c
int item;
vec_get_int(vector, index, &item);
```

Remove item at index

```c
int item;
vec_remove_int(vector, index, &item);
// if you don't want the removed value
vec_remove_int(vector, index, NULL);
```

Append a vector to another

```c
vec_append_int(destvec, srcvec);
```

Print vector

```c
vec_printf_int("%d", vector);
```

Get length

```c
vec_len_int(vector);
```

Get capacity (memory allocated)

```c
vec_capacity_int(vector);
```

Check if vector is empty

```c
vec_is_empty_int(vector);
```
