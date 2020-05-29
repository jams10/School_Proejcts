#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include "words.h"
#include "players.h"

#define MAX_BUF 64
#define MAX_PLAYERS 4
#define IP "127.0.0.1"

static int n_Client = 0;

typedef struct Player
{
	char name[32];
	int sockfd;
	int id;
	int life;
	struct sockaddr_in address;
}Player;

char prev_word[20];

FILE* fp;
BSTNode* root_BSTnodes[26];

List list;
LNode* tmp = NULL;

int player_id = 0;
Player* players[MAX_PLAYERS];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void add_Player( Player* p );
void del_Player( int process_id );
void send_msg( char* s, int id );
void send_msg_All( char* s );
void change_prev_word( char* s );
void* service( void* arg );
int valid_check( char* buf );
void freeMemory();

void main( int argc, char* argv )
{
	if( argc != 2 )
	{
		printf( "Usage: %s <port>\n", argv[0] );
		exit( 1 );
	}

	// 게임 초기 세팅
	// 1. 단어장 파일 열어서 BST에 저장
	if( (fp = fopen( "./20k.txt", "r" )) == NULL )
	{
		fprintf( stderr, "File open error.\n" );
		exit( 1 );
	}

	for( int i = 0; i < 26; i++ )
	{
		root_BSTnodes[i] = NULL;
	}
	store_words( fp, root_BSTnodes );
	fclose( fp );

	// 2. 플레이어 입력 단어 저장할 리스트 생성
	list.head = NULL;
	list.current = NULL;

	// 3. 초기 무작위 단어 선정
	int num = (int)(rand() % 26);
	strcpy( prev_word, root_BSTnodes[num]->word );

	// 소켓 초기 세팅
	pthread_t tid;

	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;

	int n_port = atoi( argv[1] );
	int listening_socket = 0, client_socket = 0;

	// Socket()
	listening_socket = socket( AF_INET, SOCK_STREAM, 0 );
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr( ip );
	serv_addr.sin_port = htons( port );

	// Bind()
	if( bind( listening_socket, (struct sockaddr*)&serv_addr, sizeof( serv_addr ) ) < 0 )
	{
		printf( "Server : Bind error\n" );
		exit( 1 );
	}

	// Listen()
	if( listen( listening_socket, 5 ) < 0 )
	{
		printf( "Server : Listen error\n" );
		exit( 1 );
	}

	fpritnf( stdin, "Word Chain Game!!\n\n" );

	while( 1 )
	{
		socklen_t len = sizeof( cli_addr );
		client_socket = accept( listening_socket, (struct sockaddr*)&cli_addr, &len );

		// MAX PLAYER CHECK
		if( (n_Client + 1) == MAX_PLAYERS )
		{
			printf( "Game already started.\n" );
			close( client_socket );
			continue;
		}

		Player* p = (Player*)malloc( sizeof( Player ) );
		p->address = cli_addr;
		p->sockfd = client_socket;
		p->id = player_id++;
		p->life = 3;

		add_Player( p );
		pthread_create( &tid, NULL, &service, (void*)p );
	}
	freeMemory();
	return 0;
}

void add_Player( Player* p )
{
	pthread_mutex_lock( &mutex );
	players[n_Client] = p;
	pthread_mutex_unlock( &mutex );
}

void del_Player( int process_id )
{
	pthread_mutex_lock( &mutex );
	for( int i = 0; i < MAX_PLAYERS; i++ )
	{
		if( players[i] != NULL && players[i]->id == process_id)
		{
			players[i] = NULL;
			break;
		}
	}
	pthread_mutex_unlock( &mutex );
}

void send_msg( char* s, int id )
{
	pthread_mutex_lock( &mutex );
	for( int i = 0; i < MAX_PLAYERS; i++ )
	{
		if( players[i] != NULL && players[i]->id != id )
		{
			write( players[i]->sockfd, s, strlen( s ) );
		}
	}
	pthread_mutex_unlock( &mutex );
}

void send_msg_All( char* s )
{
	pthread_mutex_lock( &mutex );
	for( int i = 0; i < MAX_PLAYERS; i++ )
	{
		if( players[i] != NULL)
		{
			write( players[i]->sockfd, s, strlen( s ) );
		}
	}
	pthread_mutex_unlock( &mutex );
}

void change_prev_word( char* s )
{
	pthread_mutex_lock( &mutex );
	strcpy( prev_word, s );
	pthread_mutex_unlock( &mutex );
}

void* service( void* arg )
{
	char printing_buf[MAX_BUF];
	char name[16];
	int isLeft = 0;
	int isFirst = 1;

	n_Client++;
	Player* p = (Player*) arg;

	recv( p->sockfd, name, 16, 0 );
	strcpy( p->name, name );
	
	// 프린트할 배열에 출력(추후에 메시지로 클라이언트에게 보내기 위함.)
	sprintf( printing_buf, "Player : %s entered\n", p->name ); 
	fprintf( stdin, "%s", printing_buf );
	send_msg( printing_buf, p->id );

	memset( printing_buf, 0, MAX_BUF );

	while( 1 )
	{
		if( isFirst )
		{
			send_msg_All( prev_word );
			isFirst = 0;
		}
		if( isLeft )
		{
			break;
		}
		int check_recv = recv( p->sockfd, printing_buf, MAX_BUF, 0 );
		
		printing_buf[strlen( printing_buf ) - 1] = '\0';
		
		if( check_recv > 0 ) // Player가 정상적으로 메시지 보냄.
		{
			//send_msg( printing_buf, p->id );
			//printf( "Player : %s typed %s\n", printing_buf, p->name );
			if( valid_check( printing_buf ) )
			{
				change_prev_word( printing_buf );
				sprintf( printing_buf, "Player : %s typed %s\n", p->name, printing_buf );
				send_msg_All( printing_buf );
			}
			else if( !valid_check( printing_buf ) )
			{
				sprintf( printing_buf, "Player : %s typed %s WRONG!\n", p->name, printing_buf );
				send_msg_All( printing_buf );
				p->life--;
			}
		}
		else
		{
			sprintf( printing_buf, "Player : %s left\n", p->name );
			fprintf( stdin, "%s", printing_buf );
			send_msg( printing_buf, p->id );
			isLeft = 1;
		}

		memset( printing_buf, 0, MAX_BUF );
	}

	close( p->sockfd );
	
	del_Player( p->id );
	free( p );
	
	n_Client--;
	pthread_detach( pthread_self() );

	return NULL;
}

int valid_check( char* buf )
{
	if( prev_word != buf )
	{
		/// 1) Compare the first letter of typed word with word to solve.
		if( prev_word[strlen( prev_word ) - 1] == buf[0] )
		{
			/// 2) Check the typed word is duplicated.
			if( !isWordIn( list.head, buf ) )
			{
				/// 3) Check if the word is actually in dictionary.
				if( search( root_BSTnodes[buf[0] - 97], buf ) )
				{
					tmp = createLNode( buf );
					insertLNode( &list.head, &list.current, tmp );
					return 1;
				}
			}
		}
	}
	return 0;
}

void freeMemory()
{
	for( int i = 0; i < 26; i++ )
	{
		freeAllBST( root_BSTnodes[i] );
	}
	freeAllList( list.head );
}
