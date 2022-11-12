#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

STACK_INIT(int)
STACK_INIT(float)
STACK_INIT(char)

typedef struct test
{
    int x;
    int y;
    char z;
    char *msg;
} test_t;

STACK_INIT(test_t)

#define _assert(expr) \
    assert(expr);     \
    printf("Test: %s (passed)\n", #expr);

int main(void)
{
    // Testing Ints
    Stack_int *sint = stack_new_int();
    stack_push_int(sint, 1);
    assert(stack_size_int(sint) == 1);
    stack_push_int(sint, 2);
    assert(stack_size_int(sint) == 2);
    stack_push_int(sint, 3);
    assert(stack_size_int(sint) == 3);
    stack_push_int(sint, 4);
    _assert(stack_size_int(sint) == 4);

    assert(stack_pop_int(sint) == 4);
    assert(stack_pop_int(sint) == 3);
    assert(stack_pop_int(sint) == 2);
    _assert(stack_pop_int(sint) == 1);
    _assert(stack_size_int(sint) == 0);

    stack_free_int(sint);

    // Testing Floats
    Stack_float *sfloat = stack_new_float();
    stack_push_float(sfloat, 1);
    assert(stack_size_float(sfloat) == 1);
    stack_push_float(sfloat, 2);
    assert(stack_size_float(sfloat) == 2);
    stack_push_float(sfloat, 3);
    assert(stack_size_float(sfloat) == 3);
    stack_push_float(sfloat, 4);
    _assert(stack_size_float(sfloat) == 4);

    assert(stack_pop_float(sfloat) == 4);
    assert(stack_pop_float(sfloat) == 3);
    assert(stack_pop_float(sfloat) == 2);
    _assert(stack_pop_float(sfloat) == 1);
    _assert(stack_size_float(sfloat) == 0);

    stack_free_float(sfloat);

    // Testing chars
    Stack_char *schar = stack_new_char();
    stack_push_char(schar, 1);
    assert(stack_size_char(schar) == 1);
    stack_push_char(schar, 2);
    assert(stack_size_char(schar) == 2);
    stack_push_char(schar, 3);
    assert(stack_size_char(schar) == 3);
    stack_push_char(schar, 4);
    _assert(stack_size_char(schar) == 4);

    assert(stack_pop_char(schar) == 4);
    assert(stack_pop_char(schar) == 3);
    assert(stack_pop_char(schar) == 2);
    _assert(stack_pop_char(schar) == 1);
    _assert(stack_size_char(schar) == 0);

    stack_free_char(schar);

    // testing structs
    Stack_test_t *stest_t = stack_new_test_t();
    stack_push_test_t(stest_t, (test_t){
                                   .x = 1,
                                   .y = 2,
                                   .z = 'a',
                                   .msg = "test"});
    assert(stack_size_test_t(stest_t) == 1);
    stack_push_test_t(stest_t, (test_t){
                                   .x = 1,
                                   .y = 2,
                                   .z = 'a'});
    assert(stack_size_test_t(stest_t) == 2);
    stack_push_test_t(stest_t, (test_t){
                                   .x = 1,
                                   .y = 2,
                                   .z = 'a'});
    assert(stack_size_test_t(stest_t) == 3);
    stack_push_test_t(stest_t, (test_t){
                                   .x = 1,
                                   .y = 2,
                                   .z = 'a'});
    _assert(stack_size_test_t(stest_t) == 4);

    assert(stack_pop_test_t(stest_t).x == 1);
    assert(stack_pop_test_t(stest_t).y == 2);
    assert(stack_pop_test_t(stest_t).z == 'a');
    _assert(strcmp(stack_pop_test_t(stest_t).msg, "test") == 0);

    stack_free_test_t(stest_t);
    return 0;
}