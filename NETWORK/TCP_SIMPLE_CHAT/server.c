#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Use memset
#include <sys/socket.h>
#include <arpa/inet.h> // Use transform address function
#include <error.h> // Check error

#define BUFSIZE 512

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage:%s <port>\n",argv[0]);
	}

	// socket()
	int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(serv_sock < 0)
	{
		printf("Server : Can't Create Socket\n");
		exit(1);
	}

	// set address structure
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	// bind()
	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("Server : Bind error\n");
		exit(1);
	}

	// listen()
	if(listen(serv_sock, 5) < 0)
	{
		printf("Server : Listen error\n");
		exit(1);
	}

	// variables for data communication
	int clnt_sock;
	int retval;
	struct sockaddr_in clnt_addr;
	socklen_t clntLen;
	char buf[BUFSIZE+1];
	int len = 0;
	int status = 0; // connection status for closing

	printf("If you type \"close\", close the server\n");	
	while(1)
	{	
		clntLen = sizeof(clnt_addr);
		// accpet()
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clntLen);
		if(clnt_sock < 0)
		{
			printf("Server : Accept error\n");
			exit(1);
		}

		// print client info
		printf("\n[TCP Server] Client Connected : IP Address=%s, Port Number=%d\n",
				inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
		
		// communicate with client
		while(1)
		{
			retval = recv(clnt_sock, buf, BUFSIZE, 0);
			if(retval < 0)
			{
				printf("Server : Receive error\n");
				break;
			}
			else if(retval == 0 || (strncmp(buf, "close", 5) == 0))
			{
				status = 1;
				break;
			}
			
			// print received data
			buf[retval] = '\0';
			printf("[From Server] %s\n", buf);
			
			// type data
			memset(buf, 0, sizeof(buf));
			printf("\n[To Client] : ");
			if(fgets(buf, BUFSIZE+1, stdin) == NULL) break;
			
			if(strncmp(buf, "close", 5) == 0)
			{
				status = 1;
				printf("Close Server...\n");
				break;
			}	
			// remove '\n' letter
			len = strlen(buf);
			if(buf[len-1] == '\n') buf[len-1] = '\0';
			if(strlen(buf) == 0) break;

			// send
			retval = send(clnt_sock, buf, BUFSIZE, 0);
			if(retval < 0)
			{
				printf("Server : Send error\n");
				break;
			}
		}
		
		// close client
		close(clnt_sock);
		printf("[TCP Server] Client Closed : IP Address=%s, Port Number=%d\n",
				inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));
		if(status == 1)
		{
			break;
		}
	}

	// close server
	close(serv_sock);
	return 0;
}
