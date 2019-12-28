#include <stdio.h>
#include <stdlib.h>
#include "op2.h"
#include "node.h"

void frame() {
	Node* head = NULL;
	Node* tmp = NULL;
	menu(&head,&tmp);
				  
	// 동적 할당 받은 노드들 순차적으로 해제
	tmp=head;
	head=head->next;
	while(tmp->next!=NULL){
		free(tmp);
		tmp=head;
		head=head->next;
	}
	tmp=NULL;
	free(head);
	return;
}
