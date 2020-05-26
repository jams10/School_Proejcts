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

void freeAllBST( Node* root );

void preorder( const Node* root );

void store_words( FILE* fp, Node* root_nodes[] );


