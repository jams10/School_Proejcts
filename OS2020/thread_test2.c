#include <stdio.h>          
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define element unsigned int
#define MAX 1000000

typedef struct Node
{
	element value;
	int index;
	struct Node* next;
}Node;

typedef struct List
{
	struct Node* head;
	struct Node* tail;
}List;

Node* createNode( int value, int index );

void insertNode( Node** head, Node** tail, Node* newNode );

void display( Node* head );

void splitList( Node* head, Node** front_split_head, Node** back_split_head );

Node* merge( Node* front_split_head, Node* back_split_head );

void mergeSort( Node** head );

void freeAll( Node* head );

void* thread_func( void* arg );

int main( int argc, char** argv )
{
	/* Thread */
	pthread_t t;
	int status;

	/* List setup */
	List list;
	list.head = NULL;
	list.tail = NULL;

	/* Time setup */
	clock_t start, end;
	float result;

	///* Random seed setup */
	srand( time( NULL ) );
	unsigned int num = 0;

	//int num = 0;
	Node* tmp = NULL;
	/* Insert nodes */
	for( int i = 0; i < MAX; i++ )
	{
		num = (unsigned int)(rand() % MAX);
		tmp = createNode( num, i );
		insertNode( &list.head, &list.tail, tmp );
	}
	free( tmp );

	start = clock();
	pthread_create( &t, NULL, thread_func, &list );

	pthread_join( t, (void*)&status );
	end = clock();

	result = (float)(end - start) / CLOCKS_PER_SEC;
	printf( "%f\n", result );

	return 0;
}

Node* createNode( int value, int index )
{
	Node* pNode = malloc( sizeof( Node ) );
	if( pNode == NULL )
	{
		fprintf( stderr, "ERROR : Memory allocation.\n" );
		exit( 1 );
	}
	pNode->value = value;
	pNode->index = index;
	pNode->next = NULL;
	return pNode;
}

void insertNode( Node** head, Node** tail, Node* newNode )
{
	if( *head == NULL )
	{
		*head = newNode;
		*tail = newNode;
	}
	else
	{
		(*tail)->next = newNode;
		*tail = newNode;
	}
}

void display( Node* head )
{
	Node* p = head;
	while( p != NULL )
	{
		printf( "%d\n", p->value );
		p = p->next;
	}
}

void splitList( Node* head, Node** front_split_head, Node** back_split_head )
{
	Node* fast = NULL;
	Node* slow = NULL;

	fast = head->next;
	slow = head;

	/* fast, slow pointer 전략*/
	/* https://www.quora.com/What-is-a-slow-pointer-and-a-fast-pointer-in-a-linked-list */
	/* fast pointer는 한 번에 두 노드씩 이동, slow pointer는 한 번에 한 노드씩 이동함. */
	/* 이를 통해, fast pointer가 끝에 다다를 경우, slow pointer는 중간 노드를 가리키게 됨. */
	while( fast != NULL )
	{
		fast = fast->next;
		if( fast != NULL )
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	/* list 노드 개수가 홀수인 경우, 남은 노드는 앞쪽 리스트에 포함됨. */
	/* ex) 노드 개수가 5인 경우 : 앞쪽 노드의 개수 3, 뒤쪽 노드의 개수 : 2*/
	*front_split_head = head;
	*back_split_head = slow->next;
	slow->next = NULL;
}

Node* merge( Node* front_split_head, Node* back_split_head )
{
	Node* mergedList = NULL;

	/* 한쪽 리스트가 끝나게 되면 다른쪽 리스트를 리턴해 줌. */
	if( front_split_head == NULL )
	{
		return back_split_head;
	}
	else if( back_split_head == NULL )
	{
		return front_split_head;
	}
	/* 각 분할된 리스트의 값을 서로 비교, 더 작은 값의 요소를 가진 리스트의 노드를 가리킴. */
	/* 후속 노드의 경우 해당 리스트 노드를 하나 이동시킨 재귀 호출을 통해 할당해줌. */
	if( front_split_head->value <= back_split_head->value )
	{
		mergedList = front_split_head;
		mergedList->next = merge( front_split_head->next, back_split_head );
	}
	else
	{
		mergedList = back_split_head;
		mergedList->next = merge( front_split_head, back_split_head->next );
	}

	return mergedList;
}

void mergeSort( Node** head )
{
	Node* front_split_head = NULL;
	Node* back_split_head = NULL;

	/* 노드가 하나도 없거나, 하나만 있는 경우 정렬 필요 없음. */
	if( *head == NULL || (*head)->next == NULL )
	{
		return;
	}

	/* 1. 리스트 분할 */ // Divide
	splitList( *head, &front_split_head, &back_split_head );

	mergeSort( &front_split_head );
	mergeSort( &back_split_head );

	/* 2. 병합 */ // Conquer
	*head = merge( front_split_head, back_split_head );
}

void freeAll( Node* head )
{
	Node* p = head;
	Node* next = NULL;

	while( p != NULL )
	{
		next = p->next;
		free( p );
		p = next;
	}
}

void* thread_func( void* arg )
{
	List list = *((List*)arg);

	mergeSort( &list.head );
	display( list.head );
	freeAll( list.head );

	return NULL;
}


/*
<왜 연결 리스트에서는 퀵 소트를 사용하지 않는가?>

자세히 설명하자면 LinkedList 는 삽입 및 삭제 연산에 있어, 유용하지만 접근 연산에 있어서는 유용하지않는다.

배열의 경우에는 인덱스를 통해 접근하기 때문에 시간복잡도가 O(1) 이지만, LinkedList 는 Head부터 탐색해야하기때문에 O(n) 이다.

그렇기에, 임의적인 접근에 있어서는 오버헤드가 증가한다.

이러한 이유로 LinkedList 는 순차적인 접근과 같은 합병정렬을 사용하는 것이 유용하다

출처: https://mygumi.tistory.com/309 [마이구미의 HelloWorld]

*/

/*
<참조 코드>

https://www.geeksforgeeks.org/merge-sort-for-linked-list/

*/
