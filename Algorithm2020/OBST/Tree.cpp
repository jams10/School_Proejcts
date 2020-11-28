#include <iostream>
#include "Tree.h"

Node::Node( int key_in )
	:
	key( key_in ),
	lChild( nullptr ),
	rChild( nullptr )
{
}

Node::~Node()
{
	// nullptr 체크
	if( lChild ) delete lChild;
	if( rChild ) delete rChild;
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

Tree::Tree()
	:
	root( nullptr ),
	size( 0 )
{
}

Tree::~Tree()
{
	// nullptr 체크
	if( root ) delete root;
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
	// ROOT 테이블의 해당 위치 값이 0이 아닌 경우
	if( key )
	{
		node = CreateNode( key );
	}
	else
	{
		return nullptr;
	}
	// 재귀 호출을 통해 좌/우 자식 노드 설정
	// 좌측 자식 노드의 경우 ROOT 테이블의 (i, key - 1)
	// 우측 자식 노드의 경우 ROOT 테이블의 (key, j)
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
