#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include "words.h"
#include "players.h"

#define MAX_PLAYERS 5 
#define MAX_BUF 256 

typedef struct
{
	char name[32];
	int socket;
	int id; 
	int turn;
	int score;
} Player_t; 

Player_t* players[MAX_PLAYERS]; 

static unsigned int n_players = 0; // The number of players
static unsigned int global_player_id = 0; 
static unsigned int global_player_turn = 0;
static int current_round = -1;
static int isStart = 0;

char prev_word[20];

FILE* fp;
BSTNode* root_BSTnodes[26];

List list;
LNode* tmp = NULL;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cons = PTHREAD_COND_INITIALIZER;

void addPlayer( Player_t* player );

void delPlayer( int id );

void sendMSG( char* s);

void change_prev_word( char* s );

int valid_check( char* buf );

void freeMemory();

void* service( void* arg );

int main( int argc, char** argv )
{
	if( argc != 2 )
	{
		printf( "Usage: %s <port>\n", argv[0] );
		exit( 1 );
	}

	/* Set the BST for game */
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

	/* This list is for checking whether player typed word is duplicated or not. */
	list.head = NULL;
	list.current = NULL;

	/* Set random word for the first current_round */
	srand( time( NULL ) );
	int num = (int)(rand() % 26);
	strcpy( prev_word, root_BSTnodes[num]->word );

	char* ip = "192.168.131.128";
	int port = atoi( argv[1] );
	int listening_socket = 0, service_socket = 0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	pthread_t tid;

	/* Socket settings */
	listening_socket = socket( AF_INET, SOCK_STREAM, 0 );
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr( ip );
	serv_addr.sin_port = htons( port );

	/* Bind */
	if( bind( listening_socket, (struct sockaddr*)&serv_addr, sizeof( serv_addr ) ) < 0 )
	{
		fprintf( stderr, "Can't bind a socket." );
		exit( 1 );
	}

	/* Listen */
	if( listen( listening_socket, 10 ) < 0 )
	{
		fprintf( stderr, "Can't listen sockets." );
		exit( 1 );
	}

	printf( "SERVER ON. LISTENING...\n" );

	while( 1 )
	{
		socklen_t clnt_socket_len = sizeof( clnt_addr );
		service_socket = accept( listening_socket, (struct sockaddr*)&clnt_addr, &clnt_socket_len );

		/* Max player check */
		if( MAX_PLAYERS <= ( n_players + 1 ) )
		{
			close( service_socket );
			continue;
		}

		/* Set players instance */
		Player_t* player = (Player_t*)malloc( sizeof( Player_t ) );
		player->socket = service_socket;
		player->id = global_player_id++;
		player->score = 0;
		player->turn = global_player_turn++;

		printf( "%d\n", current_round );
		addPlayer( player );
		pthread_create( &tid, NULL, &service, (void*)player );
	}
	freeMemory();
	return 0;
}

void addPlayer( Player_t* player ) 
{
	pthread_mutex_lock( &mutex );

	for( int i = 0; i < MAX_PLAYERS; i++ )
	{
		if( players[i] == NULL )
		{
			players[i] = player;
			break;
		}
	}

	pthread_mutex_unlock( &mutex );
}

void delPlayer( int id ) 
{
	pthread_mutex_lock( &mutex );

	for( int i = 0; i < MAX_PLAYERS; ++i )
	{
		if( players[i] != NULL )
		{
			if( players[i]->id == id )
			{
				players[i] = NULL;
				break;
			}
		}
	}

	pthread_mutex_unlock( &mutex );
}

void sendMSG( char* s)
{
	for( int i = 0; i < MAX_PLAYERS; ++i )
	{
		if( players[i] )
		{
			if( write( players[i]->socket, s, strlen( s ) ) < 0 )
			{
				fprintf( stderr, "Can't write to socket" );
				break;
			}
		}
	}
}

void change_prev_word( char* s )
{
	strcpy( prev_word, s );
}

