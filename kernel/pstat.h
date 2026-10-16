#ifndef PSTAT_H
#define PSTAT_H

struct rusage{
    uint cputime;
};

enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

struct pstat{
    int pid; // Process ID
    enum procstate state; // Process State
    uint64 size; // Size of process memory (bytes)
    int ppid; // Parent process ID
    char name[16]; // Parent command name
    int priority; // Priority
    uint readytime; // Time spent ready
};

#endif
