#include <sys/types.h>
#include <sys/times.h>
#include <stdio.h>
#include <pthread.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_NUMBER 1000
#define MAX_THREADS 10000
#define CLK_TCK sysconf(_SC_CLK_TCK)

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void* arg);
static unsigned int shared_Value = 0;
static unsigned int n_Threads;

int main(int argc, char** argv)
{
  n_Threads = atoi(argv[1]);

  pthread_t tid[MAX_THREADS];

  time_t t0;
  struct tms mytms;
  clock_t t1, t2;

  if ((t1 = times(&mytms)) == -1) 
  {
    perror("times 1");
    exit(1);
  }

  for(int i=0; i<n_Threads; i++)
  {
    if(pthread_create(&tid[i], NULL, &thread_func, NULL) !=0 )
    {
      fprintf(stderr, "pthread_create error!\n");
      fprintf(stderr, "%s\n",strerror(errno));
      exit(1);
    }
  }

  for(int i=0; i<n_Threads; i++)
  {
    pthread_join(tid[i], NULL);
  }
  
  if ((t2 = times(&mytms)) == -1) 
  {
    perror("times 2");
    exit(1);
  }

  fprintf( stdout, "%d의 약수의 개수 %d \n", MAX_NUMBER, shared_Value );

  printf("Real time : %.5f sec\n", (double)(t2 - t1) / CLK_TCK);
  printf("User time : %.5f sec\n", (double)mytms.tms_utime / CLK_TCK); 
  printf("System time : %.5f sec\n", (double)mytms.tms_stime / CLK_TCK); 

  return 0;
}

void* thread_func(void* arg)
{
  int count = 0;
  pthread_mutex_lock((&mutex));

  for( int i = 1; i <= MAX_NUMBER; i++ )
  {
      if( MAX_NUMBER % i == 0 )
      {
        count++;
      }
  }
  shared_Value = count;

  pthread_mutex_unlock((&mutex));
  
  return NULL;
}

/* 
스레드가 많아질수록 오히려 시간이 더 오래걸림. 
추측하기로, 작업 중 스레드가 계속 바뀔경우, mutex lock, unlock에 대한 시간.
그리고, pthread_create을 통한 스레드 생성시의 시간이 작업시간 보다 커서 그러지 않을까 싶음.
*/

/*
추가 사항 : 쓰레드 함수에서 연산의 범위를 100000개, 쓰레드 개수를 100개 이상으로 설정시, 
pthread_create에서 resource temporarily unavailable 발생함.
이는, 다수의 쓰레드가 1부터 100000까지 연산을 수행하면서 join 되지 않고 계속 쌓이게 되고
자원 공간이 꽉 차서 resource 관련 에러가 나지 않나 싶음.
*/
