#ifndef __NODE_H
#define __NODE_H
#include<stdio.h>
#include<stdlib.h>

// 단어 스펠링과 뜻을 저장할 Word 구조체
typedef struct Word {
	char eng[25];
	char kor[50];
}Word;

// 연결 리스트를 만들기위한 Node 구조체
typedef struct Node {
	struct Node* next;
	Word word;
}Node;

#endif
