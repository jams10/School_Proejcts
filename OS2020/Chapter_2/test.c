#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
int main()
{	
	int fd = open("/tmp/file", O_WRONLY | O_CREAT| O_TRUNC, S_IRWXU);
	if(fd < 0)
	{
		printf("Opening file : Failed\n");
		printf("Error no is : %d\n",errno);
		printf("Error description is : %s\n",strerror(errno));
	}
	else
	{
		printf("File Open Success\n");
	}
}
