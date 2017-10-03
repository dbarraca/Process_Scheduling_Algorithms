/**
 * Returns the index to the next ready process.
 */
int nextReadyProc(Proc **procs, int numProcs, int startNdx, int quantum);
/**
 * Round Robin PRocess SCheduling Algorithm.
 */
void roundRobin(Proc **procs, int numProcs);

/**
 * Multiple runs of the Round Robin PRocess SCheduling Algorithm.
 */
void roundRobinRuns(int numProcs);
