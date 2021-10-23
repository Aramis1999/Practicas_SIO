#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int arg, char **ipnpv)
{
    if (arg > 1)
    {
        int puerto, nbyte, fd1;
        char buf[100];
        char *ip;

        ip = ipnpv[1];
        puerto = atoi(ipnpv[2]);

        struct hostent *he;
        if ((he = gethostbyname(ip)) == NULL)
        {
            printf("Error getting IP's values \n");
            return -1;
        }

        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(puerto);
        server.sin_addr = *((struct in_addr*)he->h_addr);

        if ((fd1 = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            printf("Error: Couldn't create socket \n");
            return -1;
        }
        if (bind(fd1, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
            printf("Error: Couldn't connect to server \n");
            return -1;
        }   

        if ((nbyte = recv(fd1, buf, 100, 0)) == -1)
        {
            printf("Error: Couldn't receive serves's message \n");
        }

        buf[nbyte] = '\0';
        printf("Server mesage: %s \n", buf);
        send(fd1, "She doesn't love you", 26, 0);
    }
    else
    {
        printf("Error: Couldn't entered IP and Port number \n");
    }
}