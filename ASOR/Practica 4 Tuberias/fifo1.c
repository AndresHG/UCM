

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char ** argv){

  char * my_fifo = "fifo1";

  mkfifo(my_fifo, 0777);

  int fd = open(my_fifo, O_WRONLY | O_NONBLOCK, 0777);
  write(fd, argv[1], strlen(argv[1]));

  sleep(5);

  close(fd);

  return 0;
}
