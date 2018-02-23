

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv){


  /* execlp(argv[1], argv[1], argv[2], NULL); */
  execvp(argv[1], argv+1);
  /* system("ls -l"); */
  printf("He vuelto!\n");
  return 0;
}
