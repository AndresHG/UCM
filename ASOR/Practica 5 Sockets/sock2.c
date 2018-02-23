


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

  int rc;
  struct addrinfo hints;
  struct addrinfo * res;
  struct addrinfo * i;

  struct sockaddr_storage client;
  socklen_t clen = sizeof(struct sockaddr_storage);

  char host[NI_MAXHOST];
  char serv[NI_MAXSERV];

  char buffer[2];

  memset(&hints, 0, sizeof(struct addrinfo));

  hints.ai_flags = AI_PASSIVE;
  hints.ai_socktype = SOCK_DGRAM;

  rc = getaddrinfo(argv[1], argv[2], &hints, &res);

  if (rc != 0){
    printf("getaddrinfo(): %s\n", gai_strerror(rc));
    return -1;
  }

  int sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  bind(sd, (struct sockaddr *) res->ai_addr, res->ai_addrlen);

  freeaddrinfo(res);

  while(1){

    size_t bytes = recvfrom(sd, buffer, 1, 0, &client, &clen);

    buffer[1] = '\0';
    getnameinfo( (struct sockaddr *) &client, clen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
    printf("Recibí %ld byte(s) de %s(%s)\n", bytes, host, serv);

    time_t tiempo = time(NULL);
    struct tm *tm = localtime(&tiempo);
    size_t max = 50*sizeof(char);
    char s[50];

    if(buffer[0] == 'd'){

      ssize_t bytesT = strftime(s, max, "%A %d - %B - %Y", tm);

			sendto(sd, s, bytesT,
             0, (struct sockaddr *) &client, clen);
    } else if (buffer[0] == 't'){

      ssize_t bytesT = strftime((char *)s, max, "%I:%M:%S %p", tm);
			s[bytesT] = '\0';

      sendto(sd, s, bytesT, 0, (struct sockaddr *) &client, clen);
    } else if (buffer[0] == 'q'){

      sendto(sd, "Finalizando la conexión...\0", 27, 0, (struct sockaddr *) &client, clen);
      break;
    } else {

      sendto(sd, "Comando no soportado...\0", 24, 0, (struct sockaddr *) &client, clen);
    }
  }

  return 0;
}
