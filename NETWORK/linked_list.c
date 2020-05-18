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

Node* create( const char* word )
{
	Node* p = malloc( sizeof( Node ) );

	if( p == NULL)
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

void freeAll( Node *head )
{
	Node* p = head;
	Node* nextNode = NULL;
	
	while( p!=NULL )
	{
		nextNode = p->next;
		free( p->word );
		free( p );
		p = nextNode;
	}
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

int isValid( Node* head, const char* word )
{
	Node* p = head;
	while( p != NULL )
	{
		if( strcmp( p->word, word ) == 0 )
		{
			return 0;
		}
		p = p->next;
	}
	return 1;
}

int main(int argc, char *argv[])
{
	List list;
	list.head = NULL;
	list.current = NULL;

	Node* tmp = NULL;

	char s[20];

	for( int i = 0; i < 5; i++ )
	{
		fgets( s, 20, stdin );
		if( isValid( list.head, s ) )
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
}