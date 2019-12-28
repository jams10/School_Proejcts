#include "menu.h"
#include "search.h"

char filedate[32];
int check_exist;
char current_file[32];

void menu(){
	char s1[10];
	int flags = 0;
	printf("%c[1;32m",27);
	printf("<<News Classification>>\n");
	printf("%c[0m",27);
	while(1){
		printf("Type date of file (q is Quit) : ");

		scanf("%s",s1);
		sprintf(filedate,"%s",s1);
		if(strcmp("q",s1) == 0) break;
		else{
			sprintf(current_file,"%s",s1);
			if(nftw(".",check_file,20,flags) == -1){
				perror("nftw");
				return;
			}
			if(check_exist != 1){
				fprintf(stderr,"There is no file\n");
			}
			else if(check_exist == 1){
				sprintf(current_file,"%s.txt",s1);
				work();
				check_exist = 0;
			}
		}
	}
	printf("%c[1;31m",27);
	printf("Terminated...\n");
	printf("%c[0m",27);
}


