#include <stdio.h>
#include <stdlib.h>

#include "process.h"

#define ARRIV_MAX 100
#define RUN_MAX 11
#define PRIOR_MAX 5

/**
 * Generates process with random values
 */
Proc *randomProc(int arrival, int run, int priority){
	Proc *proc = malloc(sizeof(Proc));

	proc->arrivalTime = arrival % ARRIV_MAX;

	proc->expectedRunTime = run % RUN_MAX;
	if(proc->expectedRunTime == 0) {
		proc->expectedRunTime += 1;
    }

	proc->priority = priority % PRIOR_MAX;
	if(proc->priority == 0) {
		proc->priority += 1;
    }

	return proc;
}

/**
 * Generates |numProc| processes
 */
Proc **generateProcs(int numProc) {
    unsigned int seed = 0;
    int procIndex = 0;
    Proc **procs = malloc(sizeof(Proc *) * numProc);

	srand(seed);

    for (procIndex = 0; procIndex < numProc; procIndex++) {
        *(procs + procIndex) = randomProc(rand(), rand(), rand());
    }

	return procs;
}

/**
 * Print arrival time, run time, and priority of the given process
 */
void printProc(Proc *proc) {
    printf("arrival time  = %f\n", proc->arrivalTime);
//    printf("run time  = %f\n", proc->expectedRunTime);
//    printf("priority  = %i\n\n", proc->priority);
}

/**
 * Print arrival time, run time, and priority of all the given processes
 */
void printProcs(Proc **procs, int numProc) {
	int procIndex;

	for (procIndex = 0; procIndex < numProc; procIndex++) {
       printProc(*(procs + procIndex));
	}
}

/**
 * Makes a copy of the processes with the process to be removed
 */
Proc **removeProc(Proc **procs, int numProc, int removeIndex) {
	Proc **newProcs = malloc(sizeof(Proc *) * numProc);

	memcpy(newProcs, procs, sizeof(Proc *) * removeIndex);
	memcpy(newProcs + removeIndex, procs + (removeIndex + 1),
	 sizeof(Proc *) * (numProc - removeIndex - 1));

	free(procs);
	return newProcs;
}
