#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

static long shared_value = 0;
static long result = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* Thread_f(void *arg)
{
	int limit = *((int *) arg);
	
	pthread_mutex_lock(&mutex);
	result = 0;
	for(int i=0; i<limit; i++)
	{
		result = shared_value;
		result--;
		shared_value = result;
		//printf("result : %ld shared_value : %ld\n", result, shared_value);
		//sleep(1);
	}
	pthread_mutex_unlock(&mutex);

	return NULL;
}

int main(int argc, char* argv[])
{
	pthread_t t1, t2;
	int limit, status;

	limit = atoi(argv[1]);

	pthread_create(&t1, NULL, Thread_f, &limit);
	pthread_create(&t2, NULL, Thread_f, &limit);

	pthread_join(t1, (void*)&status);
	pthread_join(t2, (void*)&status);

	printf("%ld\n", shared_value);
	return 0;

}
