#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "op1.h"
#include "node.h"

Node* createNode() {
	char eng[25];
	char kor[50];
	Node* p = (Node*)malloc(sizeof(Node));
	printf("단어의 스펠링 : ");
	scanf("%s", eng);
	strcpy(p->word.eng, eng);
	printf("단어의 뜻 : ");
	scanf("%s", kor);
	strcpy(p->word.kor, kor);
	
	p->next = NULL;

	return p;
}
