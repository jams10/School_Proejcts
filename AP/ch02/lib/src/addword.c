#include <stdio.h>
#include <stdlib.h>
#include "op1.h"
#include "node.h"

// head 포인터가 가리키는 값을 다루기 위해 이중 포인터 사용
void addWord(Node** head, Node* newWord, int* len) {
	Node* p = *head; // p는 head가 가리키는 노드 즉, head 포인터의 값을 의미.

	if (p == NULL) {
		*head = newWord;
	}
	else {
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = newWord;
	}
	*len+=1;
	return;
}
