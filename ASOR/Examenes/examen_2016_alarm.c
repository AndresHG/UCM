

#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void handler(int signal){
  int saved_errno = errno;
  printf("Efecutando tarea programada\n");
  errno = saved_errno;
}

int main(int argc, char ** argv){

  int secsw = atoi(argv[1]);

  pid_t pid = fork();

  if(pid == -1){
    perror("Error al crear el hijo");
    return 0;
  }
  else if(pid == 0){

    sigset_t suspend;
    struct sigaction act;

    sigemptyset(&act.sa_mask);
    act.sa_handler = handler;
    act.sa_flags = SA_RESTART;

    sigaction(SIGALRM, &act, NULL);
    /* sigemptyset(&suspend); */
    sigfillset(&suspend);
    sigdelset(&suspend, SIGALRM);
    alarm(secsw);

    sigsuspend(&suspend);

    int fd = open("examen.out", O_RDWR | O_CREAT, 0666);
    dup2(fd, 1); // Redirect standar output to fd

    execvp(argv[2], argv+2); // Execute args command
    close(fd);
    exit(0);
  }
  else
    printf("Ejecución programada en %s segundos por el proceso %i\n", argv[1], pid);
  
  return 0;
}
