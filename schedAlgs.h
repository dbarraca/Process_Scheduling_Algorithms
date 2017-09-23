/**
 * Finds index of process with earliest arrival time
 */
int earlyArv(Proc **procs, int numProc, int quantum);

/**
 * Finds index of process with shortest expected run time
 */

int shortExp(Proc **procs, int numProc, int quantum);

int shortRemain(Proc **procs, int numProc, int quantum);

/**
 * returns the processes in arrival time order with earliest first
 */
Proc **orderProcs(Proc **procs, int numProc,
 int (*schedAlg)(Proc **, int));
