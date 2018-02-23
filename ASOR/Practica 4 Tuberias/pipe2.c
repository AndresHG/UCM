



#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>

#define rpipe 0
#define wpipe 1

int main(int argc, char ** argv){

  int p_h[2];
  int h_p[2];
  int result = pipe(p_h);
  result = pipe(h_p);

  //Caso de error
  if(result == -1){
    perror("Error al crear el pipe");
    return 0;
  }

  long bytes;
  pid_t pid = fork();
  switch(pid){
  case -1:
    printf("Error al crear el hijo");
    break;

  case 0: //Caso del hijo
    close(p_h[wpipe]);
    close(h_p[rpipe]);
    int cont = 0;

    char buffer[88];
    while(1){
      bytes = read(p_h[rpipe], &buffer, 87);
      printf("Hijo: %s\n", buffer);

      sleep(1);
      if(cont < 10) write(h_p[wpipe], "l", 1);
      else {
        write(h_p[wpipe], "q", 1);
        close(h_p[wpipe]);
        exit(0);
      }
      cont++;
    }
    break;

  default:
    close(p_h[rpipe]);
    close(h_p[wpipe]);

    char r_user[87];
    char r_child[2];
    r_child[0]='l';

    while(r_child[0] != 'q'){
      bytes = read(0, &r_user, 86);
      r_user[bytes] = '\0';

      write(p_h[wpipe], &r_user, bytes +1);
      bytes = read(h_p[rpipe], &r_child, 1);
    }
  }
  printf("\nAdios!\n");

  return 0;
}
