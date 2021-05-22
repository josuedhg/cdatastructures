#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "array_stack_tests.h"
#include "array_queue_tests.h"

int main()
{
	const struct CMUnitTest tests[] = {
		// array_stack tests
		cmocka_unit_test(array_stack),
		cmocka_unit_test(array_stack_overflow),
		cmocka_unit_test(array_stack_underflow),
		cmocka_unit_test(array_stack_uninitialized),
		// array_queue tests
		cmocka_unit_test(array_queue),
		cmocka_unit_test(array_queue_overflow),
		cmocka_unit_test(array_queue_underflow),
		cmocka_unit_test(array_queue_uninitialized),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
