#include <stdlib.h>
#include <assert.h>

#include "array_queue.h"

struct array_queue
{
	void **buffer;
	int buffer_len;
	int front;
	int rear;
	int amount;
};

struct array_queue *array_queue_init(int queue_size)
{
	struct array_queue *queue = (struct array_queue *)malloc(sizeof(struct array_queue));
	queue->buffer = calloc(queue_size, sizeof(void *));
	queue->buffer_len = queue_size;
	queue->front = 0;
	queue->rear = 0;
	queue->amount = 0;
	return queue;
}

int array_queue_enqueue(struct array_queue *queue, void *item)
{
	if (queue->amount >= queue->buffer_len)
		return -1;
	queue->buffer[(queue->front++)%queue->buffer_len] = item;
	queue->amount++;
	return 0;
}

void *array_queue_dequeue(struct array_queue *queue)
{
	if (array_queue_empty(queue))
		return NULL;
	queue->amount--;
	return queue->buffer[(queue->rear++)%queue->buffer_len];
}

void *array_queue_front(struct array_queue *queue)
{
	if (array_queue_empty(queue))
		return NULL;
	return queue->buffer[queue->front];
}

void *array_queue_rear(struct array_queue *queue)
{
	if (array_queue_empty(queue))
		return NULL;
	return queue->buffer[queue->rear];
}

int array_queue_empty(struct array_queue *queue)
{
	return queue->amount == 0;
}

void array_queue_free(struct array_queue **queue)
{
	if (*queue == NULL)return;
	free((*queue)->buffer);
	free(*queue);
}
