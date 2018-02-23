



#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char **argv){

  struct flock c;
  int fd = open(argv[1], O_WRONLY | O_CREAT, 0777);

  c.l_type = F_WRLCK; c.l_whence = SEEK_SET; c.l_start = 0; c.l_len = 0;
  fcntl(fd, F_GETLK, &c);

  if(c.l_type == F_UNLCK){
    c.l_type = F_WRLCK;
    fcntl(fd, F_SETLK, &c);

    time_t tm1 = time(NULL);
    struct tm *tm = localtime(&tm1);
    char buffer[256];
    strftime(buffer, 256, "%c %r\n", tm);

    write(fd, &buffer, strlen(buffer));

    c.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &c);
  }

  close(fd);
  return 0;
}
