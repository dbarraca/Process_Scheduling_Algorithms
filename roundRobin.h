/**
 * Adds to the ready processes if there are any new processes that have
 * arrived at the time of the given quantum.
 */
Proc **readyProcs(Proc **procs, int numProcs, Proc ** readyProcs,
 int numReady, int quantum);

void roundRobin(int numProcs);
