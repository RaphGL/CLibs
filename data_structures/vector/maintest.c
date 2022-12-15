#include "vector.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    vec_Vector *vector = vec_new();
    assert(vec_len(vector) == 0);

    vec_push(vector, (int *)1);
    assert(vec_len(vector) == 1 && vec_capacity(vector) == sizeof(void *));

    vec_push(vector, (int *)2);
    assert(vec_len(vector) == 2 && vec_capacity(vector) == sizeof(void *) * 2);

    vec_push(vector, (int *)3);
    vec_push(vector, (int *)4);
    vec_push(vector, (int *)5);
    vec_push(vector, (int *)6);
    vec_push(vector, (int *)7);
    vec_push(vector, (int *)8);
    assert(vec_len(vector) == 8 && vec_capacity(vector) == sizeof(void *) * 8);

    assert(*(int *)vec_get(vector, 2) == 3);
    assert(*(int *)vec_get(vector, 7) == 8);
    assert(vec_get(vector, 9) == NULL); // tests failure

    assert(*(int *)vec_pop(vector) == 8 && vec_len(vector) == 7);

    vec_free(vector);
    puts("Test passed.");
    return 0;
}