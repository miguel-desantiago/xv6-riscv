#include "kernel/types.h"
#include "user/user.h"

#define NCHILD 3

int
main(int argc, char *argv[])
{
  int pids[NCHILD];
  int prios[NCHILD];
  int start = uptime();

  // Parent runs at the highest priority so it can create every child
  // before they start competing, and can report each finish right away.
  setpriority(49);

  for (int i = 0; i < NCHILD; i++) {
    int prio = i * 10;            // children get priorities 0, 10, 20
    int pid = fork();
    if (pid < 0) {
      printf("fork failed\n");
      exit(1);
    }
    if (pid == 0) {
      // Child: lower its own priority, then become matmul (CPU-heavy work)
      setpriority(prio);
      char *args[] = { "matmul", 0 };
      exec("matmul", args);
      printf("exec failed\n");
      exit(1);
    }
    // Parent: remember which priority this child has
    pids[i] = pid;
    prios[i] = prio;
  }

  // wait() returns the pid of whichever child finished, so the
  // order of these lines is the finishing order.
  for (int i = 0; i < NCHILD; i++) {
    int done = wait(0);
    int prio = -1;
    for (int j = 0; j < NCHILD; j++)
      if (pids[j] == done)
        prio = prios[j];
    printf("pid %d (priority %d) finished at %d ticks\n",
           done, prio, uptime() - start);
  }

  exit(0);
}