int valid_check( char* buf )
{
	if( prev_word != buf )
	{
		if( prev_word[strlen( prev_word ) - 1] == buf[0] )
		{
			if( !isWordIn( list.head, buf ) )
			{
				if( search( root_BSTnodes[buf[0] - 97], buf ) )
				{
					/* If the player typed word is valid, insert it to the list
					 * for checking duplication */
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

void* service( void* arg ) 
{
	char buf[MAX_BUF];
	char player_typed_word[64];
	char player_name[32];
	int isLeft = 0;

	n_players++;

	Player_t* player = (Player_t*)arg;

	// Check name is typed.
	if( recv( player->socket, player_name, 32, 0 ) <= 0 || 
		strlen( player_name ) < 2 || strlen( player_name ) >= 32 - 1 )
	{
		printf( "Type your name\n" );
		isLeft = 1;
	}
	else
	{
		strcpy( player->name, player_name );
		sprintf( buf, "Player : [%s] entered \n", player->name );
		printf( "%s", buf );
		sendMSG( buf );
	}
	bzero( buf, MAX_BUF );

	/* If the number of connected players is 4, start the game.(wake up the first thread.) */
	if( n_players == 4 )
	{
		pthread_mutex_lock( &mutex );
		
		current_round++;
		sprintf( buf, "\n>>Word to solve : [%s]\n\n", prev_word );
		sendMSG( buf );
		
		pthread_mutex_unlock( &mutex );
		pthread_cond_broadcast( &cons );
	}
	bzero( buf, MAX_BUF );

	while( 1 )
	{
		if( isLeft )
		{
			break;
		}
		printf( "player turn : %d, current_round : %d\n", player->turn, current_round );

		pthread_mutex_lock( &mutex );

		while( player->turn != current_round )
		{
			pthread_cond_wait( &cons, &mutex );
		}
		printf( "%d turn : %d\n", current_round, player->turn );

		/* Server already printed the word to solve when game is just started,
		 * so do not print the word at fisrt current_round.*/
		if( isStart )
		{
			sprintf( buf, "\n>>Word to solve : %s\n\n", prev_word );
			sendMSG( buf );
		}
		else
		{
			isStart = 1;
		}
		bzero( buf, MAX_BUF );

		/* Send messages about players' score to all players. */
		/* In the codes below, we don't have to care about race condition
		 * because all threads are sleeping except for the thread which has turn same as current current_round. */
		for( int i = 0; i < MAX_PLAYERS; i++ )
		{
			if( players[i] )
			{
				sprintf( buf, "Player: %15s | score :%15d\n", players[i]->name, players[i]->score );
				sendMSG( buf );
				bzero( buf, MAX_BUF );
			}
		}
		sprintf( buf, "\n" );
		sendMSG( buf );
		bzero( buf, MAX_BUF );

		/* Print player's turn */
		sprintf( buf, "\n>>Player : [%s] turn!!\n\n", player->name );
		sendMSG( buf );
		bzero( buf, MAX_BUF );

		int receive_check = recv( player->socket, player_typed_word, 64, 0 );
		if( receive_check > 0 )
		{
			if( strlen( player_typed_word ) > 0 )
			{
				printf( "%s", player_typed_word );
				/* If the player typed word is valid, change prev_word and that player scores 10. */
				if( valid_check( player_typed_word ) )
				{
					change_prev_word( player_typed_word );		
					bzero( buf, MAX_BUF );			
					sprintf( buf, "Player : [%s] typed [%s] (CORRECT!!) \n", player->name, player_typed_word );
					player->score += 10;
					sendMSG( buf );
				}
				else if( !valid_check( player_typed_word ) )
				{
					bzero( buf, MAX_BUF );
					sprintf( buf, "Player : [%s] typed [%s] (WRONG!!) \n", player->name, player_typed_word );
					sendMSG( buf );
				}
			}
		}
		else if( receive_check == 0 )
		{
			isLeft = 1;
		}
		else
		{
			isLeft = 1;
		}
		bzero( buf, MAX_BUF );
		bzero( player_typed_word, 64);

		current_round++; // change current_round

		// all players have typed at once, so init round.
		if( current_round == MAX_PLAYERS - 1 )
		{
			current_round = 0;
		}

		pthread_cond_broadcast( &cons );
		pthread_mutex_unlock( &mutex );
	}

	/* Player has left, so free allocated resource. */
	close( player->socket );
	delPlayer( player->id );
	free( player );
	n_players--;
	
	/* De-allocate thread resource without pthread_join() */
	pthread_detach( pthread_self() );

	return NULL;
}
