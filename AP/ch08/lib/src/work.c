#include "work.h"
#include "search.h"
#include "menu.h"
#include "t_funcs.h"
void work(){
	pthread_t origin, sport, ent, soc;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

	fileinfo file;
	
	// file structure setting
	file.turn=0;
	if((file.ori = fopen(current_file,"r")) == NULL){
		fprintf(stderr,"ORIGIN FILE OPEN ERROR\n");
		return;
	}
	if((file.spo = fopen("Spo_news.txt","a+")) == NULL){
		fprintf(stderr,"SPORTS FILE OPEN ERROR\n");
		return;
	}
	if((file.ent = fopen("Ent_news.txt","a+")) == NULL){
		fprintf(stderr,"ENT FILE OPEN ERROR\n");
		return;
	}
	if((file.soc = fopen("Soc_news.txt","a+")) == NULL){
		fprintf(stderr,"SOC FILE OPEN ERROR\n");
		return;
	}

	// create threads
	if(pthread_create(&origin, &attr, thread_ori,&file)){
		fprintf(stderr,"pthread_create error\n");
		pthread_exit(0);
	}
	if(pthread_create(&sport, &attr, thread_spo,&file)){
		fprintf(stderr,"pthread_create error\n");
		pthread_exit(0);
	}
	if(pthread_create(&ent, &attr, thread_ent,&file)){
		fprintf(stderr,"pthread_create error\n");
		pthread_exit(0);
	}
	if(pthread_create(&soc, &attr, thread_soc,&file)){
		fprintf(stderr,"pthread_create error\n");								               
		pthread_exit(0);
	}

	pthread_join(origin,(void**)&file);
	pthread_join(sport,(void**)&file);
	pthread_join(ent,(void**)&file);
	pthread_join(soc,(void**)&file);

	fclose(file.ori);
	printf("%c[1;36m",27);
	printf("Classification has been completed!\n");
	printf("%c[0m",27);

	return;
}
