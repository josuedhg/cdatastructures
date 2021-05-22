#ifndef __ARRAY_STACK_H__
#define __ARRAY_STACK_H__

struct array_stack;

struct array_stack * array_stack_init(int stack_size);
void *array_stack_pop(struct array_stack *stack);
int array_stack_push(struct array_stack *stack, void *item);
void *array_stack_peek(struct array_stack *stack);
int array_stack_empty(struct array_stack *stack);
void array_stack_free(struct array_stack **stack);

#endif
