


#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int stop;

void handler(int signal){
  if (signal == SIGUSR1)
    stop++;
}

int main(int argc, char ** argv){

  struct sigaction sa;

  stop = 0;

  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;

  sigaction(SIGUSR1, &sa, NULL);

  sleep(atoi(argv[1]));

  if(stop > 0)
    printf("Programa detenido correctamente");
  else{
    unlink(argv[0]);
    printf("Me he auto-borrado...");
  }

  return 0;
}
