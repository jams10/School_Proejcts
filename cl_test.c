#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main(int argc, char **argv)
{
        if(argc != 3)
        {
                printf("usage : %s ip_Address port\n", argv[0]);
                exit(0);
        }

        int client_sock;

        if((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
                perror("socket error : ");
                exit(1);
        }

        struct sockaddr_in client_addr;
        int client_addr_size = sizeof(client_addr);
        client_addr.sin_family = AF_INET;
        client_addr.sin_addr.s_addr = inet_addr(argv[1]);
        client_addr.sin_port = htons(atoi(argv[2]));

        if(connect(client_sock, (struct sockaddr*)&client_addr, client_addr_size) < 0)
        {
                perror("connect error : ");
                exit(1);
        }

        char buf[BUF_SIZE];
        while(1)
        {
                memset(buf, 0x00, sizeof(buf));
                printf("write : ");

                fgets(buf, sizeof(buf), stdin);
                buf[strlen(buf)-1] = '\0';

                if(write(client_sock, buf, sizeof(buf)) <= 0)
                {
                        close(client_sock);
                        break;
                }

                memset(buf, 0x00, sizeof(buf));
                if (read(client_sock, buf, sizeof(buf)) <= 0)
                {
                        close(client_sock);
                        break;
                }

                printf("read : %s\n", buf);
        }

        return 0;
}
