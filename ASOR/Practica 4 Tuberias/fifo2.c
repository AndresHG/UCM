


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

#define MAX_BUF 256

int main(int argc, char ** argv){

  char * fifo = "./fifo1";
  char * fifo2 = "./fifo2";

  mkfifo(fifo, 0666);
  mkfifo(fifo2, 0666);

  char buffer[MAX_BUF];
  fd_set set;
  ssize_t bytes;

  int fd = open(fifo, O_RDONLY | O_NONBLOCK);
  int fd2 = open(fifo2, O_RDONLY | O_NONBLOCK);

  int sel_fd, sel_pipe;

  while(1){

    FD_ZERO(&set);
    FD_SET(fd, &set);
    FD_SET(fd2, &set);
    bytes = MAX_BUF;

    int rc = select((fd2 > fd) ? fd2+1 : fd+1, &set, NULL, NULL, NULL);

    if(FD_ISSET(fd, &set)){
      sel_fd = fd;
      sel_pipe = 1;
    } else {
      sel_fd = fd2;
      sel_pipe = 2;
    }

    while(bytes == MAX_BUF){
      bytes = read(sel_fd, buffer, MAX_BUF);
      buffer[bytes] = '\0';
      if(buffer[0] == 'q' && strlen(buffer) < 4){
        close(fd);
        close(fd2);
        unlink(fifo);
        unlink(fifo2);
        exit(0);
      }
      printf("Pipe: %i: %s", sel_pipe, buffer);
    }

    if(sel_pipe == 1){
      close(fd);
      fd = open(fifo, O_RDONLY | O_NONBLOCK);
    } else {
      close(fd2);
      fd2 = open(fifo2, O_RDONLY | O_NONBLOCK);
    }
  }

  return 0;
}
