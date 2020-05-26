////////////////////////////////////////////
// This file contains binary search tree  //
// which the words stored in              //
////////////////////////////////////////////

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	char* word;
	struct Node* left;
	struct Node* right;
}BSTNode;

BSTNode* insert( BSTNode* root, const char* word );

BSTNode* create( const char* word );

int search( BSTNode* root, const char* word );

void freeAllBST( BSTNode* root );

void preorder( const BSTNode* root );

void store_words( FILE* fp, BSTNode* root_BSTNodes[] );
