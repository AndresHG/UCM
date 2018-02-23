#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char **argv)
{
    int rc;
    struct addrinfo hints;
    struct addrinfo * res;
    struct addrinfo * i;

    struct sockaddr client;
    socklen_t clen = sizeof(struct sockaddr);

    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    char buffer[80];

    memset(&hints, 0, sizeof(struct addrinfo)); 

    hints.ai_flags    = AI_PASSIVE;
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    rc = getaddrinfo(argv[1], argv[2], &hints, &res);

    if ( rc != 0 )
    {
        printf("getaddrinfo(): %s\n", gai_strerror(rc));
        return -1;
    }

    int sd;

    sd = socket(res->ai_family, res->ai_socktype, 0);

    bind(sd, res->ai_addr, res->ai_addrlen);

    while(1)
    {
        fd_set fds;
        ssize_t bytes;

        FD_ZERO(&fds);
        FD_SET(0, &fds);
        FD_SET(sd, &fds);

        select(sd+1, &fds, NULL, NULL, NULL);

        if ( FD_ISSET(0, &fds) )
        {
            bytes = read(0, buffer, 79);
            buffer[bytes]='\0';

            printf("TECLADO: %s\n", buffer);
        }
        else
        {
            bytes = recvfrom(sd,buffer, 79, 0, &client, &clen);

            buffer[bytes] = '\0';

            getnameinfo(&client, clen, host, NI_MAXHOST, serv,
                    NI_MAXSERV, NI_NUMERICHOST);

            printf("IP: %s (%s)\n", host, serv);
            printf("MENSAJE: %s\n", buffer);

            sendto(sd, buffer, bytes, 0, &client, clen);
        }
    }


    return 0;
}
