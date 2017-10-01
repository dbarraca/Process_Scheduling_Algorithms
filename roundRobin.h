/**
 * Adds to the ready processes if there are any new processes that have
 * arrived at the time of the given quantum.
 */
//Proc **readyProcs(Proc **procs, int numProcs, Proc ** readyProcs,
// int numReady, int quantum);
Proc **readyProcs(Proc **procs, int numProcs, int quantum);
int nextReadyProc(Proc **procs, int numProcs, int startNdx, int quantum);
void roundRobinRuns(int numProcs);
