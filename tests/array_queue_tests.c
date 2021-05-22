#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "array_queue.h"
#include "array_queue_tests.h"

void array_queue(void **state)
{
	struct array_queue *queue = array_queue_init(3);
	array_queue_enqueue(queue, (void*)3);
	assert_int_equal(array_queue_rear(queue), 3);
	array_queue_enqueue(queue, (void*)4);
	assert_int_equal(array_queue_rear(queue), 4);
	array_queue_enqueue(queue, (void*)5);
	assert_int_equal(array_queue_rear(queue), 5);
	
	assert_int_equal(array_queue_dequeue(queue), 3);
	assert_int_equal(array_queue_dequeue(queue), 4);
	assert_int_equal(array_queue_dequeue(queue), 5);

	assert_true(array_queue_empty(queue));

	array_queue_free(&queue);
	assert_null(queue);
}

void array_queue_overflow(void **state)
{
	struct array_queue *queue = array_queue_init(3);
	assert_int_equal(array_queue_enqueue(queue, (void*)3), 0);
	assert_int_equal(array_queue_enqueue(queue, (void*)4), 0);
	assert_int_equal(array_queue_enqueue(queue, (void*)5), 0);
	assert_int_not_equal(array_queue_enqueue(queue, (void*)6), 0);
	array_queue_free(&queue);
}

void array_queue_underflow(void **state)
{
	struct array_queue *queue = array_queue_init(1);
	assert_null(array_queue_dequeue(queue));
	array_queue_free(&queue);
}

void array_queue_uninitialized(void **state)
{
	struct array_queue *queue = NULL;
	expect_assert_failure(array_queue_dequeue(queue));
	expect_assert_failure(array_queue_enqueue(queue, NULL));
	expect_assert_failure(array_queue_front(queue));
	expect_assert_failure(array_queue_rear(queue));
	expect_assert_failure(array_queue_empty(queue));
}
