#include "t_funcs.h"
#include "menu.h"
#include "work.h"

pthread_mutex_t rlock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cons = PTHREAD_COND_INITIALIZER;

void* thread_ori(void *arg){	       
	fileinfo *fp = (fileinfo*) arg;
	char buffer[32];
	int i=0;

	for(;;){
		pthread_mutex_lock(&rlock);
		while(fp->turn !=0)
			pthread_cond_wait(&cons,&rlock);
		while(fgets(buffer, sizeof(buffer), fp->ori)){
			if(strstr(buffer,"<<Sports>>") != NULL){
				for(i=0; i<30; i++){
					if(buffer[i]=='>' && buffer[i+1]=='>' && buffer[i+2]=='\n'){		 
						fseek(fp->ori,(32-i+2)*-1,SEEK_CUR);
						break;
					}
				}
				fp->turn = 1;			 
				break;
			}
			if(strstr(buffer,"<<Entertainment>>") != NULL){
				for(i=0; i<30; i++){
					if(buffer[i]=='>' && buffer[i+1]=='>' && buffer[i+2]=='\n'){
						fseek(fp->ori,(32-i+2)*-1,SEEK_CUR);
						break;
					}
				}
				fp->turn = 2;
				break;
			}
			if(strstr(buffer,"<<Society>>") != NULL){
				for(i=0; i<30; i++){
					if(buffer[i]=='>' && buffer[i+1]=='>' && buffer[i+2]=='\n'){		
						fseek(fp->ori,(32-i+2)*-1,SEEK_CUR);
						break;
					}
				}
				fp->turn = 3;
				break;
			}
		}
		pthread_cond_broadcast(&cons);
		pthread_mutex_unlock(&rlock);						               
		if(fgets(buffer,sizeof(buffer), fp->ori) == NULL) break;	
	}
        pthread_exit(0);
}


void* thread_spo(void *arg){
	fileinfo *fp = (fileinfo*) arg;
	char buffer[32];

	for(;;){
		pthread_mutex_lock(&rlock);
		while(fp->turn !=1)
			pthread_cond_wait(&cons,&rlock);
		fprintf(fp->spo,"##%s##\n",filedate);
		while(fgets(buffer, sizeof(buffer), fp->ori)){
			if(buffer[0]=='='){
				fprintf(fp->spo,"\n");
				fclose(fp->spo);
				break;
			}
			fprintf(fp->spo,"%s",buffer);
		}
		fp->turn = 0;
		pthread_cond_broadcast(&cons);
		pthread_mutex_unlock(&rlock);
		break;
	}
	pthread_exit(0);
}


void* thread_ent(void *arg){
	fileinfo *fp = (fileinfo*) arg;
	char buffer[32];

	for(;;){
		pthread_mutex_lock(&rlock);
		while(fp->turn !=2)
			pthread_cond_wait(&cons,&rlock);
		fprintf(fp->ent,"##%s##\n",filedate);
		while(fgets(buffer, sizeof(buffer), fp->ori)){
			if(buffer[0]=='='){
				fprintf(fp->ent,"\n");
				fclose(fp->ent);
				break;
			}
			fprintf(fp->ent,"%s",buffer);
		}
		fp->turn = 0;
		pthread_cond_broadcast(&cons);
		pthread_mutex_unlock(&rlock);
		break;
	}
	pthread_exit(0);
}


void* thread_soc(void *arg){
	fileinfo *fp = (fileinfo*) arg;
	char buffer[32];

	for(;;){
		pthread_mutex_lock(&rlock);
		while(fp->turn !=3)
			pthread_cond_wait(&cons,&rlock);
		fprintf(fp->soc,"##%s##\n",filedate);
		while(fgets(buffer, sizeof(buffer), fp->ori)){
			if(buffer[0]=='='){
				fprintf(fp->soc,"\n");
				fclose(fp->soc);
				break;
			}
			fprintf(fp->soc,"%s",buffer);
		}
		fp->turn = 0;
		pthread_cond_broadcast(&cons);
		pthread_mutex_unlock(&rlock);
		break;
	}
	pthread_exit(0);
}
































