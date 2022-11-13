#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "vector.h"

#define _assert(expr) \
    assert(expr); \
    printf("Test: %s (passed)\n", #expr);

int main(void)
{
    vec_Vector vector = vec_init();
    _assert(vec_is_empty(&vector) == true);
    _assert(vec_capacity(&vector) == 0);

    vec_push(&vector, 1);
    _assert(vec_capacity(&vector) == sizeof(int));
    _assert(vec_size(&vector) == 1);

    vec_push(&vector, 2);
    _assert(vec_capacity(&vector) == sizeof(int) * 2);
    _assert(vec_size(&vector) == 2);

    vec_push(&vector, 3);
    vec_push(&vector, 4);
    _assert(vec_capacity(&vector) == sizeof(int) * 4);
    _assert(vec_size(&vector) == 4);

    vec_push(&vector, 5);
    _assert(vec_capacity(&vector) == sizeof(int) * 8);
    _assert(vec_pop(&vector) == 5);

    vec_insert(&vector, 3, 99);
    _assert(vec_get(&vector, 3) == 99);

    vec_remove(&vector, 3);
    vec_insert(&vector, 3, 68); // inserting so I don't have to do other checks since vector is smaller than 4
    _assert(vec_get(&vector, 3) != 99);

    vec_free(&vector);
    return 0;
}
