
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char ** argv){

  char tub1[9] = "tuberia1";
  char tub2[9] = "tuberia2";
  fd_set set;
  char buf[257];
  int fd_tub, num_tub, c;

  mkfifo(tub1, 0777); // Create fifos
  mkfifo(tub2, 0777);

  int fd1 = open(tub1, O_RDONLY | O_NONBLOCK); // Open fifos
  int fd2 = open(tub2, O_RDONLY | O_NONBLOCK);

  while(1){
    FD_ZERO(&set); // Fill set struct
    FD_SET(fd1, &set);
    FD_SET(fd2, &set);

    int rc = select((fd2 > fd1) ? fd2+1 : fd1+1, &set, NULL, NULL, NULL); // Select wich fd is ready to read

    if(FD_ISSET(fd1, &set)){ // Select current fifo
      fd_tub = fd1;
      num_tub = 1;
    } else {
      fd_tub = fd2;
      num_tub = 2;
    }

    while((c = read(fd_tub, buf, 256)) != 0){ // Read until close fifo
      buf[c] = '\0';
      printf("Tubería %i: %s", num_tub, buf);
    }

    if(num_tub == 1){ // Restar fifos
      close(fd1);
      fd1 = open(tub1, O_RDONLY | O_NONBLOCK);
    } else {
      close(fd2);
      fd2 = open(tub2, O_RDONLY | O_NONBLOCK);
    }
  }
  return 0;
}
