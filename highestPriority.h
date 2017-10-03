/**
 * Returns the number of process with the given priority.
 */
int countPriority(Proc **procs, int numProcs, int priority);

/**
 * Returns an array of integers.
 * Each integers is the number of processes with the priority of index + 1.
 */
int *countAllPriority(Proc **procs, int numProcs);

/**
 * Returns an array of priority queues for processes.
 * The first index hold priority 1 process.
 */
Proc ***priorityQueues(Proc **procs, int numProcs);

/**
 * Non-Preemptemptive High Priority First with each priority queue using FCFS.
 */
void nonpreHighestPriority(Proc **procs, int numProcs);

/**
 * Round Robin for a single queu.
 */
int queueRoundRobin(Proc ***priQueues, int queueNdx, int quantum,
 int *queueLengths, Proc **curProc);

/**
 * Preemptemptive High Priority First with each priority queue using Round Robin.
 */
void preempHighestPriority(Proc **procs, int numProcs);

/**
 * Completes multiple High Priority First runs.
 */
void HPFRuns(int numProcs, int preemp);
