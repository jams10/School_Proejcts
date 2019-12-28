#include <stdio.h>
#include <stdlib.h>
#include "op1.h"
#include "node.h"

// head 포인터가 가리키는 값을 다루기 위해 이중 포인터 사용
void deleteWord(Node** head, int n, int* len) {
	int count = 1;
	Node* p, * q;
	if (*head == NULL) {
		printf("삭제할 단어가 없습니다.\n");
		return;
	}
	p = *head;
	if (n == 1) {
		p = *head;
		*head = (*head)->next;
		free(p);
		return;
	}
	else {
		while (count < n - 1) {
		p = p->next;		
		count++; 									
		}																					q = p->next;
		p->next = q->next;
		free(q);
	}																					*len-=1;
	return;
}
