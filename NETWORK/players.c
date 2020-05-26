#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "players.h"

LNode* createLNode( const char* word )
{
	LNode* p = malloc( sizeof( LNode ) );

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

Player* createPlayer( const char* name )
{
	Player* p = malloc( sizeof( Player ) );

	if( p == NULL )
	{
		fprintf( stderr, "Memory allocation error\n" );
		exit( 1 );
	}
	else
	{
		p->name = malloc( strlen( name ) + 1 );
	}

	if( p->name == NULL )
	{
		fprintf( stderr, "Memory allocation error\n" );
		exit( 1 );
	}
	else
	{
		strcpy( p->name, name );
		p->next = NULL;
	}

	p->life = 3;

	return p;
}

void insertLNode( LNode** head, LNode** current, LNode* new_LNode )
{
	if( *head == NULL )
	{
		*head = new_LNode;
		*current = new_LNode;
	}
	else
	{
		(*current)->next = new_LNode;
		*current = new_LNode;
	}
}

void insertPlayer( Player** head, Player** tail, Player* new_Player )
{
	if( *head == NULL )
	{
		*head = new_Player;
		*tail = new_Player;
	}
	else
	{
		(*tail)->next = new_Player;
		new_Player->next = *head;
		*tail = new_Player;
	}
}

void freeAllList( LNode* head )
{
	LNode* p = head;
	LNode* nextLNode = NULL;

	while( p != NULL )
	{
		nextLNode = p->next;
		free( p->word );
		free( p );
		p = nextLNode;
	}
}

void freeAllPlayers( Player* head, int nPlayers)
{
	Player* p = head;
	Player* nextPlayer = NULL;

	for( int i = 0; i < nPlayers; i++ )
	{
		nextPlayer = p->next;
		free( p->name );
		free( p );
		p = nextPlayer;
	}
}

void display( LNode* head )
{
	LNode* p = head;
	while( p != NULL )
	{
		printf( "%s\n", p->word );
		p = p->next;
	}
}

int isWordIn( LNode* head, const char* word )
{
	LNode* p = head;
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

void initPlayers( CircularList* circularList, int nPlayers )
{
	circularList->head = NULL;
	circularList->tail = NULL;
	Player* player = NULL;
	char name[20];

	for( int i = 0; i < nPlayers; i++ )
	{
		printf( "Type player's name: " );
		fgets( name, 20, stdin );
		name[strlen( name ) - 1] = '\0';
		player = createPlayer( name );
		insertPlayer( &circularList->head, &circularList->tail, player );
	}
}