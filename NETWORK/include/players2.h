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

typedef struct Player
{
	int life;
	char* name;
	struct Player* next;
}Player;

typedef struct CircularList
{
	struct Player* head;
	struct Player* tail;
	//struct Player* current;
}CircularList;

LNode* createLNode( const char* word );

Player* createPlayer( const char* word );

void insertLNode( LNode** head, LNode** current, LNode* new_LNode );

void insertPlayer( Player** head, Player** current, Player* new_Player );

void freeAllList( LNode* head );

void freeAllPlayers( Player* head, int nPlayers );

void display( LNode* head );

int isWordIn( LNode* head, const char* word );

void initPlayers( CircularList* circularList, int nPlayers);