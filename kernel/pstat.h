struct rusage{
    uint cputime;
};

struct pstat{
    int pid; // Process ID
    enum procstate state; // Process State
    uint64 size; // Size of process memory (bytes)
    int ppid; // Parent process ID
    char name[16]; // Parent command name
};
