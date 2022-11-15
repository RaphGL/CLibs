#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "vector.h"

VEC_INIT(int)

#define _assert(expr) \
    assert(expr); \
    printf("Test: %s (passed)\n", #expr);

int main(void)
{
    vec_Vector_int vector = vec_init_int();
    _assert(vec_is_empty_int(&vector) == true);
    _assert(vec_capacity_int(&vector) == 0);

    vec_push_int(&vector, 1);
    _assert(vec_capacity_int(&vector) == sizeof(int));
    _assert(vec_size_int(&vector) == 1);

    vec_push_int(&vector, 2);
    _assert(vec_capacity_int(&vector) == sizeof(int) * 2);
    _assert(vec_size_int(&vector) == 2);

    vec_push_int(&vector, 3);
    vec_push_int(&vector, 4);
    _assert(vec_capacity_int(&vector) == sizeof(int) * 4);
    _assert(vec_size_int(&vector) == 4);

    vec_push_int(&vector, 5);
    _assert(vec_capacity_int(&vector) == sizeof(int) * 8);
    _assert(vec_pop_int(&vector) == 5);

    vec_insert_int(&vector, 3, 99);
    _assert(vec_get_int(&vector, 3) == 99);

    vec_remove_int(&vector, 3);
    vec_insert_int(&vector, 3, 68); // inserting so I don't have to do other checks since vector is smaller than 4
    _assert(vec_get_int(&vector, 3) != 99);

    vec_print_int(&vector);
    vec_free_int(&vector);
    return 0;
}
