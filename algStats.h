/**
 * Returns the average run time of the process that were ran.
 */
float avgRunTime(Proc **procs, int numProcs);

/**
 * Returns the average wait time of the process that were ran.
 */
float avgWaitTime(Proc **procs, int numProcs);

/**
 * Returns the average turn around time of the process that were ran.
 */
float avgTurnaroundTime(Proc **procs, int numProcs);

/**
 * Returns the throguhput of the process scheduling algorithm.
 */
float throughput(Proc **procs, int numProcs);

/**
 * Prints statistics on the Process Scheduling Algorithm runs.
 */
void algStats(Proc **procs, int numProcs);
