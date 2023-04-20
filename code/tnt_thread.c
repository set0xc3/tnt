#include "tnt_thread.h"
#include "tnt_logger.h"

#include <pthread.h>

#define THREAD_STATUS_SUCCESS 0

struct thread_info 
{
  pthread_t thread_id;
  i32       thread_num;
  char     *argv_string;
};

u64 os_thread_create(Function func)
{
	i32 status = -1;
	pthread_t thread_id = 0;
	status = pthread_create(&thread_id, 0, func, 0);
	if (status != THREAD_STATUS_SUCCESS) {
		LOG_ERROR("[OS] Failed create thread: %i", status);
	}

	// status = pthread_join(thread_id, 0);
	status = pthread_detach(thread_id);
	if (status != THREAD_STATUS_SUCCESS) {
		LOG_ERROR("[OS] Failed join thread: %i", status);
	}

	return thread_id;
}
