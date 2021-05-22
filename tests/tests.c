#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "array_stack_tests.h"

int main()
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(array_stack),
		cmocka_unit_test(array_stack_overflow),
		cmocka_unit_test(array_stack_underflow),
		cmocka_unit_test(array_stack_uninitialized),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
