#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	char* word;
	struct Node* next;
}Node;

typedef struct List
{
	struct Node* head;
	struct Node* current;
}List;

typedef struct CircularList
{
	struct Player* head;
	struct Player* tail;
	struct Player* current;
}CircularList;

typedef struct Player
{
	int life;
	char* name;
	struct Player* next;
}Player;

Node* create( const char* word );

void insert( Node** head, Node** current, Node* new_node );

void freeAllLinkedList( Node* head, Player* players, int nPlayers );

void display( Node* head );

int isWordIn( Node* head, const char* word);

void start();

int isWordCorret() {}

int main( int argc, char* argv[] )
{
	/*
	List list;
	list.head = NULL;
	list.current = NULL;
	Node* tmp = NULL;
	char s[20];
	for( int i = 0; i < 5; i++ )
	{
		fgets( s, 20, stdin );
		if( wordIsIn( list.head, s ) )
		{
			tmp = create( s );
			insert( &list.head, &list.current, tmp );
			printf( "%s is valid\n", s );
		}
		else
		{
			printf( "%s is invalid\n", s );
		}
	}
	//display(list.head);
	freeAll( list.head );
	*/
	start();
}

Node* create( const char* word )
{
	Node* p = malloc( sizeof( Node ) );

	if( p == NULL )
	{
		fprintf( stderr, "Memory allocation error\n" );
		exit( 1 );
	}
	else
	{
		p->word = malloc( strlen( word ) + 1 );
	}

	if( p->word == NULL )
	{
		fprintf( stderr, "Memory allocation error\n" );
		exit( 1 );
	}
	else
	{
		strcpy( p->word, word );
		p->next = NULL;
	}

	return p;
}

void insert( Node** head, Node** current, Node* new_node )
{
	if( *head == NULL )
	{
		*head = new_node;
		*current = new_node;
	}
	else
	{
		(*current)->next = new_node;
		*current = new_node;
	}
}

void freeAllLinkedList( Node* head, Player* players, int nPlayers )
{
	Node* p = head;
	Node* nextNode = NULL;

	Player* pp = players;

	while( p != NULL )
	{
		nextNode = p->next;
		free( p->word );
		free( p );
		p = nextNode;
	}

	for( int i = 0; i < nPlayers; i++ )
	{
		free( pp[i].name );
	}
	free( pp );
}

void display( Node* head )
{
	Node* p = head;
	while( p != NULL )
	{
		printf( "%s\n", p->word );
		p = p->next;
	}
}

int isWordIn( Node* head, const char* word )
{
	Node* p = head;
	while( p != NULL )
	{
		if( strcmp( p->word, word ) == 0 )
		{
			return 1;
		}
		p = p->next;
	}
	return 0;
}

void start()
{
	/*Set the players*/
	int nPlayers = 0;
	char name[20];
	Player* players = NULL;

	printf( "Type the number of players: " );
	scanf( "%d", &nPlayers );

	getchar();

	if( nPlayers == 0 )
	{
		return;
	}

	players = malloc( sizeof( Player ) * nPlayers );

	for( int i = 0; i < nPlayers; i++ )
	{
		printf( "Type the name of player[%d]: ", i );
		fgets( name, 20, stdin );
		name[strlen( name ) - 1] = '\0';
		players[i].name = malloc( strlen( name ) + 1 );
		strcpy( players[i].name, name );
		players[i].life = 3;
	}
	// You should free players->name and players

	/*Start the game*/
	List list;
	list.head = NULL;
	list.current = NULL;

	Node* tmp = NULL;

	char prev_word[20];
	char current_word[20];
	int turn = 0;

	strcpy( prev_word, "start" );

	for( int i = 0; i < 10; i++ )
	{
		turn %= 3;

		printf( "\033[32mWord : \033[1;32m%s\n\033[0m", prev_word );
		printf( "Player[\033[31m%d\033[0m] \033[34m%s\033[0m's turn!\n", turn, players[turn].name );
		printf( "Type the word: " );

		fgets( current_word, 20, stdin );
		current_word[strlen( current_word ) - 1] = '\0'; // delete last word ('\n')

		/* CHECK STRING */
		// 1
		/* Compare the first word of current_word with the last word of prev_word. */
		if( prev_word[strlen( prev_word ) - 1] != current_word[0] )
		{
			printf( "\033[31mYou typed invalid word!\n\033[0m" );
			printf( "Player[\033[31m%d\033[0m] \033[34m%s\033[0m's life has decreased!\n",
				turn, players[turn].name );
			players[turn].life--;
		}
		// 2
		/* Check if the word is in list. */
		if( isWordIn( list.head, current_word) )
		{
			printf( "\033[31mType word is duplicated!\n\033[0m" );
			printf( "Player[\033[31m%d\033[0m] \033[34m%s\033[0m's life has decreased!\n",
				turn, players[turn].name );
			players[turn].life--;
		}
		// 3
		/* Check if the word is actually in dictionary. */

		else
		{
			/* If player type valid word, that word is added to list and change prev_word. */
			tmp = create( current_word );
			insert ( &list.head, &list.current, tmp );
			strcpy( prev_word, current_word );
		}
		/* If the player's life is 0, that player will be dead. */
		if( players[turn].life == 0 )
		{
			printf( "Player[\033[31m%d\033[0m] \033[34m%s\033[0m is dead!\n", turn, players[turn].name );
			return;
		}

		turn++;
	}
}
