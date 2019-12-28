#ifndef T_FUNCS
#define T_FUNCS
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#define VERYBIG 200

typedef struct fileinfo{
        int turn;
	FILE *ori;
	FILE *spo;
	FILE *ent;
	FILE *soc;
} fileinfo;

extern fileinfo file;
extern pthread_mutex_t rlock;
extern pthread_cond_t cons;

void* thread_ori(void *arg);
void* thread_spo(void *arg);
void* thread_ent(void *arg);
void* thread_soc(void* arg);

#endif
