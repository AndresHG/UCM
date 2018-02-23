

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define rpipe 0
#define wpipe 1

int main(int argc, char ** argv){

  int pipefds[2];
  int result = pipe(pipefds);

  //Caso de error
  if(result == -1){
    perror("Error al crear el pipe");
    return 0;
  }

  pid_t pid = fork();
  switch(pid){
  case -1:
    printf("Error al crear el hijo");
    break;

  case 0: //Caso del hijo
    close(pipefds[wpipe]);
    dup2(pipefds[rpipe], 0);

    execlp(argv[3], argv[3], argv[4], NULL);
    exit(0);

  default:
    close(pipefds[rpipe]);
    dup2(pipefds[wpipe], 1);

    execlp(argv[1], argv[1], argv[2], NULL);
    }

  return 0;
}
