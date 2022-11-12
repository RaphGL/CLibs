#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"

QUEUE_INIT(int)
QUEUE_INIT(float)
QUEUE_INIT(char)

typedef struct test
{
    int x;
    int y;
    char z;
    char *msg;
} test_t;

QUEUE_INIT(test_t)

#define _assert(expr) \
    assert(expr);     \
    printf("Test: %s (passed)\n", #expr);

int main(void)
{
    // Testing ints
    Queue_int *qint = queue_new_int(4); // maximum size is infinite if size == -1
    queue_enqueue_int(qint, 1);
    queue_enqueue_int(qint, 2);
    queue_enqueue_int(qint, 3);
    queue_enqueue_int(qint, 4);
    _assert(queue_size_int(qint) == 4);
    queue_enqueue_int(qint, 4);
    _assert(queue_size_int(qint) == 4); // it won't change once it reaches the maximum size
    _assert(queue_dequeue_int(qint) == 1);
    _assert(queue_size_int(qint) == 3);
    queue_free_int(qint);

    // Testing floats
    Queue_float *qfloat = queue_new_float(4);
    queue_enqueue_float(qfloat, 1);
    queue_enqueue_float(qfloat, 2);
    queue_enqueue_float(qfloat, 3);
    queue_enqueue_float(qfloat, 4);
    _assert(queue_size_float(qfloat) == 4);
    queue_enqueue_float(qfloat, 4);
    _assert(queue_size_float(qfloat) == 4);
    _assert(queue_dequeue_float(qfloat) == 1);
    _assert(queue_size_float(qfloat) == 3);
    queue_free_float(qfloat);

    // Testing chars
    Queue_char *qchar = queue_new_char(4);
    queue_enqueue_char(qchar, 'a');
    queue_enqueue_char(qchar, 'b');
    queue_enqueue_char(qchar, 'c');
    queue_enqueue_char(qchar, 'd');
    _assert(queue_size_char(qchar) == 4);
    queue_enqueue_char(qchar, 'e');
    _assert(queue_size_char(qchar) == 4);
    _assert(queue_dequeue_char(qchar) == 'a');
    _assert(queue_size_char(qchar) == 3);
    queue_free_char(qchar);

    // Testing struct
    test_t test = (test_t){
        .x = 1,
        .y = 2,
        .z = 3,
        .msg = "test"};
    Queue_test_t *qtest_t = queue_new_test_t(4);
    queue_enqueue_test_t(qtest_t, test);
    queue_enqueue_test_t(qtest_t, test);
    queue_enqueue_test_t(qtest_t, test);
    queue_enqueue_test_t(qtest_t, test);
    _assert(queue_size_test_t(qtest_t) == 4);
    queue_enqueue_test_t(qtest_t, test);
    _assert(queue_size_test_t(qtest_t) == 4);
    _assert(queue_dequeue_test_t(qtest_t).msg == test.msg);
    _assert(queue_size_test_t(qtest_t) == 3);
    queue_free_test_t(qtest_t);
}