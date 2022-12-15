# Usage
Create a vector with:
```c
vec_Vector *vector = vec_new();
```

Deleting vector:
```c
vec_free(vector);
```

To push items:
```c
vec_push(vector, (int *)1);
```

To pop items:
```c
int item = *(int *)vec_pop(vector);
```

Get item at index:
```c
int item = *(int *)vec_get(vector, index);
```
