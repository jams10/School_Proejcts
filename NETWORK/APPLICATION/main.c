#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bst.h"

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
	
	/*  De-allocate words and nodes */
	for(int i=0; i<26; i++)
	{
		freeAll(root_nodes[i]);
	}

	/* Confirm de-allocation */
	
	/*
	printf("%p\n",*root_nodes[0]);
	printf("%s\n",root_nodes[0]->word);
	*/
}

