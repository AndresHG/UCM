
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){

    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;

    struct sockaddr_storage peer_addr;

    socklen_t peer_addr_len;
    ssize_t nread;

    int BUF_SIZE = 256;

    char buf[BUF_SIZE];


   memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */

    s = getaddrinfo("www.google.com", NULL, &hints, &result);
   if (s != 0) {
     fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
   }
   /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully bind(2).
       If socket(2) (or bind(2)) fails, we (close the socket
       and) try the next address. */

   for (rp = result; rp != NULL; rp = rp->ai_next) {

     char host[NI_MAXHOST];
     getnameinfo(rp->ai_addr, rp->ai_addrlen, host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

     printf("%s ", host);
     printf("%i ", rp->ai_family);
     printf("%i\n", rp->ai_socktype);

       /* if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) */
            /* break;                  /\* Success *\/ */

   }
   freeaddrinfo(result);
   return 0;
}
