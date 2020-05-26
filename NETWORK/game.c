#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "players.h"
#include "words.h"

int main( int argc, char* argv[] )
{
	//1. Set the players
	CircularList circularList;

	int nPlayers = 0;

	for(;;)
	{
		if( nPlayers != 0 )
		{
			break;
		}
		printf( "Type the number of players: " );
		scanf( "%d", &nPlayers );

		getchar();
	}

	initPlayers( &circularList, nPlayers);

	/* Test player setting
	for( int i = 0; i < nPlayers; i++ )
	{
		printf( "%s", circularList.head->name );
		circularList.head = circularList.head->next;
	}
	*/

	//2. Set the BST
	FILE* fp;
	if( (fp = fopen( "./20k.txt", "r" )) == NULL )
	{
		fprintf( stderr, "File open error.\n" );
		exit( 1 );
	}

	BSTNode* root_BSTnodes[26];
	for( int i = 0; i < 26; i++ )
	{
		root_BSTnodes[i] = NULL;
	}
	store_words( fp, root_BSTnodes );
	fclose( fp );

	/* Test BST setting
	char words[20];
	
	printf( "Type the word : " );
	
	fgets( words, 20, stdin );
	words[strlen( words ) - 1] = '\0';

	if( search( root_BSTnodes[ words[0] - 97 ], words ) )
	{
		printf( "Found!\n" );
	}
	*/

	//3. Start game
	List list;
	list.head = NULL;
	list.current = NULL;
	LNode* tmp = NULL;

	CircularList clistForPlayer;
	clistForPlayer.head = circularList.head;
	
	CircularList clistForLife;
	clistForLife.head = circularList.head;

	int isFisrtTime = 1;
	int isValid = 0;
	int nDeadPlayers = 0;

	while(1)
	{
		// 1. Print Players Life.
		printf( "\nPlayers Life\n" );
		for( int i = 0; i < nPlayers; i++ )
		{
			printf( "%s : %d\n", clistForLife.head->name, clistForLife.head->life );
			clistForLife.head = clistForLife.head->next;
		}
		clistForLife.head = circularList.head;

		// 2. Print the random word in BST. (only first time)
		char prevWord[20];
		
		printf( "\n-QUIZ-\n" );
		if( isFisrtTime )
		{
			srand( (unsigned int)time( NULL ) );
			int num = (int)(rand() % 26);

			strcpy( prevWord, root_BSTnodes[num]->word );
			printf( "%s\n", root_BSTnodes[num]->word );
			isFisrtTime = 0;
		}
		else
		{
			printf( "%s\n", prevWord );
		}

		// 3. Players type the word.
		if( clistForPlayer.head->life == 0 )
			continue;
		char typedWord[20];
		
		printf( "\nPlayer : %s's turn!\n", clistForPlayer.head->name );
		printf( "Type the word: " );
		fgets( typedWord, 20, stdin );
		typedWord[strlen( typedWord ) - 1] = '\0';

		// 4. Check the typed word.
		
		/// 0) Check duplicated word.
		if( prevWord != typedWord )
		{
			/// 1) Compare the first letter of typed word with word to solve.
			if( prevWord[strlen( prevWord ) - 1] == typedWord[0] )
			{
				/// 2) Check the typed word is duplicated.
				if( !isWordIn( list.head, typedWord ) )
				{
					/// 3) Check if the word is actually in dictionary.
					if( search( root_BSTnodes[typedWord[0] - 97], typedWord ) )
					{
						isValid = 1;

						tmp = createLNode( typedWord );
						insertLNode( &list.head, &list.current, tmp );
						strcpy( prevWord, typedWord );
					}
				}
			}
		}

		// 5. If the typed word is invalid, decrease player's point.
		if( !isValid )
		{
			printf( "\n\033[31mPlayer :\033[0m \033[32m%s \033[31mtyped wrong word!\033[0m\n", clistForPlayer.head->name );
			printf( "Player : %s's life has decreased!\n", clistForPlayer.head->name );
			
			clistForPlayer.head->life--;
			
			if( clistForPlayer.head->life == 0 )
			{
				nDeadPlayers++;
			}
		}

		// 6. If only one player has left, end game.
		if( nDeadPlayers == nPlayers - 1 )
		{
			for( int i = 0; i < nPlayers; i++ )
			{
				if( clistForLife.head->life != 0 )
				{
					printf( "Player: %s wins!\n", clistForLife.head->name );
					break;
				}
				clistForLife.head = clistForPlayer.head->next;
			}
			break;
		}

		isValid = 0;

		clistForPlayer.head = clistForPlayer.head->next;
	}

	// de-allocation memory.
	freeAllList( list.head );
	
	freeAllPlayers( circularList.head, nPlayers );

	for( int i = 0; i < 26; i++ )
	{
		freeAllBST( root_BSTnodes[i] );
	}
	
	return 0;
}
