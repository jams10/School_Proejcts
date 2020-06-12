/////////////////////////////////////////////////
// This file contains linked, circular list    //
// which the typed words and players stored in //
/////////////////////////////////////////////////

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LNode = Linked list node
typedef struct LNode
{
	char* word;
	struct LNode* next;
}LNode;

typedef struct List
{
	struct LNode* head;
	struct LNode* current;
}List;


LNode* createLNode( const char* word );

void insertLNode( LNode** head, LNode** current, LNode* new_LNode );

void freeAllList( LNode* head );

void display( LNode* head );

int isWordIn( LNode* head, const char* word );
