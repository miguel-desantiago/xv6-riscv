#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  int get_priority_test = getpriority();
  printf("Testing getpriority(): %d\n", get_priority_test);

  int set_priority_valid_test = setpriority(10);
  printf("Testing Valid setpriority(): %d\n", set_priority_valid_test);

  int get_priority_again = getpriority();
  printf("Testing getpriority() with new value: %d\n", get_priority_again);

  int set_priority_invalid_test = setpriority(75);
  printf("Testing setpriority() with invalid value, expect -1: %d\n", set_priority_invalid_test);

  int get_priority_same = getpriority();
  printf("Testing getpriority() after invalid value, expect 10: %d\n", get_priority_same);

  int pid = fork();

  if (pid < 0){
    printf("Fork Failed");
    exit(-1);
  } else if (pid == 0){
    char *args[] = {"ps", 0};
    exec("ps",args);
    // only reached if exec fails
    printf("Exec ps failed");
    exit(1);
  } else{
    wait(0);
    exit(0);
  }
}

