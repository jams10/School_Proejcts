#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bst.h"

void start()
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
		

}

