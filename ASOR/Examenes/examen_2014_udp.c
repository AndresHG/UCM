
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

volatile int hijo1 = 0;
volatile int hijo2 = 0;

void handler(int signal){
  //Save last errno
  int saved_errno = errno;

  // Select signal recived
  if(signal == SIGUSR1){
    hijo1++;
    printf("[PADRE] Petición tratada por hijo 1 (total: %i)\n", hijo1);
  } else if(signal == SIGUSR2){
    hijo2++;
    printf("[PADRE] Petición tratada por hijo 2 (total: %i)\n", hijo2);
  }
  // Restore last errno
  errno = saved_errno;
}

int main(int argc, char ** argv){

  struct addrinfo hints, *res;
  struct sockaddr_storage cli;
  char buf[2], host[NI_MAXHOST], serv[NI_MAXSERV];

  // Initialize hints
  hints.ai_family = AF_UNSPEC;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_protocol = 0;

  // Initialize signal handler
  struct sigaction act;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_RESTART;
  act.sa_handler = handler;

  sigaction(SIGUSR1, &act, NULL);
  sigaction(SIGUSR2, &act, NULL);

  int getadd = getaddrinfo(argv[1], argv[2], &hints, &res);
  if(getadd != 0){
    gai_strerror(getadd);
  }

  // Set conection's socket
  int sd = socket(res->ai_family, res->ai_socktype, 0);
  bind(sd, (struct sockaddr *)res->ai_addr, res->ai_addrlen);
  freeaddrinfo(res);
  socklen_t clen = sizeof(cli);

  for(int i=0; i < 2; i++){ // Create 2 children
    pid_t pid = fork();

    switch(pid){
    case -1: //Case error
      perror("Error al crear el proceso hijo.");
      exit(0);
    case 0: //Case child
      while(1){
        char to_send[256];
        int bytes;

        // Recive client data in "buf"
        int c = recvfrom(sd, buf, 2, 0, (struct sockaddr *)&cli, &clen);
        buf[c] = '\0';

        getnameinfo((struct sockaddr *)&cli, clen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);

        // Display client info
        printf("[H:%i,%i]   Host:%s   Puerto:%s\n", getpid(), i+1, host, serv);

        //Send signal to father, new message in progress
        if (i == 0) kill(getppid(), SIGUSR1);
        else kill (getppid(), SIGUSR2);

        // Server options to build "send data"
        if(buf[0] == 'a')
          bytes = sprintf(to_send, "%s\n", host);
        else if(buf[0] == 'p')
          bytes = sprintf(to_send, "%s\n", serv);
        else if(buf[0] == 'q')
          break;
        else
          bytes = sprintf(to_send, "Comando no encontrado...\n");

        // Send data to client
        sendto(sd, to_send, bytes, 0, (struct sockaddr *)&cli, clen);
      }
      close(sd);
      exit(0);
    }
  }
  close(sd);
  /* sleep(300); */
  int status;
  while(waitpid((pid_t)-1, &status, 0) > 0){
    printf("[PADRE] Terminó hijo con código de salida %i\n", status);
  }

  return 0;
}
