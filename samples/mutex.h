#ifndef __MUTEX_H__
#define __MUTEX_H__

struct mutex;

struct mutex *mutex_init();
void mutex_lock(struct mutex *mutex);
void mutex_unlock(struct mutex *mutex);
void mutex_free(struct mutex **mutex);

#endif /* end of include guard: __MUTEX_H__ */
