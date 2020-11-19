#include "Tree.h"
#include <iostream>

Node::Node( int key_in )
	:
	key(key_in),
	lChild(nullptr),
	rChild(nullptr)
{
}

void Node::SetLeftChild( Node* lChild )
{
	this->lChild = lChild;
}

void Node::SetRightChild( Node* rChild )
{
	this->rChild = rChild;
}

Node* Node::GetLeftChild()
{
	return lChild;
}

Node* Node::GetRightChild()
{
	return rChild;
}

int Node::GetKey()
{
	return this->key;
}

Node::~Node()
{
	delete lChild;
	delete rChild;
}

Node* Tree::CreateNode( int key )
{
	Node* node = new Node( key );

	return node;
}

Node* Tree::Make( const int r[][8], const int& i, const int& j )
{
	int key = r[i][j];
	Node* node = nullptr;
	if( key )
	{
		node = CreateNode( key );
	}
	else
	{
		return nullptr;
	}
	node->SetLeftChild( Make( r, i, key - 1 ) );
	node->SetRightChild( Make( r, key, j ) );

	return node;
}

Node* Tree::GetRoot()
{
	return root;
}

void Tree::SetRoot( Node* root )
{
	this->root = root;
}

void Tree::Preorder( Node* node )
{
	Node* root = node;
	if( root == nullptr ) return; 
	
	std::cout << root->GetKey() << " "; 
	Preorder( root->GetLeftChild() );
	Preorder( root->GetRightChild() );
}

Tree::~Tree()
{
	delete root;
}
