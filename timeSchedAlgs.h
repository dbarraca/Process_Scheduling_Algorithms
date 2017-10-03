#include "algStats.h"

/**
 * Finds index of process with earliest arrival time
 */
int earlyArv(Proc **procs, int numProc, int quantum);

/**
 * Finds index of process with shortest expected run time
 */
int shortExp(Proc **procs, int numProc, int quantum);

/**
 * Finds index of process with shortest remaining run time
 */
int shortRemain(Proc **procs, int numProc, int quantum);

/**
 * Run a time-based process scheduling algorithm.
 */
void runAlg(Proc **procs, int numProcs, int preemp,
 int (*nextProc)(Proc **procs, int numProc, int quantum));

/**
 * Run a time based process scheduling algorithm multiple times.
 */
void multipleRuns(int numProcs, int preemp, int numRuns,
 int (*nextProc)(Proc **procs, int numProc, int quantum));

/**
 * Returns the processes in arrival time order with earliest first
 */
Proc **orderProcs(Proc **procs, int numProc,
 int (*schedAlg)(Proc **, int, int));
