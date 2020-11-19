#include "graph.h"

Node* List::CreateNode( int index )
{
	Node* node = new Node();
	node->index = index;
	node->next = nullptr;
	return node;
}

void List::InsertNode( Node* node )
{
	if( head == nullptr )
	{
		head = node;
		tail = node;
	}
	else
	{
		tail->next = node;
		tail = node;
	}
}

bool List::Search( int index )
{
	Node* node = head;
	Node* nextNode = head->next;
	while( node )
	{
		if( node->index == index ) return true;
		node = nextNode;
		nextNode = nextNode->next;
	}
	return false;
}
