#include <stdlib.h>
#include <assert.h>

#include "array_stack.h"

#define EMPTY_VAL -1

#ifdef UNIT_TESTING
extern void mock_assert(const int result, const char* const expression,
                        const char * const file, const int line);
#undef assert
#define assert(expression) \
    mock_assert((int)(expression), #expression, __FILE__, __LINE__);
#endif

struct array_stack
{
	void **buffer;
	int buffer_len;
	unsigned int stack_top;
};

struct array_stack * array_stack_init(int stack_size)
{
	struct array_stack *stack = (struct array_stack *)malloc(sizeof(struct array_stack));
	stack->buffer = calloc(stack_size, sizeof(void *));
	stack->buffer_len = stack_size;
	stack->stack_top = EMPTY_VAL;
	return stack;
}

void *array_stack_pop(struct array_stack *stack)
{
	assert(stack != NULL);
	if (stack->stack_top == EMPTY_VAL)
		return NULL;
	return stack->buffer[stack->stack_top--];
}

int array_stack_push(struct array_stack *stack, void *item)
{
	assert(stack != NULL);
	if ((stack->stack_top + 1) >= stack->buffer_len)
		return -1;
	stack->buffer[++stack->stack_top] = item;
	return 0;
}

void *array_stack_peek(struct array_stack *stack)
{
	assert(stack != NULL);
	return stack->buffer[stack->stack_top];
}

int array_stack_empty(struct array_stack *stack)
{
	assert(stack != NULL);
	return stack->stack_top == EMPTY_VAL;
}

void array_stack_free(struct array_stack **stack)
{
	if (*stack == NULL) return;
	free((*stack)->buffer);
	free(*stack);
	*stack = NULL;
}
