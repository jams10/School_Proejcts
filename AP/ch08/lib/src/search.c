#include "search.h"

int check_exist=0;
char current_file[32];


int check_file(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf){
	char buf[32];

	switch(tflag){
		case FTW_D:
			break;
		case FTW_F:
			sprintf(buf, "%s", fpath);
			if(strstr(buf,current_file) != NULL) check_exist = 1;
			break;
	}
		return 0;
}

