int possibleNextProc(Proc **procs, int numProc, int quantum, Proc *oldProc);

/*
 * Adds to the ready processes if there are any new processes that have arrived
 *  at the time of the given quantum.
 */
Proc **checkArrived(Proc **procs, int numProcs, Proc ** readyProcs,
 int numReady, int quantum);

void roundRobin(int numProcs);
