#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static int money = 1000;

void* Thread_f(void *arg)
{
	int limit = *((int *) arg);
	int result = 0;

	for(int i=0; i<limit; i++)
	{
		result = money;
		result--;
		money = result;
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	pthread_t t1, t2;
	int limit, s;

	limit = atoi(argv[1]);

	s = pthread_create(&t1, NULL, Thread_f, &limit);
	if(s!=0)
	{
		perror("pthread create");
	}
	
	s = pthread_create(&t2, NULL, Thread_f, &limit);
	if(s!=0)
	{
		perror("pthread create");
	}

	s = pthread_join(t1, NULL);
	if(s!=0)
	{
		perror("pthread_join");
	}

	s = pthread_join(t1, NULL);
	if(s!=0)
	{
		perror("pthread_join");
	}

	printf("%d\n",money);
	return 0;

}
