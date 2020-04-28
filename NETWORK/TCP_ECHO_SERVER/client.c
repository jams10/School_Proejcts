#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <error.h>

#define BUFSIZE 512

int recvn(int s, char *buf, int len, int flags)
{
	int received;
	char *ptr = buf;
	int left = len;

	while(left > 0)
	{
		// recv()
		received = recv(s, ptr, left, flags);
		if(received < 0)
		{
			return -1;
		}
		else if(received == 0) break;

		left -= received;
		ptr += received;
	}

	return (len - left);
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage : %s <IP> <PORT>\n", argv[0]);
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
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
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

	while(1)
	{
		// type data
		printf("\n[data] ");
		if(fgets(buf, BUFSIZE+1, stdin) == NULL) break;
		
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
		printf("[TCP Client] Send %d byte.\n", retval);

		// receive()
		retval = recvn(sock, buf, retval, 0);
		if(retval < 0)
		{
			printf("Client : receive error\n");
			exit(1);
		}
		else if(retval == 0) break;

		// print received data
		buf[retval] = '\0';
		printf("[TCP Client] Received %d byte.\n", retval);
		printf("[data] %s\n", buf);
	}

	// close()
	close(sock);
	return 0;
}
