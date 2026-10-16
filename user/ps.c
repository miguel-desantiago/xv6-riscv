#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

// Had to make minor change to given code in printf() statements switching %l -> %lu

int
main(int argc, char **argv)
{
  struct pstat uproc[NPROC];
  int nprocs;
  int i;
  char *state;
  static char *states[] = {
    [SLEEPING]  "sleeping",
    [RUNNABLE]  "runnable",
    [RUNNING]   "running ",
    [ZOMBIE]    "zombie  "
  };

  nprocs = getprocs(uproc);
  if (nprocs < 0)
    exit(-1);

  // Get singular endtime for all processes to calculate age
  uint endtime = uptime();

  printf("pid\tstate\t\tsize\tppid\tname\tpriority\tage\n");
  for (i=0; i<nprocs; i++) {
    state = states[uproc[i].state];

    if (uproc[i].state == RUNNABLE){
       printf("%d\t%s\t%lu\t%d\t%s\t%d\t\t%u\n", uproc[i].pid, state,
                   uproc[i].size, uproc[i].ppid, uproc[i].name, uproc[i].priority, endtime-uproc[i].readytime);
    } else{
       printf("%d\t%s\t%lu\t%d\t%s\t%d\n", uproc[i].pid, state,
                   uproc[i].size, uproc[i].ppid, uproc[i].name, uproc[i].priority);
    }
  }

  exit(0);
}
