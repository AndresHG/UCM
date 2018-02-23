

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


int main(int argc, char ** argv){

  struct addrinfo hints, *res;
  struct sockaddr_storage cli;
  socklen_t clen = sizeof(cli);
  char buf[81], host[NI_MAXHOST], serv[NI_MAXSERV], to_send[NI_MAXHOST+15]; // 15 = "Tu direccion: %s\n"

  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_protocol = 0;

  getaddrinfo(argv[1], argv[2], &hints, &res);
  int sd = socket(res->ai_family, res->ai_socktype, 0);
  bind(sd, (struct sockaddr *)res->ai_addr, res->ai_addrlen);
  freeaddrinfo(res);

  while(1){

    int c = recvfrom(sd, buf, 80, 0, (struct sockaddr *)&cli, &clen);
    getnameinfo((struct sockaddr *)&cli, clen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

    printf("Cliente con Host:%s Puerto:%s\n", host, serv);

    int tc = sprintf(to_send, "Tu direccion: %s\n", host);
    sendto(sd, to_send, tc, 0, (struct sockaddr *)&cli, clen);
  }
}
