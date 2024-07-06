#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_int(void) {
  int arr[] = {1, 2, 3, 4, 5};
  vec_Vector *int_vec =
      vec_from(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]));
  vec_printf("%d", int_vec);
  assert(vec_len(int_vec) == 5);
  vec_free(int_vec);

  vec_Vector *vec = vec_new(sizeof(int));
  assert(vec_len(vec) == 0);
  assert(vec_capacity(vec) == 0);

  int val = 0;
  vec_push(vec, &val);
  val = 1;
  vec_push(vec, &val);
  val = 2;
  vec_push(vec, &val);
  val = 3;
  vec_push(vec, &val);
  val = 4;
  vec_push(vec, &val);
  assert(vec_len(vec) == 5);

  vec_pop(vec, &val);
  vec_pop(vec, &val);
  assert(vec_len(vec) == 3);
  assert(val == 3);
  assert(vec_capacity(vec) > 0);

  val = 69;
  vec_insert(vec, 2, &val);
  val = 23432;
  vec_remove(vec, 2, &val);
  assert(val == 69);

  vec_printf("%d", vec);

  vec_Vector *vec2 = vec_new(sizeof(int));
  val = 0;
  vec_push(vec2, &val);
  val = 1;
  vec_push(vec2, &val);
  val = 2;
  vec_push(vec2, &val);
  val = 3;
  vec_push(vec2, &val);
  size_t len = vec_len(vec);
  vec_append(vec, vec2);
  assert(vec_len(vec) == vec_len(vec2) + len);

  vec_free(vec2);
  vec_free(vec);
  puts("Primitive type test passed");
}

void test_struct(void) {
  typedef struct {
    float gravity;
    int year;
    char *name;
  } TestStruct;

  vec_Vector *vec = vec_new(sizeof(TestStruct));
  assert(vec_is_empty(vec) == true);
  assert(vec_len(vec) == 0);
  assert(vec_capacity(vec) == 0);

  vec_push(vec, &(TestStruct){
                    .name = "vector",
                    .gravity = 9.8,
                    .year = 2222,
                });

  assert(vec_capacity(vec) == sizeof(TestStruct));
  vec_push(vec, &(TestStruct){
                    .name = "vector",
                    .gravity = 9.8,
                    .year = 2222,
                });
  vec_push(vec, &(TestStruct){
                    .name = "vector",
                    .gravity = 9.8,
                    .year = 2222,
                });
  assert(vec_len(vec) == 3);

  TestStruct val;
  vec_pop(vec, &val);
  assert(vec_len(vec) == 2);
  assert(val.year == 2222);
  assert(strcmp(val.name, "vector") == 0);

  vec_free(vec);
  puts("Struct test passed");
}

int main(void) {
  test_int();
  test_struct();
  return 0;
}
