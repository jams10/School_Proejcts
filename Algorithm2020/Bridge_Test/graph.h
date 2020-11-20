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
  Node* GetHead();
	void InsertNode( Node* node );
  void ShowList() const;
  std::vector<int> GetValues() const;
	bool Search( int index ) const;
  ~List();
};

class Graph
{
	int nVerts;
	std::vector<List*> vertices;
public:
  Graph( int nVerts_in );
	void ShowVertices() const;
  void ShowConnections() const;
  int GetSize() const;
  bool SetConnection( const int& v1, const int& v2 );
  bool CheckConnection( const int& v1, const int& v2 ) const;
};
