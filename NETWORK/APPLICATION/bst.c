#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node
{
	char* word;
	struct Node* left;
	struct Node* right;
}Node;

Node* insert( Node* root, const char* word );

Node* create( const char* word );

int search( Node* root, const char* word );

void freeAll( Node* root );

void preorder( const Node* root );

void store_words( FILE* fp, Node* root_nodes[] );

int main( int argc, char* argv[] )
{
	/* Open file */
	FILE* fp;
	if( (fp = fopen( "./20k.txt", "r" )) == NULL )
	{
		fprintf( stderr, "File open error.\n" );
		exit( 1 );
	}

	/* Read and store words from file. */

	Node* root_nodes[26];
	for( int i = 0; i < 26; i++ )
	{
		root_nodes[i] = NULL;
	}
	store_words(fp, root_nodes);
	
	/* Close the file. */
	fclose( fp );

	/* Generate random number */
	srand( (unsigned int)time( NULL ) );
	int num = (int)(rand() % 26);

	//printf( "%s\n", root_nodes[num]->word );
	
		
	char word[20];
	printf("Type word : ");
	fgets(word, 20, stdin);
	word[strlen(word) - 1] = '\0';
	int idx = word[0] - 97;
	if(search(root_nodes[ idx ], word))
	{
		printf("Found!\n");
	}
	
	//printf( "%s", root_nodes['a' - 97]->word );

	//preorder(root_nodes [ 'a' - 97 ]);
	printf("%p\n",*root_nodes[0]); 
	printf("%s\n",root_nodes[0]->word);

	/*  De-allocate words and nodes */
	for(int i=0; i<26; i++)
	{
		freeAll(root_nodes[i]);
	}

	/* Confirm de-allocation */
	printf("%p\n",*root_nodes[0]);
	printf("%s\n",root_nodes[0]->word);

}

Node* insert( Node* root, const char* word )
{
	if( root == NULL )
	{
		fprintf(stdin, "%s\n",word);
		return create( word );
	}

	/* word > root->word */
	if( strcmp( word, root->word ) > 0 )
	{
		root->left = insert( root->left, word );
	}
	/* word < root->word */
	else if( strcmp( word, root->word ) < 0 )
	{
		root->right = insert( root->right, word );
	}

	return root;
}

Node* create( const char* word )
{
	Node* p = malloc( sizeof( Node ) );

	if( p == NULL )
	{
		fprintf( stderr, "Memory allocation error\n" );
		exit( 1 );
	}

	p->word = malloc( strlen( word ) + 1 );

	if( p->word == NULL )
	{
		fprintf( stderr, "Memory allocation error\n" );
		exit( 1 );
	}

	strcpy( p->word, word );

	p->left = NULL;
	p->right = NULL;

	return p;
}

void freeAll( Node* root )
{
	if(root == NULL)
	{
		return;
	}
	
	freeAll(root->left);
	freeAll(root->right);

	free(root->word);
	free(root);	
}

int search( Node* root, const char* word )
{
	while( root != NULL )
	{
		if( strcmp( word, root->word ) > 0 )
		{
			root = root->left;
		}
		else if( strcmp( word, root->word ) == 0 )
		{
			return 1;
		}
		else if( strcmp( word, root->word ) < 0 )
		{
			root = root->right;
		}
	}
	return 0;
}

void preorder( const Node* root )
{
	if( root != NULL )
	{
		printf( "%s\n", root->word );
		preorder( root->left );
		preorder( root->right );
	}
}

void store_words( FILE* fp, Node* root_nodes[] )
{
	char buf[32];

	while( fgets(buf, 32, fp) )
	{
		/* The first character of string - 97 = root_nodes array index */
		/* Save the word to corresponding binary search tree */
		
		if(buf[0] != '.')
		{
			buf[strlen( buf ) - 1] = '\0';
			//printf("%s\n",buf);
			root_nodes[buf[0] - 97] = insert( root_nodes[buf[0] - 97], buf );
			//printf("%s",root_nodes[buf[0] - 97]->word);
		}
	}
}
