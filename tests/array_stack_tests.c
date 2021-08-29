#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "array_stack.h"

void array_stack(void **state)
{
	struct array_stack *stack = array_stack_init(3);
	array_stack_push(stack, (void*)3);
	assert_int_equal(array_stack_peek(stack), 3);
	array_stack_push(stack, (void*)4);
	assert_int_equal(array_stack_peek(stack), 4);
	array_stack_push(stack, (void*)5);
	assert_int_equal(array_stack_peek(stack), 5);

	assert_int_equal(array_stack_pop(stack), 5);
	assert_int_equal(array_stack_pop(stack), 4);
	assert_int_equal(array_stack_pop(stack), 3);

	assert_true(array_stack_empty(stack));

	array_stack_free(&stack);
	assert_null(stack);
}

void array_stack_overflow(void **state)
{
	struct array_stack *stack = array_stack_init(3);
	assert_int_equal(array_stack_push(stack, (void*)3), 0);
	assert_int_equal(array_stack_push(stack, (void*)4), 0);
	assert_int_equal(array_stack_push(stack, (void*)5), 0);
	assert_int_not_equal(array_stack_push(stack, (void*)6), 0);
	array_stack_free(&stack);
}

void array_stack_underflow(void **state)
{
	struct array_stack *stack = array_stack_init(1);
	assert_null(array_stack_pop(stack));
	array_stack_free(&stack);
}

void array_stack_uninitialized(void **state)
{
	struct array_stack *stack = NULL;
	expect_assert_failure(array_stack_pop(stack));
	expect_assert_failure(array_stack_push(stack, NULL));
	expect_assert_failure(array_stack_peek(stack));
	expect_assert_failure(array_stack_empty(stack));
}

int main()
{
	const struct CMUnitTest tests[] = {
		// array_stack tests
		cmocka_unit_test(array_stack),
		cmocka_unit_test(array_stack_overflow),
		cmocka_unit_test(array_stack_underflow),
		cmocka_unit_test(array_stack_uninitialized),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
