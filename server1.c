#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int arg, char **npv)
{
    if (arg > 0)
    {
        int lcliente, puerto, fd1, fd2;
        puerto = atoi(npv[1]);
        int nbyte;
        char buf[100];

        struct sockaddr_in server, cliente;
        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(puerto);
        server.sin_addr.s_addr = INADDR_ANY;

        if ((fd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("Error: Couldn't open socket \n");
            return -1;
        }
        if (bind(fd1, (struct sockaddr*)&server, sizeof(server)) == -1)
        {
            printf("Error: Couldn't set sockets's IP and Port number \n");
            return -1;
        }
        if (listen(fd1, 3) == -1)
        {
            printf("Error: Couldn't define socket as pasive \n");
            return -1;
        }

        lcliente = sizeof(cliente);

        while (1)  
        {
            fd2 = accept(fd1, (struct sockaddr *)&cliente, &lcliente);
            if (fd2 < 0)
            {
                printf("Error: Couldn't accept connection \n");
                return -1;
            }

            send(fd2, "Welcome to the server \n", 26, 0);

            if ((nbyte = recv(fd2, buf, 100, 0)) == -1)
            {
                printf("Error: Couldn't receive message \n");
            }

            buf[nbyte] = '\0';
            printf("Client message: %s \n", buf);
            close(fd2);
        }
    }
    else
    {
        printf("Number wasn't entered at the port \n");
    }
    return 0;
}