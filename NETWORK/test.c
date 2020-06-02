#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include "words.h"
#include "players.h"

#define MAX_CLIENTS 5
#define BUFFER_SZ 2048

static _Atomic unsigned int cli_count = 0;
static int uid = 10;
static int turn = 0;
static int round = -1;
static int isStart = 0;

/* Client structure */
typedef struct
{
	struct sockaddr_in address;
	int sockfd;
	int uid;
	int turn;
	int score;
	char name[32];
} client_t;

client_t* clients[MAX_CLIENTS];

char prev_word[20];

FILE* fp;
BSTNode* root_BSTnodes[26];

List list;
LNode* tmp = NULL;

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cons = PTHREAD_COND_INITIALIZER;

void str_overwrite_stdout()
{
	printf( "\r%s", "> " );
	fflush( stdout );
}

void str_trim_lf( char* arr, int length )
{
	int i;
	for( i = 0; i < length; i++ )
	{ // trim \n
		if( arr[i] == '\n' )
		{
			arr[i] = '\0';
			break;
		}
	}
}

void print_client_addr( struct sockaddr_in addr )
{
	printf( "%d.%d.%d.%d",
		addr.sin_addr.s_addr & 0xff,
		(addr.sin_addr.s_addr & 0xff00) >> 8,
		(addr.sin_addr.s_addr & 0xff0000) >> 16,
		(addr.sin_addr.s_addr & 0xff000000) >> 24 );
}

/* Add clients to queue */
void queue_add( client_t* cl )
{
	pthread_mutex_lock( &clients_mutex );

	for( int i = 0; i < MAX_CLIENTS; ++i )
	{
		if( !clients[i] )
		{
			clients[i] = cl;
			break;
		}
	}

	pthread_mutex_unlock( &clients_mutex );
}

/* Remove clients to queue */
void queue_remove( int uid )
{
	pthread_mutex_lock( &clients_mutex );

	for( int i = 0; i < MAX_CLIENTS; ++i )
	{
		if( clients[i] )
		{
			if( clients[i]->uid == uid )
			{
				clients[i] = NULL;
				break;
			}
		}
	}

	pthread_mutex_unlock( &clients_mutex );
}

/* Send message to all clients except sender */
void send_message( char* s, int uid )
{
	//pthread_mutex_lock( &clients_mutex );

	for( int i = 0; i < MAX_CLIENTS; ++i )
	{
		if( clients[i] )
		{
			//if( clients[i]->uid != uid )
			//{
				if( write( clients[i]->sockfd, s, strlen( s ) ) < 0 )
				{
					perror( "ERROR: write to descriptor failed" );
					break;
				}
			//}
		}
	}

	//pthread_mutex_unlock( &clients_mutex );
}

void change_prev_word(char*s)
{
	strcpy(prev_word, s);
}

int valid_check(char* buf)
{
	if(prev_word != buf)
	{
		if(prev_word[strlen(prev_word) - 1] == buf[0])
		{
			if(!isWordIn(list.head, buf))
			{
				if(search(root_BSTnodes[buf[0]-97], buf))
				{
					tmp = createLNode(buf);
					insertLNode(&list.head, &list.current, tmp);
					return 1;
				}
			}
		}
	}
	return 0;
}

void freeMemory()
{
	for(int i=0; i<26; i++)
	{
		freeAllBST(root_BSTnodes[i]);
	}
	freeAllList(list.head);
}

