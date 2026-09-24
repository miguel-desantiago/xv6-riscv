#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#include "kernel/pstat.h"

int 
main (int argc, char *argv[])
{

    // Check if argc >= 2 (user enters command)
    if (argc >= 2){

        // Save user arguments
        char* user_command = argv[1];
        char** user_command_args = argv+1;

        // Start timer
        uint64 start = uptime();

        // Fork
        int rc = fork();

        // Fork failed
        if (rc < 0){
            printf("fork failed\n");
            exit(1);
        }

        // Child
        else if (rc == 0){
            // Execute user command
            exec(user_command, user_command_args);

            // Failed Exec, only reaches this line if a failure occurs
            printf("exec failed\n");
	    exit(1);
        }

        // Parent
        else{
            // Call wait2() with respective addresses for status and rusage
	    int proc_status;
	    struct rusage proc_rusage;
            wait2(&proc_status, &proc_rusage);

	    uint64 proc_cputime =  proc_rusage.cputime;

	    // Calculate total elapsed time for process
            uint64 end = uptime();
            uint64 total_time_elapsed = end-start;

	    // Calculate total CPU Usage Time
	    int cpu_usage = (100 * proc_cputime) / total_time_elapsed;

            printf("elapsed time: %lu ticks, cputime: %lu ticks, %d%% CPU\n", total_time_elapsed, proc_cputime, cpu_usage);
            exit(0);
        }
    }

    // Program exits with no user arguments passed
    else {
        printf("Usage: time1 command [args]");
        exit(0);
    }
}

