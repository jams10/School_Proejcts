#pragma once

#include <vector>

typedef struct Node
{
	int index;
	Node* next;
}Node;

class List
{
	Node* head;
	Node* tail;
public:
	Node* CreateNode( int index );
	void InsertNode( Node* node);
	bool Search( int index );
};

class Graph
{
	int nVerts;
	std::vector<List> vertices;
public:
	void SetNumberOfVertices( int n ); 
};
