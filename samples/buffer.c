#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_queue.h"

#define COMMAND_EXIT -1
#define COMMAND_REPORT -2

#define COMMAND_ADD 1
#define COMMAND_REST 2
#define COMMAND_TIMES 3
#define COMMAND_DIV 4

#define COMMANDS_LEN 4

int command_data[] = {3, 1, 5, 2};
int command_codes[] = {COMMAND_ADD, COMMAND_REST, COMMAND_TIMES, COMMAND_DIV};

struct command
{
	int command;
	int data;
};

struct command_interface
{
	struct array_queue *command_buffer;
	pthread_mutex_t *muttex;
};

void wait_response(struct command_interface *interface, int *result)
{
	int command = 0;
	while (command != COMMAND_REPORT) {
		pthread_mutex_lock(interface->muttex);
		if (!array_queue_empty(interface->command_buffer)) {
			struct command *cmd = array_queue_front(interface->command_buffer);
			command = cmd->command;
			if (command == COMMAND_REPORT)
				*result = cmd->data;
		}
		pthread_mutex_unlock(interface->muttex);
	}
}

void send_command(struct command_interface *interface, int command, int data)
{
	pthread_mutex_lock(interface->muttex);
	struct command *cmd = malloc(sizeof(struct command));
	cmd->command = command;
	cmd->data = data;
	array_queue_enqueue(interface->command_buffer, cmd);
	pthread_mutex_unlock(interface->muttex);
}

void *dispatcher(void *info)
{
	struct command_interface *interface = (struct command_interface *)info;
	int command = 0;
	int data = 0;
	int *result = malloc(sizeof(int));

	for (int i = 0; i < COMMANDS_LEN; i++)
		send_command(interface, command_codes[i], command_data[i]);
	send_command(interface, COMMAND_EXIT, 0);
	wait_response(interface, result);

	return result;
}

int execute(int command, int data1, int data2)
{
	if (command == COMMAND_ADD) return data1 + data2;
	if (command == COMMAND_REST) return data1 - data2;
	if (command == COMMAND_TIMES) return data1 * data2;
	if (command == COMMAND_DIV) return data1 / data2;
	return data1;
}

void read_command(struct command_interface *interface, int *command, int *data)
{
	struct command *cmd = NULL;
	while (!cmd){
		pthread_mutex_lock(interface->muttex);
		if (!array_queue_empty(interface->command_buffer)) {
			cmd = array_queue_dequeue(interface->command_buffer);
			*command = cmd->command;
			*data = cmd->data;
			free(cmd);
		}
		pthread_mutex_unlock(interface->muttex);
	}
}

void *worker(void *info)
{
	struct command_interface *interface = (struct command_interface *)info;
	int command = 0;
	int data = 0;
	int result = 0;
	while(command != COMMAND_EXIT) {
		read_command(interface, &command, &data);
		result = execute(command, result, data);
	}
	send_command(interface, COMMAND_REPORT, result);
	return NULL;
}

int main(void)
{
	struct command_interface *interface = malloc(sizeof(struct command_interface));
	interface->command_buffer = array_queue_init(10);
	interface->muttex = malloc(sizeof(pthread_mutex_t));
	pthread_t producer, consumer;
	int ret;
	int *result = NULL;

	pthread_mutex_init(interface->muttex, NULL);
	ret = pthread_create(&producer, NULL, &dispatcher, interface);
	if (ret) {
		return -1;
	}
	ret = pthread_create(&consumer, NULL, &worker, interface);
	if (ret) {
		return -1;
	}

	pthread_join(consumer, NULL);
	pthread_join(producer, (void **)&result);
	printf("result %d \n", *result);

	pthread_mutex_destroy(interface->muttex);
	array_queue_free(&interface->command_buffer);
	free(interface->muttex);
	free(interface);
	free(result);
	return 0;
}
