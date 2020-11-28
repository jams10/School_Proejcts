#pragma once

class Node
{
	int key;	// 노드 키 값
	Node* lChild;   // 노드의 왼쪽 자식 노드
	Node* rChild;   // 노드의 오른쪽 자식 노드
public:
	Node( int key_in );
	~Node();
	/* 좌/우 자식 노드 설정 */
	void SetLeftChild( Node* lChild );
	void SetRightChild( Node* rChild );

	/* 좌/우 자식 노드 가져오기 */
	Node* GetLeftChild();
	Node* GetRightChild();

	/* 노드 키 가져오기 */
	int GetKey();
};

class Tree
{
	Node* root;	// 루트 노드
	int size;       // 트리 사이즈
public:
	Tree();
	~Tree();
	// 노드 생성 함수
	Node* CreateNode( int key );
	// Root 테이블을 통해 트리 만드는 함수
	Node* Make( const int r[][8], const int& i, const int& j );
	// 루트 노드 가져오는 함수
	Node* GetRoot();
	// 루트 노드 설정 함수
	void SetRoot( Node* root );
	// 트리 전위 순회 함수
	void Preorder( Node* node );
};
