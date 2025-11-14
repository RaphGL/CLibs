#define VEC_ITEM_TYPE int
#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_int(void) {
   int arr[] = { 1, 2, 3, 4, 5 };
   vec_Vector_int *int_vec = vec_from_int(arr, sizeof(arr) / sizeof(arr[0]), sizeof(arr[0]));
   vec_printf_int("%d", int_vec);
   assert(vec_len_int(int_vec) == 5);
   vec_free_int(int_vec);

   vec_Vector_int *vec = vec_new_int();
   assert(vec_len_int(vec) == 0);
   assert(vec_capacity_int(vec) == 0);

   int val = 0;
   vec_push_int(vec, val);
   val = 1;
   vec_push_int(vec, val);
   val = 2;
   vec_push_int(vec, val);
   val = 3;
   vec_push_int(vec, val);
   val = 4;
   vec_push_int(vec, val);
   assert(vec_len_int(vec) == 5);

   vec_pop_int(vec, &val);
   vec_pop_int(vec, &val);
   assert(vec_len_int(vec) == 3);
   assert(val == 3);
   assert(vec_capacity_int(vec) > 0);

   val = 69;
   vec_insert_int(vec, 2, val);
   val = 23432;
   vec_remove_int(vec, 2, &val);
   assert(val == 69);

   vec_printf_int("%d", vec);

   vec_Vector_int *vec2 = vec_new_int();
   val = 0;
   vec_push_int(vec2, val);
   val = 1;
   vec_push_int(vec2, val);
   val = 2;
   vec_push_int(vec2, val);
   val = 3;
   vec_push_int(vec2, val);
   size_t len = vec_len_int(vec);
   vec_append_int(vec, vec2);
   assert(vec_len_int(vec) == vec_len_int(vec2) + len);

   vec_free_int(vec2);
   vec_free_int(vec);
   puts("Primitive type test passed");
}

typedef struct {
   float gravity;
   int year;
   char *name;
} TestStruct;

#define VEC_ITEM_TYPE TestStruct
#define VEC_SUFFIX teststruct
#include "vector.h"

void test_struct(void) {

   vec_Vector_teststruct *vec = vec_new_teststruct();
   assert(vec_is_empty_teststruct(vec) == true);
   assert(vec_len_teststruct(vec) == 0);
   assert(vec_capacity_teststruct(vec) == 0);

   vec_push_teststruct(vec,
       (TestStruct) {
           .name = "vector",
           .gravity = 9.8,
           .year = 2222,
       });

   assert(vec_capacity_teststruct(vec) == sizeof(TestStruct));
   vec_push_teststruct(vec,
       (TestStruct) {
           .name = "vector",
           .gravity = 9.8,
           .year = 2222,
       });
   vec_push_teststruct(vec,
       (TestStruct) {
           .name = "vector",
           .gravity = 9.8,
           .year = 2222,
       });
   assert(vec_len_teststruct(vec) == 3);

   TestStruct val;
   vec_pop_teststruct(vec, &val);
   assert(vec_len_teststruct(vec) == 2);
   assert(val.year == 2222);
   assert(strcmp(val.name, "vector") == 0);

   vec_free_teststruct(vec);
   puts("Struct test passed");
}

int main(void) {
   test_int();
   test_struct();
   return 0;
}
