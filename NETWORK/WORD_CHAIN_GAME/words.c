////////////////////////////////////////////
// This file contains binary search tree  //
// which the words stored in              //
////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "words.h"

BSTNode* insert( BSTNode* root, const char* word )
{
	if( root == NULL )
	{
		fprintf( stdin, "%s\n", word );
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

BSTNode* create( const char* word )
{
	BSTNode* p = malloc( sizeof( BSTNode ) );

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

void freeAllBST( BSTNode* root )
{
	if( root == NULL )
	{
		return;
	}

	freeAllBST( root->left );
	freeAllBST( root->right );

	/* Memory de-allocation */
	free( root->word );
	free( root );
}

int search( BSTNode* root, const char* word )
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

void preorder( const BSTNode* root )
{
	if( root != NULL )
	{
		printf( "%s\n", root->word );
		preorder( root->left );
		preorder( root->right );
	}
}

void store_words( FILE* fp, BSTNode* root_BSTNodes[] )
{
	char buf[32];

	while( fgets( buf, 32, fp ) )
	{
		/* The first character of string - 97 = root_BSTNodes array index */
		/* Save the word to corresponding binary search tree */

		if( buf[0] != '.' )
		{
			buf[strlen( buf ) - 1] = '\0';
			root_BSTNodes[buf[0] - 97] = insert( root_BSTNodes[buf[0] - 97], buf );
		}
	}
}
