#include <stdio.h>
#include <stdlib.h>
#include "op2.h"
#include "node.h"

void printWord(Node* head) {
	Node* p = head;
	int n = 1;
	if (p == NULL) {
		printf("표시할 단어가 없습니다.\n");
	}
	while (p != NULL) {
		printf("%d. %s : %s\n", n, p->word.eng, p->word.kor);
		p = p->next;
		n++;
	}
	return;
}
