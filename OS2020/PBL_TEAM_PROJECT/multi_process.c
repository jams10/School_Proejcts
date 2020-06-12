#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/times.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <semaphore.h>
#include <string.h>      
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 32 // 공유 메모리 크기
#define SHM_KEY 0x1234 // 공유 메모리 키

#define MAX_NUMBER 1000
#define MAX_PROCESS 10000
#define CLK_TCK sysconf(_SC_CLK_TCK)

int main( int argc, char** argv )
{
    int n_Process = atoi( argv[1] ); // 생성 프로세스 개수

    int shmid; // 공유 메모리 id
    int* shmaddr; // 공유 메모리
    sem_t* sem; // 공유 세마포어
    unsigned int value = 1; // 세마포어 값
    pid_t pids[MAX_PROCESS]; // fork한 프로세스 아이디

    /* Time setup */
    time_t t0;
    struct tms mytms;
    clock_t t1, t2;

    /* 시간 측정 시작 */
    if( (t1 = times( &mytms )) == -1 )
    {
        perror( "times 1" );
        exit( 1 );
    }

    shmid = shmget( SHM_KEY, BUFSIZ, IPC_CREAT | 0644 ); // 공유 메모리 생성
    if( shmid == -1 )
    {
        perror( "shmget" );
        exit( 1 );
    }

    shmaddr = (int*)shmat( shmid, (int*)NULL, 0 ); // 공유 메모리 연결
    
    shmaddr[0] = 0;

    /* 세마포어 초기화 */
    sem = sem_open( "pSem", O_CREAT | O_EXCL, 0644, value ); // 해당 세마포어는 pSem 이름으로 접근 가능함.

    /* fork child processes */
    for( int i = 0; i < n_Process; i++ )
    {
        if ((pids[i] = fork()) < 0)
        {
            /* pid가 0보다 작으면 fork 실패 */
            sem_unlink( "pSem" ); // 세마포어 링크 해제   
            sem_close( sem ); // 세마포어 닫기
            //fprintf( stderr, "Fork() error.\n" );
            printf("problem with fork() in pid %d error %s!!! \n",
            (int) getpid(), strerror(errno));
        }
        else if(pids[i] == 0)
        {
            int count = 0;
            sem_wait( sem ); // 세마포어 획득 
            for( int i = 1; i <= MAX_NUMBER; i++ )
            {
                if( MAX_NUMBER % i == 0 )
                {
                    count++;
                }
            }
            shmaddr[0] = count;
            sem_post( sem ); // 세마포어 반납    
            exit( 0 );
        }
        int status;
        pid_t pid;
        pid = wait(&status);
    }

    fprintf( stdout, "%d의 약수의 개수 %d \n", MAX_NUMBER, shmaddr[0] );

    if( (t2 = times( &mytms )) == -1 )
    {
      perror( "times 2" );
      exit( 1 );
    }

    printf( "Real time : %.5f sec\n", (double)(t2 - t1) / CLK_TCK );
    printf( "User time : %.5f sec\n", (double)mytms.tms_utime / CLK_TCK );
    printf( "System time : %.5f sec\n", (double)mytms.tms_stime / CLK_TCK );

    /* 공유 메모리 해제 */
    shmdt( shmaddr );
    shmctl( shmid, IPC_RMID, 0 );

    sem_unlink( "pSem" ); // 세마포어 링크 해제     
    sem_close( sem ); // 세마포어 닫기

    exit( 0 );

}

/* Referene */
// https://12bme.tistory.com/227
// https://awesomebit.tistory.com/19
// https://stackoverflow.com/questions/16400820/how-to-use-posix-semaphores-on-forked-processes-in-c
// https://www.joinc.co.kr/w/man/2/waitpid
// https://stackoverflow.com/questions/876605/multiple-child-process

/*
추가 사항 
86~88번줄에서 wait으로 자식 프로세스가 종료되기를 기다리는데, 이를 for문 밖으로 꺼낼 경우,
자식 프로세스가 끝났음에도 변경 상태를 회수해 가지 않아서 프로세스 슬롯을 차지하게 됨. (쫌비 프로세스)
그래서 종료 되었음에도 자원을 소비하여 fork 시에 resource 관련 에러가 생김.
따라서, 자식 프로세스가 exit(0)으로 종료되자마자 회수하여 이를 방지함.

참고 내역 : https://stackoverflow.com/questions/28140355/c-fork-resource-temporarily-unavailable-on-tcp-server
*/
