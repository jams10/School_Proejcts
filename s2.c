#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <wchar.h>
#include <locale.h>

#define MAX_SERVICE_SOCKETS 5
#define MAX_BUF 512

#define filename "EK57873.txt"
/* Text file is from http://www.114pda.com/language/dic-data/dic-ek-57873.htm */
FILE* fp;

void* service( void* arg );
void search( char* word, char msg[] );

int doing_service_sockets = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main( int argc, char** argv )
{
    setlocale(LC_ALL,"");

    if( argc != 2 )
    {
        printf( "Usage : %s [port]\n", argv[0] );
        return 1;
    }

    /* open file */
    if( (fp = fopen( filename, "r" )) == NULL )
    {
	printf("ERROR : Can't open a file.\n");
        return(-1);
    }
    
    struct sockaddr_in serv_addr, client_addr;
    int client_addr_len = sizeof( client_addr );
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons( atoi( argv[1] ) );
	
    int server_sock, service_sock;
    pthread_t service_threads[MAX_SERVICE_SOCKETS];
    
    // Socket()
    if( (server_sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP )) < 0 )
    {
        printf( "ERROR : Can't create a socket.\n" );
        exit(1);
    }
    /*
    int on = 1;
    if( setsockopt( server_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof( on ) ) < 0 )
    {
        printf( "socket option set error\n" );
        return -1;
    }
    */
    
    // Bind()
    if( bind( server_sock, (struct sockaddr*)&server_addr, sizeof( server_addr ) ) < 0 )
    {
        printf( "ERROR : Can't bind a socket.\n" );
        exit(1);
    }
    
    // Listen()
    if( listen( server_sock, 5 ) < 0 )
    {
        printf( "ERROR : Can't listen a client socket.\n" );
        exit(1);
    }
    
    // Accpet() and provice a service to the clinet.
    while( 1 )
    {
        printf( "Waiting for a client connection request...\n" );

        service_sock = accept( server_sock, (struct sockaddr*)&client_addr, (socklen_t*)&client_addr_size );
        
	if( service_sock < 0 )
        {
            printf( "ERROR : Can't accpet client's request.\n" );
        }

        if( doing_service_sockets == MAX_SERVICE_SOCKETS )
        {
            printf( "Can't accpet your request. The maximumm number of service sockets is %d\n", MAX_SERVICE_SOCKETS );
            close( service_sock );
            continue;
        }

        if( pthread_create( &thread_client[doing_service_sockets++], NULL, &service, (void*)&service_sock ) != 0 )
        {
            printf( "ERROR : Can't create a thread.\n" );
            close( service_sock );
            continue;
        }
	// edited : service -> &service
        //client_index++;

        printf( "(Addr: %s, Port: %d)\n", inet_ntoa( client_addr.sin_addr ), ntohs( client_addr.sin_port ) );

    }

    fclose( fp );
    close( service_sock );

    return 0;

}

void* t_function( void* arg )
{
    int service_sock = *((int*)arg);
    pid_t pid = getpid();      // process id
    pthread_t tid = pthread_self();  // thread id

    printf( "pid:%u, tid:%x\n", (unsigned int)pid, (unsigned int)tid );

    char buf[MAX_BUF];
    //char buf_out[BUF_SIZE];

    while( 1 )
    {
        memset( buf, 0, sizeof( buf ) );
        
	if( read( service_sock, buf, sizeof( buf ) ) <= 0 )
        {
            printf( "Close service socket (number : %d)\n", service_sock);
	    
	    pthread_mutex_lock( &mutex );
            doing_service_sockets--;
	    pthread_mutex_unlock( &mutex );
            
            close( service_sock );
            break;
        }

        printf( "From client : %s\n", buf );
        search( buf, buf );

        if( write( service_sock, buf, sizeof( buf ) ) <= 0 )
        {
            printf( "Close service socket (number : %d)\n", service_sock);
            
	    pthread_mutex_lock( &mutex );
	    client_index--;
	    pthread_mutex_unlock( &mutex );
            
	    close( service_sock );
            break;
        }
	//memset(buf_out, 0x00, sizeof(buf_out));
        printf( "To client : %s\n", buf );
    }

}

void search( char* word, char msg[] )
{
    char temp[256];
    int isIn = 0;

    strcat( word, " ///" );

    pthread_mutex_lock( &mutex );
	
    while( fgets( temp, 256, fp ) != NULL )
    {
        if( (strstr( temp, word )) != NULL )
        {
            if( strncmp( temp, word, strlen( word ) ) == 0 && temp[0] == word[0] )
            {
                strcpy( msg, temp );
                isIn = 1;
            }
        }
    }
    rewind( fp ); // Move the file pointer to the start point.
    if(isIn = 0)
    {
	    strcpy( msg, "There is no word.\n" );
    }
	
    pthread_mutex_unlock( &mutex );
}
