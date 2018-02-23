
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>

int main(int argc, char **argv){

  struct addrinfo hints, *res;
  struct sockaddr_storage cli;
  socklen_t clen = sizeof(cli);
  char buf[81], host[NI_MAXHOST], serv[NI_MAXSERV];

  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0;

  getaddrinfo(argv[1], argv[2], &hints, &res);
  int sd = socket(res->ai_family, res->ai_socktype, 0);
  bind(sd, (struct sockaddr *)res->ai_addr, res->ai_addrlen);
  freeaddrinfo(res);

  listen(sd, 5);
  while(1){
    int cli_sd = accept(sd, (struct sockaddr *) &cli, &clen);
    getnameinfo((struct sockaddr *)&cli, clen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

    printf("Conexión desde Host:%s Puerto:%s\n", host, serv);
    dup2(cli_sd, 1); // redirect standard outup

    while(1){
      int c = recv(cli_sd, buf, 80, 0);
      buf[c] = '\0';
      if(buf[0] == 'q' && strlen(buf) == 2){
        break;
      }
      system(buf);
    }
    break;
  }
  return 0;
}
