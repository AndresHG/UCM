
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char ** argv){

  int last_prio = getpriority(PRIO_PROCESS, getpid());
  nice(-(last_prio + 10));

  struct sched_param param;
  param.sched_priority = 12;

  int result = sched_setscheduler(getpid(), SCHED_FIFO, param);
  if(result == -1)
    perror("Error during setting scheduler");

  return 0;
}
