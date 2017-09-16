#include <stdlib.h>
#include <stdio.h>
#include "process.h"
#include "schedAlgs.h"

/**
 * Finds index of process with earliest arrival time
 */
int earliestArrival(Proc **procs, int numProc) {
	int procIndex = 0;
	float earliestArrivTime = 100;
    int earliestIndex;

	for (procIndex = 0; procIndex < numProc; procIndex++) {
		Proc *currentProc = *(procs + procIndex);

		if(currentProc->arrivalTime < earliestArrivTime) {
			earliestIndex = procIndex;
			earliestArrivTime = currentProc->arrivalTime;
		}
	}

	return earliestIndex;
}

/**
 * returns the processes in arrival time order with earliest first
 */
Proc **arrivalOrder(Proc **procs, int numProc) {
    Proc **orderedProcs = malloc(sizeof(Proc *) * numProc);
    Proc **unorderedProcs = malloc(sizeof(Proc *) * numProc);
    int numUnordered = numProc, retNumProc = 0, procIndex;

    memcpy(unorderedProcs, procs, sizeof(Proc *) * numProc);

    for(procIndex = 0; procIndex < numProc; procIndex++) {
        *(orderedProcs + retNumProc) =
         *(unorderedProcs + earliestArrival(unorderedProcs, numUnordered));
        retNumProc++;

        unorderedProcs = removeProc(unorderedProcs, numUnordered,
         earliestArrival(unorderedProcs, numUnordered));
        numUnordered--;
    }

    free(unorderedProcs);

    return orderedProcs;
}
