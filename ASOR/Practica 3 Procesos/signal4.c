

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int ctrl_c;
volatile int ctrl_z;

void handler(int signal){
  if (signal == SIGINT)
    ctrl_c++;
  else
    ctrl_z++;
}

int main(int argc, char ** argv){

  struct sigaction sa;

  ctrl_c = 0;
  ctrl_z = 0;

  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;

  sigaction(SIGINT, &sa, NULL);
  sigaction(SIGTSTP, &sa, NULL);

  while(ctrl_c + ctrl_z < 10){
    sleep(5);
  }
  printf("Numero de control C %d\n", ctrl_c);
  printf("Numero de control Z %d\n", ctrl_z);

  return 0;
}
