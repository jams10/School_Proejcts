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
