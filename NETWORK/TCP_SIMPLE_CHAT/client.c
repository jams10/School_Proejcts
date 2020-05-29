#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <error.h>

#define BUFSIZE 512

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage : %s <IP> <PORT>\n", argv[0]);
		exit(1);
	}
	
	struct hostent *host;
	host = gethostbyname(argv[1]);
	char *ip = inet_ntoa( *(struct in_addr*)host->h_addr_list[0]);	
	
	if((host = gethostbyname(argv[1]) == NULL))
	{
		printf("%s is invalid domain\n",argv[1]);
		exit(1);
	}
	
	// socket()
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		printf("Client : Create socket error\n");
		exit(1);
	}

	// set address structure
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_port = htons(atoi(argv[2]));

	// connect()
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
	{
		printf("Client : Connect error\n");
		exit(1);
	}

	// variables for data communication
	char buf[BUFSIZE+1];
	int len;
	int retval;

	printf("If you type \"close\", close the client.\n");	
	while(1)
	{
		// type data
		printf("\n[To Server] ");
		if(fgets(buf, BUFSIZE+1, stdin) == NULL) break;
		
		if((strncmp(buf, "close", 5)) == 0)
		{
			printf("Close the client...\n");
			break;
		}
		// remove '\n' letter
		len = strlen(buf);
		if(buf[len-1] == '\n') buf[len-1] = '\0';
		if(strlen(buf) == 0) break;

		// send()
		retval = send(sock, buf, strlen(buf), 0);
		if(retval < 0)
		{
			printf("Client : Send error\n");
			exit(1);
		}

		// receive()
		retval = recv(sock, buf, BUFSIZE, 0);
		if(retval < 0)
		{
			printf("Client : receive error\n");
			exit(1);
		}
		else if(retval == 0 || (strncmp(buf, "close", 5)) == 0)
		{
			break;
		}

		// print received data
		//buf[retval] = '\0';
		printf("[From Server] %s\n", buf);
	}

	// close()
	close(sock);
	return 0;
}
