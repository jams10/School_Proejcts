#pragma once

class Node
{
	int key;
	Node* lChild;
	Node* rChild;
public:
	Node( int key_in );
	void SetLeftChild( Node* lChild );
	void SetRightChild( Node* rChild );
	Node* GetLeftChild();
	Node* GetRightChild();
	int GetKey();
	~Node();
};

class Tree
{
	Node* root;
	int size;
public:
	Node* CreateNode( int key );
	Node* Make( const int r[][8], const int& i, const int& j );
	Node* GetRoot();
	void SetRoot( Node* root );
	void Preorder( Node* node );
	~Tree();
};
