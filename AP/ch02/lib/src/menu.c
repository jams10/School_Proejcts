#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "op1.h"
#include "op2.h"
#include "node.h"

void menu(Node** head, Node** tmp){
	int sel = 0, wh_n = 0, len=0;
	char c[3];
	while (1) {
		printf("<단어장 프로그램>\n");
		printf("1. 단어 추가하기\n");
		printf("2. 단어 삭제하기\n");
		printf("3. 단어 출력하기\n");
		printf("4. 종료\n");
		printf("원하는 작업을 선택하세요 >> ");
		scanf("%d", &sel);
		if (sel == 1) {
			*tmp = createNode();
			addWord(head, *tmp, &len);
		}
		else if (sel == 2) {
			printWord(*head);
			printf("몇 번째 단어를 지우시겠습니까? >>");
			scanf("%d", &wh_n);
			if(wh_n<=len) deleteWord(head, wh_n, &len);
			else{
				printf("저장된 단어의 총 개수 : %d 보다 큽니다.",len);
				sleep(5);
			}
		}
		else if (sel == 3) {
			printWord(*head);
			while(1){
				getchar();
				printf("계속하기(Y)>> ");
				scanf("%s",c);
				if(c[0] =='Y') break;
			}
		}
		else if (sel == 4) {
			break;
		}
		else {
			printf("올바른 번호를 입력해주세요...\n");
		}
		system("clear");
	}
}
