#include "kernel/types.h"
#include "user/user.h"

int
main (int argc, char *argv[])
{

    //call uptime() and store the result
    uint64 uptime_res = uptime();

    // print the result
    printf("up %lu clock ticks\n", uptime_res);

    // exit
    exit(0);

}
