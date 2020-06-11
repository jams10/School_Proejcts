#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

#define BUF_SIZE 32

static int isFound = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_func(void *);

int main(int argc, char** argv) {
 
  int n_thread = atoi(argv[1]);
  
  FILE **fps;
  fps = malloc(sizeof(FILE*)*n_thread);
  
  pthread_t *tid = malloc( n_thread * sizeof(pthread_t) );

  for(int i=0; i<n_thread; i++)
  {
    fps[i] = fopen("30eng.txt","r");
    fseek(fps[i], i*6*10, SEEK_SET);
    pthread_create( &tid[i], NULL, &thread_func, fps[i] );
  }
  
  for(int i=0; i<n_thread; i++)
  {
    pthread_join( tid[i], NULL );
  }

  if(isFound) printf("FOUND\n");

  for(int i = 0; i<n_thread; i++)
  {
    fclose(fps[i]);
  }
}

void *thread_func(void *arg)
{
  FILE *fp = ((FILE*)(arg));

  pid_t pid;            // process id
  pthread_t tid;        // thread id
 
  pid = getpid();
  tid = pthread_self();
  
  char buf[BUF_SIZE];
  for(int i=0; i<10; i++)
  {
    if(isFound) break;
    fgets(buf, sizeof(buf), fp);
    if(strcmp(buf,"never\n") == 0)
    {
      fprintf(stderr, "found : %s ", buf); 
      pthread_mutex_lock(&mutex);
      isFound=1;
      pthread_mutex_lock(&mutex);
    }
    printf("[pid] : %u [tid] : %x %s Found : %d\n",(unsigned int)pid, (unsigned int)tid, buf, isFound);
  }

  return NULL;
}
