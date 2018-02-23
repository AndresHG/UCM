


#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char **argv){

  int fd = open(argv[1], O_WRONLY | O_CREAT, 0777);

  dup2(fd, STDOUT_FILENO);
  dup2(fd, 2);

  char buffer[86] = "Hola mundo\n";
  /* write(1, &buffer, strlen(buffer)); */

  /* write(1, "Segunda linea\n", strlen(buffer)); */

  printf("Hola mundo que tal estas?\n");
  close(fd);
  return 0;
}
