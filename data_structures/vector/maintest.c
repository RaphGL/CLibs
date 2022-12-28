#include "vector.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
  vec_Vector *vector = vec_new();
  assert(vec_is_empty(vector));

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

  assert(vec_len(vector) == 7);
  vec_insert(vector, 3, (int *)22);
  assert(*(int *)vec_get(vector, 3) == 22);
  assert(vec_len(vector) == 8);

  vec_remove(vector, 3);
  assert(*(int *)vec_get(vector, 3) == 4);
  assert(vec_len(vector) == 7);

  vec_Vector *vector2 = vec_new();
  vec_push(vector2, (int *)91);
  vec_push(vector2, (int *)92);
  vec_push(vector2, (int *)93);
  int prelen = vec_len(vector2);
  vec_append(vector2, vector);
  assert(prelen + vec_len(vector) == vec_len(vector2));

  vec_free(vector);
  vec_free(vector2);
  puts("Test passed.");
  return 0;
}
