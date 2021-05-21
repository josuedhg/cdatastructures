CC := gcc
CFLAGS := -g -Wall -DUNIT_TESTING=ON
TESTS_OBJS := tests.o
OBJS := array_stack.o $(TESTS_OBJS)


%.o: %.c
	@echo "CC $^    ->    $@"
	@$(CC) $(CFLAGS) -c -o $@ $^

all: $(OBJS)
	$(CC) -lcmocka -o tests $^

.PHONY: clean
clean:
	rm -f $(OBJS) tests
