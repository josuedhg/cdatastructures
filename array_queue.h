#ifndef __ARRAY_QUEUE_H__
#define __ARRAY_QUEUE_H__

struct array_queue;

struct array_queue *array_queue_init(int queue_size);
int array_queue_enqueue(struct array_queue *queue, void *item);
void *array_queue_dequeue(struct array_queue *queue);
void *array_queue_front(struct array_queue *queue);
void *array_queue_rear(struct array_queue *queue);
int array_queue_empty(struct array_queue *queue);
void array_queue_free(struct array_queue **queue);

#endif
