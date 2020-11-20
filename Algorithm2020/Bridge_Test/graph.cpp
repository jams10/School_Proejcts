#include "graph.h"
#include <iostream>

Node* List::CreateNode( int index )
{
	Node* node = new Node();
	node->index = index;
	node->next = nullptr;
	return node;
}

Node* List::GetHead()
{
  return head;
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

void List::ShowList() const
{
  Node* node = head;
	while( node != nullptr )
	{
    std::cout << node->index << ' ';
		node = node->next;
	}
}

std::vector<int> List::GetValues() const
{
  std::vector<int> v;
  Node* node = head;
	while( node != nullptr )
	{
    v.emplace_back(node->index);
		node = node->next;
	}
  return v;
}

bool List::Search( int index ) const
{
	Node* node = head;
	while( node != nullptr )
	{
		if( node->index == index ) return true;
		node = node->next;
	}
	return false;
}

List::~List()
{
  /*
    본 프로그램에서 각 노드는 중복으로 삽입 되어 있으므로
    ex) 1과 2가 연결되어 있는 경우, 1번 리스트에 2번 삽입, 2번 리스트에 1번 삽입
    
    각 리스트마다 연결된 모든 노드를 할당 해제할 경우,
    두 번 이상의 할당 해제를 하게 되는 경우가 있음.
    따라서, 각 리스트마다 head 노드만 할당 해제함.
  */
  // 위 삭제
  Node* node = head;
  Node* delNode = nullptr;
	while( node != nullptr )
	{
    delNode = node;
    delete delNode;
		node = node->next;
	}
}

Graph::Graph( int nVerts_in )
  :
  nVerts( nVerts_in )
{
  for(int i = 0; i < nVerts; ++i)
  {
    List* pList = new List;
    Node* node = pList->CreateNode( i );
    pList->InsertNode( node );
    vertices.emplace_back( pList );
  }
}

void Graph::ShowVertices() const
{
  for(const auto& index : vertices)
  {
    index->ShowList();
  }
}

void Graph::ShowConnections() const
{
  std::vector<int> v;
  for(int i = 0; i < vertices.size(); ++i)
  {
    v = vertices[i]->GetValues();  
    if(v.size() < 2)
    {
      std::cout << "Vertex [" << i << "] : " << "has no bridges" << std::endl;
    }
    else
    {
      std::cout << "Vertex [" << i << "] : ";
      for(int j = 1; j < v.size(); ++j)
      {
        std::cout << v[0] << " - " << v[j] << ' ';
      }
      std::cout << std::endl;
    }
    
  }
}

int Graph::GetSize() const
{
  return vertices.size();
}

bool Graph::SetConnection( const int& v1, const int& v2 )
{
  if( vertices[v1]->Search(v2) ) return false;
  vertices[v1]->InsertNode(vertices[v1]->CreateNode(v2));
  vertices[v2]->InsertNode(vertices[v2]->CreateNode(v1));
  return true;
}

bool Graph::CheckConnection( const int& v1, const int& v2 ) const
{
  if(vertices[v1]->Search(v2)) return true;
  return false;
}

