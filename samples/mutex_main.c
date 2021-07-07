#include <stdio.h>
#include <pthread.h>

#include "mutex.h"

struct data {
	struct mutex *mutex;
	int data[100];
	int index;
};

void data_init(struct data *data)
{
	data->mutex = mutex_init();
	for (int i = 0; i < 100; i++) data->data[i] = i + 1;
	data->index = 0;
}

void data_deinit(struct data *data)
{
	mutex_free(&data->mutex);
}

void *thread(void *val)
{
	struct data *data = (struct data *)val;
	while(1) {
		mutex_lock(data->mutex);
		if (data->index >= 100) {
			mutex_unlock(data->mutex);
			break;
		}
		printf("%d\n", data->data[data->index++]);
		mutex_unlock(data->mutex);
	}
	return NULL;
}

int main(void)
{
	struct data data = {};
	pthread_t tid;
	pthread_t tid2;
	pthread_t tid3;
	data_init(&data);
	pthread_create(&tid, NULL, &thread, &data);
	pthread_create(&tid2, NULL, &thread, &data);
	pthread_create(&tid3, NULL, &thread, &data);
	pthread_join(tid, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);

	data_deinit(&data);
	return 0;
}
