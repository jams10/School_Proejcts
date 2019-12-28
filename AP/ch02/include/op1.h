#ifndef __OP1_H
#define __OP1_H
#include<stdio.h>
#include<stdlib.h>
#include "node.h"

extern Node* createNode(); // 노드 생성 함수
extern void addWord(Node** head, Node* newWord, int* len); // 단어 추가 함수
extern void deleteWord(Node** head, int n, int* len); // 단어 삭제 함수

#endif