/* Handle all communication with the client */
void* handle_client( void* arg )
{
	char buff_out[BUFFER_SZ];
	char buff_out2[BUFFER_SZ];
	char name[32];
	int leave_flag = 0;
	int isDead=0;

	cli_count++;
	
	/*	
	if( cli_count == 4 )
	{
		pthread_mutex_lock(&clients_mutex);
		round++;
		//pthread_cond_broadcast(&cons);
		pthread_mutex_unlock(&clients_mutex);
		pthread_cond_broadcast(&cons);
	}
	*/
	client_t* cli = (client_t*)arg;

	// Name
	
	if( recv( cli->sockfd, name, 32, 0 ) <= 0 || strlen( name ) < 2 || strlen( name ) >= 32 - 1 )
	{
		printf( "Didn't enter the name.\n" );
		leave_flag = 1;
	}
	else
	{
		strcpy( cli->name, name );
		sprintf( buff_out, "%s has joined\n", cli->name );
		printf( "%s", buff_out );
		send_message( buff_out, cli->uid );
	}
	if( cli_count == 4)
	{
		pthread_mutex_lock(&clients_mutex);
		round++;
		sprintf(buff_out2,"\nWord to solve : %s\n\n", prev_word);
		send_message( buff_out2, cli->uid);
		pthread_mutex_unlock(&clients_mutex);
		pthread_cond_broadcast(&cons);
	}

	bzero( buff_out, BUFFER_SZ );
	bzero( buff_out, BUFFER_SZ );
	while( 1 )
	{
		if( leave_flag )
		{
			break;
		}
		printf("player turn : %d, round : %d\n",cli->turn, round);
		
		pthread_mutex_lock( &clients_mutex );
		while( cli->turn != round )
		{
			pthread_cond_wait( &cons, &clients_mutex );
		}
		printf("%d turn : %d\n",round, cli->turn);
		
		if(isStart)
		{	
			sprintf(buff_out2,"\nWord to solve : %s\n\n", prev_word);
			send_message(buff_out2, cli->uid);
		}
		else
		{
			isStart = 1;
		}
		bzero(buff_out2, BUFFER_SZ);
		
		for(int i=0; i<MAX_CLIENTS; i++)
		{
			if(clients[i])
			{
				sprintf(buff_out,"Player: %s | score :%d\n", clients[i]->name, clients[i]->score);
				send_message(buff_out, clients[i]->uid);
				bzero(buff_out, BUFFER_SZ);
			}
		}
		sprintf(buff_out,"\n");
		send_message(buff_out, cli->uid);
		bzero(buff_out, BUFFER_SZ);
		
		sprintf(buff_out,"\nPlayer : %s turn!!\n\n",cli->name);
		send_message(buff_out, cli->uid);
		bzero(buff_out, BUFFER_SZ);

		int receive = recv( cli->sockfd, buff_out, BUFFER_SZ, 0 );
		if( receive > 0 )
		{
			if( strlen( buff_out ) > 0 )
			{
				//buff_out[strlen(buff_out)-1]='\0';
				printf("%s",buff_out);
				if(valid_check( buff_out ) )
				{
					change_prev_word( buff_out );
					sprintf( buff_out, "Player : %s typed word is Correct!\n", cli->name);
					cli->score+=10;
					send_message( buff_out, cli->uid);
				}
				else if(!valid_check(buff_out))
				{
					sprintf(buff_out, "Player : %s typed wrong word!\n", cli->name);
					send_message( buff_out, cli->uid);
				}
				/*
				send_message( buff_out, cli->uid );

				str_trim_lf( buff_out, strlen( buff_out ) );
				printf( "%s -> %s\n", buff_out, cli->name );
				*/
			}
		}
		else if( receive == 0 || strcmp( buff_out, "exit" ) == 0 )
		{
			sprintf( buff_out, "%s has left\n", cli->name );
			printf( "%s", buff_out );
			send_message( buff_out, cli->uid );
			leave_flag = 1;
		}
		else
		{
			printf( "ERROR: -1\n" );
			leave_flag = 1;
		}
		bzero( buff_out, BUFFER_SZ );
		round++;
		
		if( round == MAX_CLIENTS - 1)
		{
			round = 0;
		}
		
		pthread_cond_broadcast( &cons );
		pthread_mutex_unlock( &clients_mutex );
	}

	/* Delete client from queue and yield thread */
	close( cli->sockfd );
	queue_remove( cli->uid );
	free( cli );
	cli_count--;
	pthread_detach( pthread_self() );

	return NULL;
}

int main( int argc, char** argv )
{
	if( argc != 2 )
	{
		printf( "Usage: %s <port>\n", argv[0] );
		return EXIT_FAILURE;
	}

	if((fp=fopen("./20k.txt", "r"))==NULL)
	{
		fprintf(stderr,"File open error.\n");
		exit(1);
	}

	for(int i=0; i<26; i++)
	{
		root_BSTnodes[i] =NULL;
	}	
	store_words(fp, root_BSTnodes);
	fclose(fp);

	list.head = NULL;
	list.current = NULL;
	srand(time(NULL));
	int num=(int)(rand() % 26);
	strcpy(prev_word, root_BSTnodes[num]->word);

	char* ip = "127.0.0.1";
	int port = atoi( argv[1] );
	int option = 1;
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	pthread_t tid;

	/* Socket settings */
	listenfd = socket( AF_INET, SOCK_STREAM, 0 );
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr( ip );
	serv_addr.sin_port = htons( port );

	/* Ignore pipe signals */
	/*
	signal( SIGPIPE, SIG_IGN );

	if( setsockopt( listenfd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char*)&option, sizeof( option ) ) < 0 )
	{
		perror( "ERROR: setsockopt failed" );
		return EXIT_FAILURE;
	}
	*/
	/* Bind */
	if( bind( listenfd, (struct sockaddr*)&serv_addr, sizeof( serv_addr ) ) < 0 )
	{
		perror( "ERROR: Socket binding failed" );
		return EXIT_FAILURE;
	}

	/* Listen */
	if( listen( listenfd, 10 ) < 0 )
	{
		perror( "ERROR: Socket listening failed" );
		return EXIT_FAILURE;
	}

	printf( "=== WELCOME TO THE CHATROOM ===\n" );

	while( 1 )
	{
		socklen_t clilen = sizeof( cli_addr );
		connfd = accept( listenfd, (struct sockaddr*)&cli_addr, &clilen );

		/* Check if max clients is reached */
		if( (cli_count + 1) == MAX_CLIENTS )
		{
			printf( "Max clients reached. Rejected: " );
			print_client_addr( cli_addr );
			printf( ":%d\n", cli_addr.sin_port );
			close( connfd );
			continue;
		}

		/* Client settings */
		client_t* cli = (client_t*)malloc( sizeof( client_t ) );
		cli->address = cli_addr;
		cli->sockfd = connfd;
		cli->uid = uid++;
		cli->score = 0;
		cli->turn = turn++;
		/*
		if(turn == 4)
		{
			round = 0;
			pthread_cond_broadcast(&cons);
		}
		*/
		printf("%d\n",round);
		/* Add client to the queue and fork thread */
		queue_add( cli );
		pthread_create( &tid, NULL, &handle_client, (void*)cli );

		/* Reduce CPU usage */
		sleep( 1 );
	}
	freeMemory();
	return EXIT_SUCCESS;
}
