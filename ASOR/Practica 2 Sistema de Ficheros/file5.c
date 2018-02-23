
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char **argv){

  struct stat stats;
  mode_t o_mask = umask(027);
  int fd = open(argv[1], O_WRONLY | O_CREAT, 0777);
  char buffer[86] = "Hola mundo";
  write(fd, &buffer, strlen(buffer));
  umask(o_mask);

  fstat(fd, &stats);
  printf("%llu\n", stats.st_ino);
  printf("%i\n", stats.st_mode);
  if(S_ISREG(stats.st_mode)){
    printf("Es un archivo regular\n");
  }
  printf("EL major es %li\n", (long) major(stats.st_dev));

  close(fd);

  return 0;
}
