




#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <fcntl.h>

int main(int argc, char **argv) {

  printf("SID: %i\n", getsid(getpid()));
  pid_t pid = fork();

  if(pid == 0){

    setsid();

    printf("SID: %i\n", getsid(getpid()));
    printf("PID: %i\n", getpid());
    printf("PPID: %i\n", getppid());
    printf("PGID: %i\n", getpgid(getpid()));
    printf("SID: %i\n", getsid(getpid()));

    struct rlimit limit;
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
      perror("Unable to get the resource limits");
      return -1;
    }
    printf("LIMIT: %llu\n", limit.rlim_max);

    chdir("/tmp");

    char *path = malloc(sizeof(char)*(4096 + 1));
    /* char path[256]; */
    char *rpath = getcwd(path, 4096 + 1);
    printf("CWD: %s\n", path);
    free (path);

    int fd = open("/tmp/daemon.log", O_WRONLY | O_CREAT);
    int fderr = open("/tmp/daemon.err", O_WRONLY | O_CREAT);
    int fdin = open("/tmp/null", O_RDWR | O_CREAT);

    dup2(fd, 1);
    dup2(fderr, 2);
    dup2(fdin, 0);

    execvp(argv[1], argv+1);

    exit(0);
  } else {
    /* int status; */
    while(waitpid(-1, 0, 0) > 0){}
    printf("EL hijo terminó\n");
  }

  return 0;
}
