#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// List of used words.
typedef struct invalidWords
{
	char word[32];
	struct invalidWords *next;
}invalidWords;

typedef struct invalidWordsManager
{
	invalidWords *header;
	invalidWords *current;
}invalidWordsManager;

// Player struct
typedef struct Player
{
	int life;
}Player;

invalidWordsn *CreateNode(char *s);
bool IsValidWord(char *s, invalidWordsManager wordChecker);

int main(int argc, char *argv[])
{
	int n = 0;
	printf("Type the number of players : ");
	scanf("%d",&n);

	Player *pPlayer = (Player*)malloc(sizeof(Player)*n);
	
		
	for(int i=0; i<n; i++)
	{
		pPlayer[i].life=3;	
	}

	for(int i=0; i<n; i++)
	{
		printf("%d\n",pPlayer[i].life);
	}

	char typedWord[32];
	int playerCount = 1;
	invalidWordsManager wordChecker;

	wordChecker.header = NULL;
	wordChecker.current = NULL;

	/* Suppose players type the words */
	for(;;)
	{
		printf("Type the word : ");
		/* Player typed word should meet two condition.
		 * 1) The first letter of typed word should be same as the last letter of previous typed word.
		 * 2) The typed words should not be duplicated. (The words should not be in inValidWords list.)
		 */

		scanf("%s",&typedWord);
	
		/* Check if it is valid or not. */
		// The typed word is valid.
		if(IsValidWord(typedWord, wordChecker))
		{	
			// If head pointer is null = there is no node
			// 1) Head pointer should point the created node
			// 2) Current pointer should point the created node
			if(wordChecker.header == NULL)
			{
				wordChecker.header = CreateNode(typedWord);
				wordChecker.current = wordChecker.header;
			}
			
			// If there is only one node
			// 1) The next node of the node which head pointer is pointing, is created node
			// 2) Current pointer is now pointing the created node.
			else if(wordChecker.header.next = NULL)
			{
				wordChecker.header.next = CreateNode(typedWord);
				wordChecker.current = wordChecker.header.next;
			}	
			// The number of nodes is more than one 
			// 1) The next node of the node which current pointer is pointing, is created node
			else
			{
				wordChecker.current.next = CreateNode(typedWord);
				wordChecker.current = wordChecker.current.next;
			}
		}
		// The typed word is invalid.
		else
		{
			printf("Typed word is invalid! Your life point decreased!!\n");
			pPlayer[playerTurn%3].life--;
		}

		// Check dead player
		if(pPlayer[playerTurn%3].life <= 0)
		{
			printf("Player %d is dead.\n", i%3);
		}
		playerTurn++; // change player's turn
	}

	// If the game has ended, free memory allocated variables.
}

invalidWords *CreateNode(char *s)
{
	invalidWords *p = (invalidWords *)malloc(sizeof(invalidWords));
	strdup(p.word, s);
	p.next = NULL;

	return p;
}

bool IsValidWord(char *s, invalidWordsManager wordChecker)
{
	while(wordChecker.header.next!=NULL)
	{
		if(strcmp(wordChecker.header.word, s) == 0)
		{
			return false;
		}
		wordChecker.header = wordChecker.header.next;
	}
	return true;
}
