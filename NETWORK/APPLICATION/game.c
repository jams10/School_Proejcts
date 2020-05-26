// include bst
// include linked_list

void start();

Player* initPlayers( int nPlayers );

void initBST( Node* root_nodes[]);

void gameLoop( Player* players, Node* root_nodes[]);

int main(int argc, char *argv[])
{
	start();
}

void start()
{
	/* Set the players */
	printf( "Type the number of players: " );
	scanf( "%d", &nPlayers );

	getchar();

	if( nPlayers == 0 )
	{
		return;
	}
	
	Player* players = initPlayers( nPlayers );
	
	/* Set bst */
	Node* root_nodes[26];
	initBST( root_nodes );
	
	// 1. Node structure type name is duplicated!
	// Change structures name.
	//
	// 2. Player structure should be controlled by cicular list.
	// If middle position player want to end game, we have to handle this situation.

	/* Game Loop */
	gameLoop(players, root_nodes);
	/* If a player typed -1 break */
}

Player* initPlayers( int nPlayers )
{
	/*Set the players*/
	char name[20];
	Player* players = NULL;

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

	return players;
}

void initBST( Node* root_nodes[] )
{
	/* Open file */
	FILE* fp;
	if( (fp = fopen( "./20k.txt", "r" )) == NULL )
	{
		fprintf( stderr, "File open error.\n" );
		exit( 1 );
	}

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

void gameLoop( Player* players, Node* root_nodes[] )
{
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
		}
		turn++;
	}
}
