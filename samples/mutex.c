#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>

#include "singly_linked_list.h"

struct mutex {
	atomic_flag internal_lock;
	atomic_flag external_lock;
	struct singly_linked_list *waiters;
};

struct mutex *mutex_init()
{
	struct mutex *mutex = (struct mutex *)calloc(1, sizeof(struct mutex));
	atomic_flag_clear(&mutex->internal_lock);
	atomic_flag_clear(&mutex->external_lock);
	mutex->waiters = singly_linked_list_init();
	return mutex;
}

static void mutex_internal_lock(struct mutex *mutex)
{
	while(atomic_flag_test_and_set(&mutex->internal_lock));
}

static void mutex_internal_unlock(struct mutex *mutex)
{
	atomic_flag_clear(&mutex->internal_lock);
}

void mutex_lock(struct mutex *mutex)
{
	pthread_t tid = pthread_self();
	mutex_internal_lock(mutex);
	singly_linked_list_append(mutex->waiters, &tid);
	mutex_internal_unlock(mutex);

	while(1) {
		while(atomic_flag_test_and_set(&mutex->external_lock));
		mutex_internal_lock(mutex);
		struct singly_linked_node * node = singly_linked_list_get_head(mutex->waiters);
		pthread_t *tid_head = singly_linked_node_get_data(node);
		if (&tid == tid_head) {
			mutex_internal_unlock(mutex);
			break;
		}
		atomic_flag_clear(&mutex->external_lock);
		mutex_internal_unlock(mutex);
	}
}

void mutex_unlock(struct mutex *mutex)
{
	mutex_internal_lock(mutex);
	singly_linked_list_delete_first(mutex->waiters);
	mutex_internal_unlock(mutex);
	atomic_flag_clear(&mutex->external_lock);
}

void mutex_free(struct mutex **mutex)
{
	singly_linked_list_free_nodes((*mutex)->waiters);
	singly_linked_list_free(&(*mutex)->waiters);
	free(*mutex);
	*mutex = NULL;
}
