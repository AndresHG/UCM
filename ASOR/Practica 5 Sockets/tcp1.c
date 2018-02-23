

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
#include <time.h>

int main(int argc, char ** argv){

  struct addrinfo hints, *res;
  struct sockaddr_storage cli;
  char host[NI_MAXHOST], serv[NI_MAXSERV];
  char buf[81];

  //All hints needed to select tcp address
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0;

  //Get all info needed to bind socket in addres and socket specify by arguments
  getaddrinfo(argv[1], argv[2], &hints, &res);

  int sd = socket(res->ai_family, res->ai_socktype, 0);
  bind(sd, (struct sockaddr *)res->ai_addr, res->ai_addrlen);
  freeaddrinfo(res);

  //Number of conectiones waiting
  listen(sd, 5);
  socklen_t clen = sizeof(cli);
  int cli_sd;
  ssize_t c;

  //Repeat me plz!
  while(1){

    cli_sd = accept(sd, (struct sockaddr *)&cli, &clen);

    pid_t pid = fork();

    if(pid == 0){
      while(1){
        //Get client info to display
        getnameinfo((struct sockaddr *)&cli, clen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);
        printf("%s %s\n", host, serv);

        //Recive data from client (this will wait until somthing is sent)
        c = recv(cli_sd,  buf, 80, 0);
        buf[c] = '\0';

        //Check if quit server
        if((buf[0] == 'q') && (c == 2)){
          printf("Conexión terminada...\n");
          close(cli_sd);
          exit(0);
        }

        //Send data to client
        send(cli_sd, buf, c, 0);
      }
    } else{ //Caso del padre, cierra cli_sd
      close(cli_sd);
    }
  }

  close(sd);
}
